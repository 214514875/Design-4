#define _XTAL_FREQ 4000000
#define RS RC3
#define EN RC4
#define D4 RC0
#define D5 RC1
#define D6 RC2
#define D7 RC6

//Configuration
#pragma config FOSC = INTRCIO
#pragma config WDTE = OFF //OFF
#pragma config PWRTE = OFF //OFF
#pragma config BOREN = ON //ON
#pragma config CPD = OFF //OFF
#pragma config CP = OFF //OFF
//End of Configuration

//__CONFIG(0x2024);

/*Includes*/
#include <xc.h>
#include <string.h>
#include "lcd.h"

unsigned char value[50] = {0},pos = 0;
unsigned char sec = 0;
//UART Protocol
void interrupt Serial()
{
    if(RCIF==1&&pos<28)
    {
        value[pos]=RCREG;
        pos++;
        RCIF=0;


    }
}
void transmit(unsigned char x)
{
    TXREG=x;
    while(TRMT==0);

}


void transmit2(unsigned char *ptr)
{
    int i=0;
    pos=0;
    while(ptr[i]!='\0')
    {
        transmit(ptr[i]);
        i++;
        delay(100);
    }

    delay(10000);
}



void transmit_string(unsigned char *ptr)
{
    int i=0;
    pos=0;
    transmit(0x0d);
    transmit(0x0d);
    while(ptr[i]!='\0')
    {
        transmit(ptr[i]);
        i++;
        delay(100);
    }

    transmit(0x0d);
    transmit(0x0a);
    delay(60000);
}


void clearVAL()
{
    char i;
    for(i=0; i<30; i++){
        value[i]='\n';
    }
}

void delay1sec()
{
    char i;
    for(i=0; i<20; i++)
    {
        TMR1H=0x3a;
        TMR1L=0xbb;
        TMR1ON=1;

        while(TMR1IF==0);
        TMR1ON=0;
        TMR1IF=0;

    }
    sec++;
}

