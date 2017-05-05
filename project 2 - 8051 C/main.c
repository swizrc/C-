#include "key.h"
#include "modes.h"
#include "key_stack.h"
#include "leds.h"
#include "common_utils.h"
#include "uart.h"



//---------------------------------------------------------
// common_utils.h methods
//---------------------------------------------------------



// @name: btn_just_released
// @brief: Return true if the button was pressed and is now released. Else
//			false. DOES NOT UPDATE last_btn_state!
bit btn_just_released(bit btn_state, bit last_btn_state)
{
	return (1 == btn_state) && (0 == last_btn_state); // If button (is released) and (was pressed)
}



//---------------------------------------------------------
// hey.h methods
//---------------------------------------------------------

// @name: get_key_state
// @brief: Given the global 'sf' state and the key, return a 1 or 0
//			representing the value of the port.
bit get_key_state(const char key)
{
	if(sf_bool)
	{
		return (key == 0 && CD_btn) || (key == 1 && DE_btn) || (key == 2 && FG_btn) || (key == 3 && GA_btn) || (key == 4 && AB_btn); 
	}
	else
	{
		return (key == 0 && C_btn) || (key == 1 && D_btn) || (key == 2 && E_btn) || (key == 3 && F_btn) || (key == 4 && G_btn) || (key == 5 && A_btn) || (key == 6 && B_btn);
	}
}



// @name: get_num_mc
// @brief: Return a the number of mc for the hal-period of the key. The value
//			depends on 'sf' and 'current_octave'.
unsigned int get_num_mc(const char key)
{
	if(sf_bool)
	{
		return NUM_SF_MC[key]*current_octave;
	    //switch(key)
	    //{
	    //    case 0: return 6650*current_octave; // cd (0)
	    //    case 1: return 5924*current_octave; // de (1)
	    //    case 2: return 4982*current_octave; // fg (2)
	    //    case 3: return 4438*current_octave; // ga (3)
	    //    case 4: return 3954*current_octave; // ab (4)
	    //}
	}
	else
	{
		return NUM_MC[key]*current_octave;
	    //switch(key)
	    //{
	    //    case 0: return 7045*current_octave; // c  (0)
	    //    case 1: return 6277*current_octave; // d  (1)
	    //    case 2: return 5592*current_octave; // e  (2)
	    //    case 3: return 5278*current_octave; // f  (3)
	    //    case 4: return 4702*current_octave; // g  (4)
	    //    case 5: return 4189*current_octave; // a  (5)
	    //    case 6: return 3732*current_octave; // b  (6)
	    //}
	}
}



// @name: get_num_keys
// @brief: Return a different value depending 'sf'.
char get_num_keys()
{
	if(sf_bool)
	{
		return 5;
	}
	else
	{
		return 7;
	}
}



// @name: up_oct
// @brief: Move up an octave
void up_oct()
{
	if(current_octave > .125) // .125 = 2^-3 --> 3 octaves up from middle c
	{
		current_octave/=2;
	}
}



// @name: down_oct
// @brief: Move down an octave (only can be done 3 times 
void down_oct()
{
	if(current_octave < 8) // 8 = 2^3 --> 3 octaves down from middle c
	{
		current_octave*=2;
	}
}



// @name: stop_playing
// @brief: Turn off timer0. Turn off the sound.
void stop_playing()
{
	TR0 = 0; // Timer off.
	SOUND_port = 1; // TURN OFF (active low)

	// These ports are only set by the 'play' methods.
	L__ = 0;
	M__ = 0;
	R__ = 0;
	TR_ = 0;
}



// @name: turn_on_sseg
// @brief: Turn off timer0. Turn off the sound.
void turn_on_sseg(const char key)
{
	char portsval; //^2 is L__, ^1 is M__, ^0 is R__

	if(sf_bool)
	{
		//c#(0) -> 010 2
		//d#(1) -> 011 3
		//f#(2) -> 101 5
		//g#(3) -> 110 6
		//a#(4) -> 111 7
		
		if(key<2) // key < FG (aka f#)
		{
			portsval = key+2;
		}
		else
		{
			portsval = key+3;
		}
	}
	else
	{
		//c(0) -> 010 2
		//d(1) -> 011 3
		//e(2) -> 100 4
		//f(3) -> 101 5
		//g(4) -> 110 6
		//a(5) -> 111 7
		//b(6) -> 001 1
		
		if(key<6) // key < B_
		{
			portsval = key+2;
		}
		else
		{
			portsval = 1;
		}
	}

	L__ = (portsval & 4); // Get 2nd bit
	M__ = (portsval & 2); // Get 1st bit
	R__ = (portsval & 1); // Get 0th bit
	TR_ = sf_bool || (key & 128); // If playing the stored song, ^7 is the sf_bool val.
}



