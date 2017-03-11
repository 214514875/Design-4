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
#pragma config FOSC = INTRCIO
#pragma config WDTE = OFF 
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config CPD = OFF
#pragma config CP = OFF 
//End of Configuration

#include <xc.h>
#include <string.h>
#include "lcd.h" 
#include "UART Library.h"
//#include "LOL.h"
//#include "esp8266.h"
//#include "PIC16_I2C_BITBANG.h"
//#include "LOL.h"

signed int a, pos;
unsigned char x = 0, value[15];

void clearVAL() {
    unsigned char i;
    for (i = 0; i < 15; i++)
        value[i] = NULL;
}

void main(void) {
    GIE = 0;
    /*Setting Fosc to 8MHz*/
    /*
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;

     */

    /*Disabling analogue inputs and comparators*/
    ANSEL = 0x00;
    ANSELH = 0x00;

    /*Disabling comparators*/
    C1ON = 0;
    C2ON = 0;

    //Initialisation for ESP8266
    TRISC = 0;
    TRISB = 0x10; //All But RB4 set as output for Port B
    TRISB5 = 1; //Set as input
    TRISB7 = 0; //Set as output
    SPBRGH = 0; //Baud Rate of ~ 9600
    SPBRG = 8;
    TXEN = 1;
    CREN = 1; //Enabling Reception
    SYNC = 0;
    SPEN = 1;
    BRGH = 1;
    BRG16 = 1;

    unsigned char temp = 0x00;
    unsigned char temp1 = 0x00;

    TRISC = 0x00;

    Lcd_Init();


    //UART_Init(9600);
    //EUSART_Init(9600);

    /*
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
     */

    __delay_ms(1000);

    clearVAL();
    UART_Write_Text("ATE0\r\n");
    UART_Read_Text(&value, 15);

    
    if (strstr(value, "OK") != NULL) {
        Lcd_Write_String("OK");
    } else {
        Lcd_Write_String("ERROR");
    }
    
    unsigned char tempp[15];
    __delay_ms(300);
    clearVAL();
    UART_Write_Text("AT\r\n");
    UART_Read_Text(&tempp, 10);
    
    Lcd_Write_String("LOLz");
    
    if (strstr(tempp, "OK") != NULL) {
        Lcd_Write_String("OK");
    } else {
        Lcd_Write_String("ERROR");
    }

    while (1) {
        // UART_Write_Text("AT");
        /*
         RC7 = 1;
         __delay_ms(1000);
         RC7 = 0;
         __delay_ms(1000);
         */

    }

    return;
}
