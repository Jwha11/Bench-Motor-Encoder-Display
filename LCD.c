/*
 * File:   LCD.c
 * Author: Mike
 *
 * Created on February 7, 2017
 * Modified on February 13, 2019
 * 
 *  Compiler: XC8 
 * Platform: PIC16F1823
 *
 * Description - LCD library of functions to be used in conjuction with LCD.h
 * 
 */

#include <xc.h>
#include <string.h>
#include "LCD.h"


void writebyteLCD(unsigned char out)
{
    unsigned char mask = 0x80;
    D7 = ((out & mask) == mask) ? 1 : 0 ;
    mask = 0x40;
    D6 = ((out & mask) == mask) ? 1 : 0 ;
    mask = 0x20;
    D5 = ((out & mask) == mask) ? 1 : 0 ;
    mask = 0x10;
    D4 = ((out & mask) == mask) ? 1 : 0 ;
    return;
}
void clockE(void)          //clocks enable for read / write
{
    Enable = 1;
    __delay_us(10);
    Enable = 0;
    __delay_us(10);
    return;
}
    
    void writeLCD(unsigned char out, unsigned char rs)
{
    RS = rs;
    writebyteLCD(out);
    clockE();
    __delay_us(200);
    out = out<<4;
    writebyteLCD(out);
    clockE();
}

void lcd_Initialize(void)
{
    
    __delay_ms(15);             // wait for the display to stabilize
    RS = 0;                     // set register select to instruction
    //*************************************************************************
    writebyteLCD(0x30);
    clockE();                   // Function Set - 8 bit mode
    //*************************************************************************
    __delay_ms(5);
    clockE();                   // Function Set - 8 bit mode
    //*************************************************************************
    __delay_us(200);
    clockE();                   // Function Set - 8 bit mode
    //*************************************************************************
    __delay_us(200);
    
    writebyteLCD(0x20);
    clockE();                   // Function Set DL = 1 4 bit mode
    //*************************************************************************
    __delay_us(200);
    
    writeLCD(0x28,0);           // Function Set DL = 0 4 bit, N = 1 2 lines, 
                                // F = 0 5x8
    //*************************************************************************
    __delay_us(200);
    
    writeLCD(0x0f,0);           // Display - on, cursor on, blinks 
    //*************************************************************************
    __delay_us(200);
    
    writeLCD(0x06,0);           // Entry Mode - Increment - no shift
    //*************************************************************************
    __delay_us(200);
    
    writeLCD(0x01,0);           // Clear Display
    //*************************************************************************
      __delay_ms(5);     
    
      writeLCD(0x02,0);         // Return Home
    //*************************************************************************
    __delay_ms(5);
    /* Initialization Complete */
}


void goTo(unsigned char pos, unsigned char line)
{
    if(pos > 39)
        return;
    pos += 0x80;        // add a one in most sig digit for command
    if(line == 1)
        pos += 0x40;    // if second line add 40h to get to next line
    writeLCD(pos,0);
    __delay_us(200);
    return;
}
    void cLCD(void)       // Clear the Display
    {
      writeLCD(0x01,0);
      __delay_ms(4);      
    }
    void lcdDisplay (unsigned char D, unsigned char C, unsigned char B)
    {
        if(D==1)
            B |= 0x04;
        if(C==1)
            B|= 0x02;
        
            B |= 0x08;
        
        writeLCD(B,0);
        __delay_us(200);
        return;
    }
    void lcdHome(void)
    {
        writeLCD(0x02,0);
        __delay_ms(4);
    }
    
    void stringToLCD(char mess[])
{
    unsigned int i = strlen(mess);
    for(char x = 0; x<i; x++)
        writeLCD(mess[x],1);
    return;
}