// @name: play_stored
// @brief: Play a stored note with the specified t0 value and duration count.
void play_stored(char stored_key, int stored_t0_val, long stored_duration_count)
{
	TR0 = 0; //	Start by turning the timer off in case other key playing.

	t0_val = stored_t0_val;

	duration_count = stored_duration_count; // For the RECORD_FREE_PLAY mode.

	turn_on_sseg(stored_key);

	TF0 = 1; // This is weird - force the interrupt to set TH0 and TL0.
	TR0 = 1; // Timer on!
}



// @name: play
// @brief: If mode <= 2, duration_s will be ignored and the note will play
//			indefinitely. NOTE that negative duration will equate to a duration
//			of 1/abs(duration_s) seconds.
//
//		   1) Load timer 0 with # mc / half period.
//         2) Set duration_count based on # mc / half period.
//                (will count # half periods)
//         3) Start timer.
void play(const char key, const char duration_s)
{
	float duration;
	int num_mc_halfp;

	TR0 = 0; //	Start by turning the timer off in case other key playing.
	
	num_mc_halfp = get_num_mc(key);
	t0_val = -num_mc_halfp; // 2's comp	

	// Only bother with duration calculations if not free play
	if(mode > 2)
	{
		// This allows us to pass in chars for durations < 1 rather than floats.
		duration = duration_s;
		if(duration < 0)
		{
			  duration = 1/(-duration);
		}
	
		// Set the duration
		duration_count = (3686500/num_mc_halfp) * duration;
	}
	else
	{
	 	duration_count = 0;
	}

	turn_on_sseg(key);

	TF0 = 1; // This is weird - force the interrupt to set TH0 and TL0.
	TR0 = 1; // Timer on!
}



// @name: toggle_sound_set_timer
// @brief: IF NOT PLAYING A REST, toggle the sound port. Regardless, reset the
//			TH0 and TL0 values.
void toggle_sound_set_timer()
{
	SOUND_port = ~SOUND_port;
	TH0 = t0_val >> 8;
	TL0 = t0_val;
}



// @name: key_interrupt
// @brief: Handle the key-playing timer interrupt differently depending on
//			the mode.
void key_interrupt() interrupt 1
{
	if(mode < 3)
	{
		toggle_sound_set_timer();

		if(mode == 2)
		{
			++duration_count;
		}
	}
	else
	{
		if(duration_count > 0)
		{
			toggle_sound_set_timer();
			--duration_count;
		}
		else
		{
			stop_playing();
		}
	}
}



// @name: get_index_pressed_key
// @brief: Return the index of the first key we find pressed. Else return -1.
char get_index_pressed_key()
{
	char key;
	for(key=0 ; key<get_num_keys() ; ++key)
	{
		if(0 == get_key_state(key))
		{
			return key;	
		}
	}
	return NOT_KEY;
}



// @name: update_keys_playing
// @brief: If there is a key pressed that is different from the key that was
//			playing last time we checked, play it. If same key, let it keep
//			playing. If none pressed, stop playing. 
// @param 'prev_key': What was the key playing the last time this was called?
// @return: The pressed key if there is one. Else -1. 
char update_keys_playing(const char prev_key)
{
	char key = get_index_pressed_key();
	bit key_changed = (prev_key != NOT_KEY) && (prev_key != key); // the previous key was indeed a key	AND is not the current key

	// If mode 2 and a key was just released, record prev key.
	if(key_changed && mode == 2)
	{
	  stored_key[Note_Count] = prev_key;
	  if(sf_bool)
	  {
	  	stored_key[Note_Count]+=128; // Store a 1 in ^7 to show the key was a sharp/flat.	
	  }
	  stored_t0_val[Note_Count] = t0_val; // Stores notes
	  stored_duration_count[Note_Count] = duration_count; //Stores duration in a char
	  Note_Count++;
	}
	
	// Alter which key is played?
	if(key == NOT_KEY || Note_Count >= MAX_NOTE_COUNT) // If nothing pressed
	{
		stop_playing();	
	}
	else // Key is pressed
	{
		if(key != prev_key)	// Different than last key
		{
			play(key,0); //infinite duration
			return key;
		}
	}

	return key;
}



