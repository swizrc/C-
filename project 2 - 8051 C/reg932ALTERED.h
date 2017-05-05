//Altered reg932.h to save on program memory

#ifndef REG932ALTERED_H
#define REG932ALTERED_H

//  BYTE Registers
sfr P0   = 0x80;
sfr P1   = 0x90;
sfr P2   = 0xA0;
sfr TCON = 0x88;
sfr TMOD = 0x89;
sfr TL0  = 0x8A;
sfr TH0  = 0x8C;
sfr IEN0 = 0xA8;
sfr SCON = 0x98;

sfr P0M1   = 0x84;
sfr P1M1   = 0x91;
sfr P2M1   = 0xA4;


//  TCON
sbit TF0  = TCON^5;
sbit TR0  = TCON^4;
sbit IE0  = TCON^1;
sbit IT0  = TCON^0;

//  IEN0 
sbit EA   = IEN0^7;
sbit ET0  = IEN0^1;

//  SCON  
sbit RI   = SCON^0;



// Special function registers and bit for UART

/*  BYTE Registers  */

sfr PCON = 0x87;
sfr IP0  = 0xB8;
sfr SBUF = 0x99;

sfr AUXR1  = 0xA2;
sfr BRGR0  = 0xBE;
sfr BRGR1  = 0xBF;
sfr BRGCON = 0xBD;
sfr P1M2   = 0x92;
sfr SSTAT  = 0xBA;
sfr IP0H   = 0xB7;

/*  SCON  */
sbit TI   = SCON^1;





#endif

