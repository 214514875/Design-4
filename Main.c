/*
 * File:   Main.c
 * Author: Denver Pillay
 *
 * Created on 21 February 2017, 9:08 AM
 */
#define _XTAL_FREQ 4000000

//For LCD
#define RS RC3
#define EN RC4
#define D4 RC0
#define D5 RC1
#define D6 RC2
#define D7 RC6

//For I2C Bitbang

//Configuration
#pragma config FOSC = HS,WDTE=OFF ,PWRTE = OFF,BOREN = OFF
#include <xc.h>
#include "lcd.h" 
#include "I2C_Software.h"

signed int a;


void main(void) {
    unsigned char temp = 0x00;
    unsigned char temp1 = 0x00;

    TRISC = 0x00;
    TRISB = 0x00;

    ANSEL = 0x00;
    ANSELH = 0x00;
    CM1CON0 = 0;
    CM2CON0 = 0;
    __delay_ms(100);

    Lcd_Init();
    Lcd_Clear();
    
    /*Testing out*/
    
    Lcd_Write_Char(0x30+temp);
    
    //Test out the I2C Library
    while (1) {

    }

    return;
}
