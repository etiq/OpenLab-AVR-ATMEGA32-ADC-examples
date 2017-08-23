/*
 * File Name  :ADC.c
 *
 * Created    : 3/25/2016 10:32:17 AM
 * Author     : Etiq technologies
 * Description: The Project is intended to create a sample code for converting an analog voltage signal into digital using
                the 10 bit resolution ADC of ATmega32 microcontroller.An analog voltage signal say a sensor output is connected
				to the ADC0 channel and its corresponding digital output is obtained and displays on an LCD.ADC interrupt is not 
				implemented.Certain portions of the code are commented which enables the user to use the interrupt feature by 
				uncommenting it.
 */ 

//#ifdef F_CPU              //defines the CPU clock to be 8 MHz
//#define F_CPU 16000000UL
//#endif // F_CPU

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"                               //lcd header file

void delay_max(int k)
{
	for(int i=0; i<k; i++){
		for(int j=0; j<10; j++)
			_delay_ms(250);
	}
}
/*************************************Result Display Function************************************/

void result_string(unsigned int result)        // out put the adc result to lcd
{
unsigned char string[4];
unsigned char b;
signed char i=0;

do 
{
	string[i]=(result%10)+48;		
	result=result/10;
	i++;
} while (result);                            //conversion of the result  into string
                     

_delay_ms(100);

i = 3;
while (i>=0)                                 //output the string  to LCD
{
	if((string[i]>'9') || (string[i]<'0'))			//Check whether the converted characters are garbage values or not
		string[i] = '0';
		
	CharData(string[i]);
	i--;
}
	
}

/*****************************uncomment if interrupt is used********************************/

/* ISR(ADC_vect)                          
{
unsigned int resultH,resultL,result=0;

ADCSRA|=(1<<ADIF);


resultL=ADCL;                          // obtain the result
resultH=ADCH;
result|=(resultH<<8);
result|=resultL;


result_string(result);                //function call to output the result
	
resultL=0;
resultH=0;
result=0;
} */
/******************************main*********************************/


int main(void)
{
	unsigned int resultH,resultL,result=0;
	
	lcd_init();
	ADMUX= 0x40;	//ADC0 single input selected.Reference signal to be AVCC with external capacitor connected to AREF pin

	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);           // ADC enable, Prescalar select Division Factor 64
	
	
	//ADCSRA|=(1<<ADIE);  sei();                       /*uncomment if interrupt used*/
	
	CMD(0x80);
	StringData("ADC CONV.");
	
						  
	while (1) 
    {
	resultL=0;
	resultH=0;
	result=0;   
	
    ADCSRA|=(1<<ADSC);                                 //start conversion
	while(!(ADCSRA&(1<<ADSC)));                         // wait until conversion
	
	//ADCSRA&=0xEF;                                    //clear the ADIF flag
	ADCSRA|=(1<<ADIF);
	resultL=ADCL;                                       // obtain the result
	resultH=ADCH;
	result|=(resultH<<8);
	result|=resultL;
	
	CMD(0xC0);
	result_string(result);                //function call to output the result
	delay_max(1);
}
}