void main()
{ 
    char i=0,x=0,flag=0;
    unsigned int adc_val=0;

    ANSEL=0x00;//Intialise ADC channel RA0
    ANSELH=0x00;
    
    TRISC = 0;
    TRISB = 0x10; //All But RB4 set as output for Port B
    TRISB5 = 1; //Set as input
    TRISB7 = 0; //Set as output
    
    /*Disabling comparators*/
    C1ON = 0;
    C2ON = 0;
    
    T1CON=0x00;
    //TRISC=0XC0;

    delay(60000);
    SPBRG=8;
    TXSTA=0x26;
    RCSTA=0x90;
    BRG16 = 1;

    //ADCON0=0x01;  //channel 0,ADC on
    //ADCON1=0x80; // right justified, inner RC for FOSC
    //delay(1000);

    Lcd_Init();

    //delay(60000);
       
   // Lcd_Set_Cursor(1,1);
   // LCD
    Lcd_Write_String("ESP Temp Logger");
    
    delay(60000);
    delay(60000);
    delay(60000);
    //command(0x01);
    
    
    
    delay1sec();
    
    GIE=1;
    RCIE=1;
    PEIE=1;
    
    Lcd_Clear();
    
    /*******SENDING COMMANDS******/
    clearVAL();   //AT
    Lcd_Clear();
    Lcd_Write_String("AT");
    transmit_string("AT\r\n");
    while(1)
    {
        x=strstr(&value,"OK");
        if(x-32<0)
        {
            Lcd_Write_String("ERROR1");
        }
        else
        {
            Lcd_Write_String("OK1   ");
            break;
        }
    }
    delay(60000);

    clearVAL();   //ATE0
    Lcd_Write_String("ATE0");
    transmit_string("ATE0");
    while(1)
    {
        x=strstr(&value,"OK");
        if(x-32<0)
        {
            Lcd_Write_String("ERROR2");
        }
        else
        {
            Lcd_Write_String("OK2   ");
            break;
        }
    }
    delay(60000);


   // Lcd_Clear();
    clearVAL();   //AT+CWMODE=3
    Lcd_Write_String("AT+CWMODE=1");
    transmit_string("AT+CWMODE=1");
    while(1)
    {
        x=strstr(&value,"OK");
        if(x-32<0)
        {
            Lcd_Write_String("ERROR3");
        }
        else
        {
            Lcd_Write_String("OK3   ");
            break;
        }
    }
    delay(60000);



    clearVAL();   //AT+CIPMUX=1
    Lcd_Write_String("AT+CIPMUX=1");
    transmit_string("AT+CIPMUX=1");
    while(1)
    {
        x=strstr(&value,"OK");
        if(x-32<0)
        {
            Lcd_Write_String("ERROR4");
            
        }
        else
        {
            Lcd_Write_String("OK4   ");
            break;
        }
    }
    delay(60000);

    clearVAL();   //AT+CWJAP
    Lcd_Write_String("connecting...");
    //value[0]='\0';
    //strcat(value,"AT+CWJAP=\"MWEB_CB7A29\",\"1E28E9B6FC\"");//Connect to WIFI
    //transmit_string(&value);
    
    transmit_string("AT+CWJAP=\"");
    transmit_string("MWEB_CB7A29");
    transmit_string("\",\"");
    transmit_string("1E28E9B6FC");
    transmit_string("\"\r\n");
    
    while(1)
    {
        x=strstr(&value,"OK");
        if(x-32<0)
        {
            Lcd_Write_String("464");
            break;
        }
        else
        {
            Lcd_Write_String("OK5   ");
            break;
        }
    }
   delay(60000);

    //command(0x01);
    delay(2000);
    Lcd_Write_String("TEMP:-");
    Lcd_Write_String("Upload after:");
    sec=0;
    

    while(1)
    {
        GO=1;
        while(GO==1);
        adc_val=((ADRESH<<8)+ADRESL)*4.88; //Calc. Temp from ADC port
        //command(0x87);
        Lcd_Write_Char((adc_val/1000)+48);
        Lcd_Write_Char(((adc_val%1000)/100)+48);
        Lcd_Write_Char(((adc_val%100)/10)+48);
        Lcd_Write_Char('.');
        Lcd_Write_Char((adc_val%10)+48);
        Lcd_Write_Char('C');
        adc_val=adc_val/10;
        delay(20000);
        delay1sec();

        //command(0xce);
        Lcd_Write_Char((30-sec)/10+48);
        Lcd_Write_Char(((30-sec)%10)+48);


        if(sec==30)
        {
            //command(0x01);
            delay(1000);
            delay(60000);
            Lcd_Write_String("Uploading...");
            clearVAL();
            value[0]='\0';
            strcat(value,"AT+CIPSTART=4,\"TCP\",\"184.106.153.149\",80");//IP link to thingspeak.com
            transmit_string(&value);
            sec=0;
            delay(60000);
            delay(60000);
            delay(60000);
            delay(60000);
            while(1)
            {
                x=strstr(&value,"OK");
                if(x-32<0)
                {
                    Lcd_Write_String("Error");
                    flag=0;
                    break;
                }
                else
                {
                    Lcd_Write_String("OK6  ");
                    flag=1;
                    break;
                }
            }
            delay(10000);


            if(flag==1)
            {
                clearVAL();
                value[0]='\0';
                strcat(value,"AT+CIPSEND=4,46");//Send No. of character
                transmit_string(&value);
                delay(60000);
                delay(60000);
                delay(60000);

                while(1)
                {
                    x=strstr(&value,">");
                    if(x-32<0)
                    {
                        Lcd_Write_String("ERROR");
                        flag=0;
                        break;
                    }
                    else
                    {
                        Lcd_Write_String("OK7   ");
                        flag=1;
                        break;
                    }
                }
                delay(60000);
                delay(60000);
                if(flag==1)
                {
                    clearVAL();
                    value[0]='\0';
                    Lcd_Write_String("GET DATA");
                    strcat(value,"GET /update?key=FQHTFYSPY3K8LML7&field1="); //UPDATE CHANNEL using API
                    transmit2(&value);
                    Lcd_Write_Char('1');
                    transmit((adc_val/1000)+48);
                    Lcd_Write_Char('1');
                    transmit(((adc_val%1000)/100)+48);
                    Lcd_Write_Char('1');
                    transmit(((adc_val%100)/10)+48);
                    Lcd_Write_Char('1');
                    transmit((adc_val%10)+48);
                    Lcd_Write_Char('1');
                    transmit(0x0d);
                    transmit(0x0a);
                    delay(40000);
                    Lcd_Write_Char('1');
                    delay(10000);


                    //command(0x01);
                    delay(2000);
                    Lcd_Write_String("CIPLCOSE");
                    clearVAL();   //AT+CIPCLOSE=0
                    value[0]='\0';
                    delay(3000);
                    strcat(value,"AT+CIPCLOSE");//close channel
                    transmit_string(&value);
                    //command(0x01);
                    delay(1000);

                }
            }
            //command(0x01);
            delay(1000);
            Lcd_Write_String("TEMP:-");
            Lcd_Write_String("Upload after:");
            sec=0;

        }
    }


}






