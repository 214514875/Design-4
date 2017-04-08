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
#include <stdio.h>
#include "lcd.h" 
#include "UART Library.h"

signed int a, pos=0;
unsigned char x = 0;

void main(void) {
    GIE = 0;

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
 
    TRISC = 0x00;
    Lcd_Init();

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

    unsigned char temp[35];
    /*Check Startup*/
    __delay_ms(1000);
    UART_Write_Text("AT\r\n");
    newCheck();
    
    /*Disable Echo*/
    __delay_ms(50);
    UART_Write_Text("ATE0\r\n");
    newCheck();
    
    /*Dual Mode - Client and Host*/
    __delay_ms(50);
    UART_Write_Text("AT+CWMODE=3\r\n");
    newCheck();
    
    /*Enable Multiple Connections - Max 4*/
    __delay_ms(50);
    UART_Write_Text("AT+CIPMUX=1\r\n");
    newCheck();
    
    while(1){
        
    }
    
    Lcd_Clear();
    /*Creating a server to sent locally*/
    __delay_ms(50);
    UART_Write_Text("AT+CIPSERVER=1,333\r\n");
    newCheck();
    
    Lcd_Clear();
    __delay_ms(50);
    UART_Write_Text("AT+CIPSTATUS\r\n");
    UART_Read_Text(&temp, 20);
    Lcd_Write_String(temp);
    //newCheck();
    
    //Lcd_Clear();
    //Lcd_Write_String(arr);
    
    /*Connect to the Required Router using routerName and Password*/
    //__delay_ms(50);
    //UART_Write_Text("AT+CWJAP=\"Timmy\",\"96027313\"\r\n");
    //newCheck();
  
    
    /*Enable a connection to TCP and required Remote IP and PORT*/
    //__delay_ms(50);
    //UART_Write_Text("AT+CIPSTART=4,\"TCP\",\"184.106.153.149\",80\r\n");
    //newCheck();
    
    //Lcd_Clear();
    /*Data Send to the IOT server*/
    //__delay_ms(50);
    //UART_Write_Text("AT+CIPSEND=4,50\r\n");
    //waitToSend();
    
    /*Linking to Field*/
    //__delay_ms(50);
    //UART_Write_Text("GET /update?key=FQHTFYSPY3K8LML7&field1=101010\r\n");
    
    /*Close the channel*/
    //__delay_ms(1000);
    //UART_Write_Text("AT+CIPCLOSE=4\r\n");
    //newCheck();
    
  
  
    /*Send Data Over the Internet*/
    
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