//---------------------------------------------------------
// modes.h methods
//---------------------------------------------------------



// @name: free_play_modes
// @brief: Play any key for any duration of time. Track the duration if
//			recording.
void free_play_modes()
{
	bit up_oct_state, down_oct_state;
	char key = NOT_KEY;

	// Reset the value of Note_Count if in mode 2.
	if(mode == 2)
	{
	 	Note_Count = 0;
	}

	// Keep going until we try to switch modes OR as long as keys are pressed.
	while(!mode_btn_released())
	{
		if(mode != 2 || Note_Count < MAX_NOTE_COUNT) // Only allow MAX_NOTE_COUNT notes to be recorded.
		{
			// Play new key? Stop playing?
			key = update_keys_playing(key);
		
			// Change sharps/flats?
			sf_bool = ~KEY_OPTIONS_btn; // If held down, we are in sf_mode.
			TL_ = ~sf_bool; // Light stays on when in S/F mode.
			
			// Change octaves?
			if(sf_bool)
			{
				if(btn_just_released(OCT_UP_btn, up_oct_state))
				{
					up_oct();
				}
				up_oct_state = OCT_UP_btn;
				
				if(btn_just_released(OCT_DOWN_btn, down_oct_state))
				{
					down_oct();
				}
				down_oct_state = OCT_DOWN_btn;
			}
		}
	}
	
	TL_ = 1; // sf_bool LED back off
}



// @name: play_stored_mode
// @brief: The user can press the middle-left button to play their recorded
//			song, the middle button to play Hash Pipe, or the middle-right
//			button to play Paranoid.
void play_stored_mode()
{
	unsigned char i;
	bit last_paranoid_btn_state = 1, last_other_btn_state = 1, last_user_btn_state = 1;

	while(!mode_btn_released())
	{
	  current_octave = 1;
	  
	   //Second riff to Paranoid by Black Sabbath with a twist, cheap memory song
	  if(btn_just_released(paranoid_btn,last_paranoid_btn_state))
	  {
	  	for(i=0; i<10; i++)
			uart_transmit(song1[i]);

		for(i=0;i<8;i++)
		{
		  if(!(play_loop(2,-i)))
		  {
		   return;
		  }
		  up_oct();
		}  
		for(i=0;i<8;i++)
		{
		  if(!(play_loop(6,-i)))
		  {
		   return;
		  }
		  down_oct();
		} 
	  }
	  last_paranoid_btn_state = paranoid_btn;
	  
	   //Riff in Hash Pipe by Weezer, dirt poor memory song
	  if(btn_just_released(other_btn,last_other_btn_state))  
	  {
		for(i=0; i<6; i++)
			uart_transmit(song2[i]);

		down_oct();
		down_oct();
		for(i=0;i<4;i++)
		{
		  if(!(play_loop(5,-4) && play_loop(5,-4) && play_loop(6,-4) && play_loop(0,-4)))
		  {
		  	return;
		  }

		}
	  }
	  last_other_btn_state = other_btn;
	  
	  
	  if(btn_just_released(user_btn,last_user_btn_state))  	
	  {
		for(i=0;i<Note_Count;i++)
		  {
		  	play_stored(stored_key[i], stored_t0_val[i], stored_duration_count[i]);
			while(duration_count>0)
			{
			 	if(mode_btn_released())
				{
					return;
				}
			}
		  }
	  }
	  last_user_btn_state = user_btn;
	}
}



// @name: play_loop
// @brief: Play the note until its duration expires or until the mode button is
//			released.
bit play_loop(char note,char dur)
{
	play(note,dur);
	while(duration_count>0)
	{
	 	if(mode_btn_released())
			return 0;
	}
	return 1;
}



