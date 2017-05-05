#ifndef MODES_H
#define MODES_H



//---------------------------------------------------------
// GLOBAL VARIABLES
//---------------------------------------------------------
sbit MODE_btn = P2^2;
bit last_mode_btn_state; ///< 1 or 0, corresponding to previous state of P2^2

char mode; ///< Global var for the mode of operation
//const char NUM_MODES = 4;

//---------------------------------------------------------
// Mode methods
//---------------------------------------------------------
void free_play_modes();
void play_stored_mode();
void serial_play_mode();

bit play_loop(char note, char dur);
void increment_mode();
void update_mode_leds();

bit mode_btn_released();

#endif