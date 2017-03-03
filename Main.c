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

//Configuration
#pragma config FOSC = HS,WDTE=OFF ,PWRTE = OFF,BOREN = OFF
#include <xc.h>
#include "lcd.h" 
#include "PIC16_I2C_BITBANG.h"
#include "esp8266.h"

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
    temp = i2c_rd(NACK);//i2c_Recieve_Byte(&temp);
    i2c_stop();

    Lcd_Write_Char(temp + 0x30);

    while (1) {

    }

    return;
}
