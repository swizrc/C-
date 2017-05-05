#ifndef LEDS_H
#define LEDS_H

//------------------------------
// TL_|T__|TR_    2.4|0.5|2.7
// L__|M__|R__    0.6|1.6|0.4
// BL_|B__|BR_    2.5|0.7|2.6
//------------------------------
sbit TL_ = P2^4;
//sbit T__ = P0^5; // We don't use this one. Saving memory.
sbit TR_ = P2^7;
sbit L__ = P0^6;
sbit M__ = P1^6;
sbit R__ = P0^4;
sbit BL_ = P2^5;
sbit B__ = P0^7;
sbit BR_ = P2^6;

#endif