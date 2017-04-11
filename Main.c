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

signed int a, pos = 0;
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

    unsigned char temp = 0x00;

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

    /*
    __delay_ms(1000);
    UART_Write_Text("AT+CIPSTATUS:tetype\r\n");
    char str [40];
    UART_Read_Text(&str,39);
    
     */

    /*
    int j;
    for(j=0;str[j]!='\0';j++){
        Lcd_Write_Char(str[j]);
        __delay_ms(500);
        if(j%15==0){
            Lcd_Clear();
        }
    }
     */

    /*Check Startup*/  
    __delay_ms(50);
    UART_Write_Text("AT\r\n");
    newCheck();

    __delay_ms(50);
    UART_Write_Text("AT+CWMODE=1\r\n");
    //newCheck();


    char str [20];
    UART_Read_Text(&str, 10);
    Lcd_Write_String(str);

    Lcd_Clear();
    int j;
    for (j = 0; str[j] != '\0'; j++) {
        Lcd_Write_Char(str[j]);
        __delay_ms(500);
        if (j % 16 == 0) {
            Lcd_Clear();
        }
    }


    UART_Write_Text("AT+CIPMUX=1\r\n");
    newCheck();
    __delay_ms(5000);

    UART_Write_Text("AT+CWJAP=\"NOKIA 909_0136\",\"4904aA!!\"\r\n");
    newCheck();
    __delay_ms(15000);

    /*
    UART_Write_Text("AT+CIPSTART=4,\"TCP\",\"184.106.153.149\",80\r\n");
    newCheck();
    __delay_ms(50);*/

    //192.168.137.43//192.168.1.64


    UART_Write_Text("AT+CIPSTART=4,\"TCP\",\"192.168.137.43\",4000\r\n");
    newCheck();
    __delay_ms(1000);

    UART_Write_Text("AT+CIPSEND=4,10\r\n");
    waitToSend();
    __delay_ms(1000);


    UART_Write_Text("111111\r\n");
    __delay_ms(1000);
    
    Lcd_Clear();
    Lcd_Write_String("Said");
    
    UART_Write_Text("AT+CIPCLOSE=4\r\n");
    newCheck();
    Lcd_Write_String("Said");
    // newCheck();
    //__delay_ms(1000);
    
    while (1) {
    }

    UART_Write_Text("AT+CIPSEND=4,50\r\n");
    waitToSend();
    __delay_ms(50);

    UART_Write_Text("GET /update?key=FQHTFYSPY3K8LML7&field1=101010\r\n");
    __delay_ms(50);

    UART_Write_Text("AT+CIPCLOSE=4\r\n");
    //newCheck();



    while (1) {

    }

    return;
}
