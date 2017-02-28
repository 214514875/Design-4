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
 #include "PIC16_I2C_BITBANG.h"

signed int a;
void i2c_Send_Byte(unsigned char ch);
unsigned char i2c_Recieve_Byte();

void i2c_Send_Byte(unsigned char ch)
{
    for(a=0;a<8;a++)
    {
      bit_out(ch<<a);  
    }
}


unsigned char i2c_Recieve_Byte()
{
    unsigned char temp = 0x00;
    for(a=7;a>=0;a--){
        bit_in(&temp);
        temp<<a;
    }
    return temp;
}

void main(void) {  
    unsigned char temp = 0x00;
    unsigned char temp1 = 0x00;
    
    TRISC = 0x00;
    TRISB = 0x00;
    
    ANSEL = 0x00;
    ANSELH = 0x00;
    CM1CON0= 0;
    CM2CON0= 0;
    __delay_ms(100);
    
    Lcd_Init();    
    //Test out the I2C Library
    i2c_start();
    i2c_Send_Byte(0xD0); //Data Write
    bit_in(&temp);
    i2c_Send_Byte(0x00);
    bit_in(&temp);
    i2c_Send_Byte(0x00);
    bit_in(&temp);
    i2c_stop();
    
    i2c_start();
    i2c_Send_Byte(0xD1); //Data Read
    bit_in(&temp);
    
     bit_in(&temp);
     bit_in(&temp);
     bit_in(&temp);
     bit_in(&temp);
     bit_in(&temp);
    bit_in(&temp);
    bit_in(&temp);
    bit_in(&temp);
    
    i2c_sendnoack();
    i2c_stop();
    
    Lcd_Write_Char(temp + 0x30);
    
    
    while(1)
    {
       
    }
    
    return;
}
