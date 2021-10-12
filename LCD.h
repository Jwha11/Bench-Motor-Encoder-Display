// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define RS LATCbits.LATC4
#define Enable LATCbits.LATC5
#define D4 LATCbits.LATC0
#define D5 LATCbits.LATC1
#define D6 LATCbits.LATC2
#define D7 LATCbits.LATC3

#define _XTAL_FREQ 1000000       // define 1 MHz oscillator frequency

#define cRight writeLCD(0x14,0)      // moves cursor one space right
#define cLeft writeLCD(0x10,0)        // move cursor one space left
#define sRight writeLCD(0x18,0)       // scrolls display one space right
#define sLeft writeLCD(0x1c,0)       // scrolls display one space left

void lcd_Initialize(void);
void writeLCD(unsigned char,unsigned char);            // writes char to LCD
void writebyteLCD(unsigned char);            // set output pins to 1st byte of char
void clockE(void);                      // toggles Enable to write to LCD
void goTo(unsigned char pos, unsigned char line);  // pos 0-39, line 0,1
void cLCD(void);       // Clear the Display
/* Adjusts the display D=1 on /0 off, cursor C=1 on/0 off, blink B=1 on/0 off*/
void lcdDisplay(unsigned char D, unsigned char C, unsigned char B);
void lcdHome(void);    // returns cursor to 0 position / shift to 0 position
void stringToLCD(char mess[]); // writes a string to LCD

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

