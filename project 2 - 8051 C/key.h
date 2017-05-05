#ifndef KEY_H
#define KEY_H

#include "reg932ALTERED.h"
//#include <reg932.h>


//---------------------------------------------------------
// GLOBAL VARIABLES
//---------------------------------------------------------

const char song1[] = {'p','a','r','a','n','o','i','d','\n','\r'};
//const char song1_length = 10;
const char song2[] ={'h','a','s','h','\n','\r'};
//const char song2_length = 6;

// For the play_stored mode.
const char MAX_NOTE_COUNT = 5;
char Note_Count;
char stored_key[5]; // For LED display - ^2, ^1, ^0: key, ^7: sf_bool 
int stored_t0_val[5]; // Stores notes
long stored_duration_count[5]; //Stores duration in a char



bit sf_bool; ///< 1: using the sharp/flat keys, 0: not.

float current_octave; ///< Default 1, range: [8,0.125]

int t0_val; ///< Set every time we play a new key --> TH0>>8, TL0 value.

long duration_count; ///< num half periods for duration of sound

const char NOT_KEY = -1;

//------------------------------
// OPT |UP|    2.0|0.1|2.3
// DOWN|  |    0.2|1.4|0.0
//     |  |    2.1|0.3|2.2
//------------------------------
sbit KEY_OPTIONS_btn = P2^0; ///< sf_bool set when this is held
sbit OCT_UP_btn = P0^1;
sbit OCT_DOWN_btn = P0^2;

//------------------------------
//    |   |     2.0|0.1|2.3
// Usr|Oth|Par  0.2|1.4|0.0
//    |   |     2.1|0.3|2.2
//------------------------------
sbit paranoid_btn = P0^0;
sbit other_btn = P1^4;
sbit user_btn = P0^2;

sbit SOUND_port = P1^7;


//---------------------------------------------------------
// Sharps/Flat Keys (SF)
//---------------------------------------------------------
//const char NUM_SF_KEYS = 5;
//const char CD = 0, DE = 1, FG = 2, GA = 3, AB = 4;
const int NUM_SF_MC[] = {6650, 5924, 4982, 4438, 3954};

//------------------------------
//   |  |AB  2.0|0.1|2.3
//   |GA|DE  0.2|1.4|0.0
// FG|CD|    2.1|0.3|2.2
//------------------------------
sbit CD_btn = P0^3;
sbit DE_btn = P0^0;
sbit FG_btn = P2^1;
sbit GA_btn = P1^4;
sbit AB_btn = P2^3;



//---------------------------------------------------------
// Other keys
//---------------------------------------------------------
//const char NUM_KEYS = 7;
//const char C_ = 0, D_ = 1, E_ = 2, F_ = 3, G_ = 4, A_ = 5, B_ = 6;
const int NUM_MC[] = {7045, 6277, 5592, 5278, 4702, 4189, 3732};

//------------------------------
//  |b|g  2.0|0.1|2.3
// a|e|f  0.2|1.4|0.0
// c|d|   2.1|0.3|2.2
//------------------------------
sbit C_btn = P2^1;
sbit D_btn = P0^3;
sbit E_btn = P1^4;
sbit F_btn = P0^0;
sbit G_btn = P2^3;
sbit A_btn = P0^2;
sbit B_btn = P0^1;



//---------------------------------------------------------
// Key Methods
//---------------------------------------------------------

// Need these two to be able to use the key variables to reference ports 
bit get_key_state(const char key);

unsigned int get_num_mc(const char key);
char get_num_keys();

void up_oct();
void down_oct();

void stop_playing();
void turn_on_sseg(const char key);
void play_stored(char stored_key, int stored_t0_val, long stored_duration_count);
void play(const char key, const char duration_s);
void toggle_sound_set_timer();
void key_interrupt();

bit play_loop(char note,char dur);

char get_index_pressed_key();
char update_keys_playing(const char prev_key);


#endif