// @name: increment_mode
// @brief: Increment the mode. Will roll over if exceeds NUM_MODES. Possible
//			value range: [1, NUM_MODES]
void increment_mode()
{
	if(mode < 4)
	{
		++mode;
	}
	else
	{
		mode = 1;
	}
}



// @name: update_mode_leds
// @brief: Display the current mode on three LEDs.
void update_mode_leds()
{
	BL_ = !(mode & 4); // Get 2nd bit, then account for active low
	B__ = !(mode & 2); // Get 1st bit, ...
	BR_ = !(mode & 1); // Get 0th bit, ...
}



// @name: mode_btn_released
// @brief: Detect the release of button P2^2. It is active high, so check for a
//			P2^2 value of 1 with a prev value of 0. 
bit mode_btn_released()
{
	bit released = btn_just_released(MODE_btn, last_mode_btn_state);
	last_mode_btn_state = MODE_btn; // active low
	return released;
}



//---------------------------------------------------------
// main
//---------------------------------------------------------



void main()
{
	// Set ports bi-directional
	P2M1 = 0;
	P1M1 = 0;
	P0M1 = 0;

	last_mode_btn_state = MODE_btn;
	mode = 1; // Default first mode
	
	// Reg values
	EA = 1;	// Interrupts enabled
	ET0 = 1; // t0 interrupt enabled
	TMOD = 0x01; // t0 mode 1 (16-bit)

	//enable UART
	uart_init();

	while(1)
	{
		// You can count on these conditions at the start of each mode.
		sf_bool = 0; // Not sharp/flat mode
		current_octave = 1; // Middle c octave
		stop_playing(); // Not playing notes

		update_mode_leds();
		switch(mode)
		{
			case 1: free_play_modes(); break;
			case 2: free_play_modes(); break;
			case 3: play_stored_mode(); break;
			case 4: serial_play_mode(); break;
		}
		increment_mode();
	}
}



void serial_play_mode()
{ 
	
	char sound_num, mult;
	int durr; 

	sound_num=8;
	sf_bool = 0;
	durr = 0;
	mult=100;				 
	
	while(!mode_btn_released())
	{
		if(duration_count==0 && RI)
		{
			unsigned char input;
			input = uart_get();
			uart_transmit(input);
			switch(input)
			{

				case 'A':	
					if(sound_num == 4)
					{
						sound_num = 3;
						sf_bool = 1;
					}
					else if(sound_num == 8)
					{
						sound_num = 5;
					}
				break;
				case 'B':
					if(sound_num == 5)
					{
						sound_num = 4;
						sf_bool = 1;
					}
					else if(sound_num == 8)
					{
						sound_num = 6;
					}
				break;
				case 'C':
					if(sound_num == 8)
					{
						sound_num = 0;
					}
				break;
				case 'D':
					if(sound_num == 0)
					{
						sf_bool = 1;
					}
					else if(sound_num == 8)
					{
						sound_num = 1;
					}
				break;
				case 'E':
					if(sound_num == 1)
					{
						sf_bool = 1;
					}
					else if(sound_num == 8)
					{
						sound_num = 2;
					}
				break;
				case 'F':
					if(sound_num == 8)
					{
						sound_num = 3;
					}
				break;
				case 'G':
					if(sound_num == 3)
					{
						sound_num = 2;
						sf_bool = 1;
					}
					else if(sound_num == 8)
					{
						sound_num = 4;
					}
				break;
				case '^':	up_oct();	break;
				case 'v':	down_oct();	break;
				
				case ';':
					
					if(mult != 0)
						durr /= (mult*10);
						
					if(sound_num==8)
						sound_num=0;
					if(durr == 0)
						durr=1;

					play(sound_num,durr);

					sound_num=8;
					sf_bool = 0;
					durr = 0;
					mult=100;
					current_octave = 1; 	

				break;
			}
			
			if(input>='0' && input <= '9' && mult != 0)
			{
				durr += ((input-'0') * mult);
				if(mult == 1)
					mult = 0;
				else
					mult /= 10;
			}
		}
	}
}
