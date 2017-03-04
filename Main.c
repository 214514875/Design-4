/*
 * File:   Main.c
 * Author: Denver Pillay
 *
 * Created on 21 February 2017, 9:08 AM
 */
#define _XTAL_FREQ 8000000
//For LCD
#define RS RC3
#define EN RC4
#define D4 RC0
#define D5 RC1
#define D6 RC2
#define D7 RC6


//Configuration
#pragma config FOSC = HS,WDTE=OFF ,PWRTE = OFF,BOREN = OFF
#include <xc.h>
#include "lcd.h" 
#include "PIC16_I2C_BITBANG.h"
#include "UART Library.h"

signed int a;
unsigned char value[50];

void main(void) {
    GIE = 0;
    /*Setting Fosc to 8MHz*/
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;

    /*Disabling analogue inputs and comparators*/
    ANSEL = 0x00;
    ANSELH = 0x00;
    //CM1CON0 = 0;
    //CM2CON0 = 0;

    /*Initialisation for ESP8266
    TRISC = 0;
    TRISB = 0x10; //All But RB4 set as output for Port B
    TRISB5 = 1; //Set as input
    TRISB7 = 0; //Set as output
    SPBRGH = 0; //Baud Rate of ~ 9600
    SPBRG = 12;
    TXEN = 1;
    CREN = 1; //Enabling Reception
    SYNC = 0;
    SPEN = 1;
     */

    unsigned char temp = 0x00;
    unsigned char temp1 = 0x00;

    TRISC = 0x00;

    __delay_ms(100);

    Lcd_Init();

    //Write and the Read
    i2c_start();
    i2c_wr(0xD0);
    i2c_wr(0x00);
    i2c_wr(0x09);
    i2c_stop();

    //Test out the I2C Library
    i2c_start();
    i2c_wr(0xD0); //Data Read using a false write
    i2c_wr(0x00);

    i2c_start();
    i2c_wr(0xD1);
    temp = i2c_rd(NACK); //i2c_Recieve_Byte(&temp);
    i2c_stop();

    //temp1 = esp8266_isStarted();
    temp = 0;
    temp = UART_Init(9600);

    Lcd_Write_Char(temp + 0x30);

    /*Trying to get a ESP8266 interface*/

    while (1) {
       
        /*RC7 = 1;
        __delay_ms(1000);
        RC7 = 0;
        __delay_ms(1000);*/

    }

    return;
}
