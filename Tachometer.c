/*
 * File:   Tachometer.c
 * Author: jneveu
 *
 * Created on February 11, 2020, 12:23 PM
 * Edited: 6-28-21 by Jacob Hall
 * 
 * PORT A:    
 * RA0 (pin 13) ICSP Connector Pin #4	(ICSPDAT) 
 * RA1 (pin 12) ICSP Connector Pin #5	(ICSPCLK)
 * RA2 (pin 11) Extra pin
 * RA3 (pin 4)  ICSP Connector Pin #1	(ICSP VPP)
 * RA4 (pin 3)  input - Encoder B phase (white) for direction(changed from (RA5)
 * RA5 (pin 2)  input - Encoder A phase (green) for direction (changed from RA3)
 * PORT C:
 * RC0 (pin 10) output - D4
 * RC1 (pin 9)  output - D5
 * RC2 (pin 8)  output - D6
 * RC3 (pin 7)  output - D7		
 * RC4 (pin 6)  output - LCD RS
 * RC5 (pin 5)  output - LCD E
 * 
 */

// PIC16F1823 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdlib.h>
#include <string.h>
#include "LCD.h"
#define _XTAL_FREQ 1000000 //SETS FREQ FOR DELAY

    void __interrupt () ISR (void); //PROTOTYPE FOR THE INTERRUPT SUBROUTINE
    void direction (void);
    void printLCD (void);
    char* ItoA(int);
    
    const char clockwise[] = "Counter Clock";
    const char counterclockwise[] = "Clockwise";
    const char speed[] = "RPM:";
    
    int count;
    int hold;
    int RPMdisplay;
    int motorDirection;
    
void main(void) {

    //TIMER0 COUNTER SET UP
    TMR0CS = 1;
    TMR0SE = 1;
    PSA = 0;
    
    //TIMER1 SET UP
    OSCCON = 0x58; //OSCILATOR SET TO 1 MHZ
    T1CON = 0x31; //TIMER1 IS ENABLED AND PRESCALE IS SET TO 8:1
    TMR1IE = 1;
    PEIE = 1;
    GIE = 1;
          
    // PORT A SET UP
    PORTA = 0x00;
    LATA = 0x00;  //ALL PINS START LOW
    TRISA = 0x3F; //RA4, RA5  SET AS INPUTS
    ANSELA = 0x00; //ALL PINS ARE SET TO DIGITAL
    WPUA = 0x30; //PULL-UP RESISTORS SET ON RA4 & RA5
    nWPUEN = 0; //PULL-UP RESISTORS ARE ENABLED
    
    // PORT C SET UP
    PORTC = 0x00;
    LATC = 0x00; //ALL PINS START LOW
    TRISC = 0X00;  //ALL PINS SET AS OUTPUTS
    ANSELC = 0x00; //ALL PINS ARE SET TO DIGITAL
    WPUC = 0x00; //PULL-UP RESISTOR NOT SET

    lcd_Initialize();
    lcdDisplay(1,0,0);
    
    while(1){
        
        
        //stringToLCD(speed);
        direction();
        
        //SECTION IN CHARGE OF COUNTING PULSES
        if(RA5 == 0){
        count++;
        while(RA5 == 0){     
        }
        
        }
            } 
   
    return;
}


    void ISR (void){
                
    TMR1ON = 0; //TURNS TIMER1 OFF          
    TMR1 = 34286; //SET TIMER SO IT REFRESHES EVERY SECOND
       
    float RPMvalue;
    
       RPMvalue = count*0.15;
       count = RPMvalue;
           
       cLCD();
       goTo(0,0);
       stringToLCD(speed);
       stringToLCD(ItoA(count));
       
       goTo(0,1);
       if(motorDirection == 1)
       stringToLCD(clockwise);
       if(motorDirection == 0)
       stringToLCD(counterclockwise);    
       
       count = 0; //RESETS PULSE COUNT
       
       TMR1ON = 1; //TURNS TIMER1 BACK ON            
       TMR1IF = 0; //RESETS FLAG   
         
         
           
     } //END OF ISR FUNCTION
 
    
    void direction (void){
     
     if((RA4 == 0) && (RA5 == 0)){
           hold = 1;
           
                while(hold == 1){
           
                    if((RA4 == 1) && (RA5 == 0)){ 
                    motorDirection = 1;
                    hold = 0;
                    }
           
                    if((RA4 == 0) && (RA5 == 1)){
                    motorDirection = 0;
                    hold = 0;
                    }
           
                } //END OF WHILE LOOP
           
        } //END OF IF STATEMENT 
     
}
    
    char* ItoA(int x)
{
	int remainder;
	char Num_str[33];
	Num_str[32]='\0';
	char *ptr = &Num_str[32];
	
	do
	{
		remainder = x % 10;
		x /= 10;
		*--ptr = (unsigned char)remainder + 48; 
	}while(x!=0);
	
	return (ptr);
}