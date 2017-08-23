/*
 * File name LCD.c
 * Created: 05/05/2017 11:44:44 AM
 * Author : Etiq Technologies
   Description:The source code includes functions for the complete data write operations in a 16x2 alpha numeric LCD with ATmega32.
   
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define DATA	PORTD
#define CONTROL	PORTC

#define DATADIR	DDRD
#define CONTROLDIR	DDRC

#define ENABLE		PORTC |= 0x01  			/* SET PORTC FIRST BIT for ENABLE  */
#define DISABLE		PORTC &= 0xFE			/* CLEAR PORTC FIRST BIT for DISABLE */

#define RW_SET		PORTC |= 0x02   		/* SET PORTC SECOND BIT for RW */
#define RW_CLEAR	PORTC &= 0xFD   		/* CLEAR PORTC SECOND BIT for RW */

#define RS_SET		PORTC |= 0x04   		/* SET PORTC THIRD BIT for RS */
#define RS_CLEAR	PORTC &= 0xFB   		/* CLEAR PORTC THIRD BIT for RS */

void CMD(unsigned char cmd)
{                             
        DATA = cmd;							// Write command to data port
	RW_CLEAR;							// Set the control signals
        RS_CLEAR;
    	_delay_ms(10);						
        ENABLE;								// Clock the command in
        _delay_ms(10);						// Small delay for sending the command
        DISABLE;
	RS_CLEAR;
        _delay_ms(10);
        return;
}

void CharData(char data)
{											// 8-bit interface for writing characters
	DATA = data;							// Write data to port
	RS_SET;									// Set control bits
	RW_CLEAR;
	_delay_ms(10);
	ENABLE;									// Clock data into LCD
	_delay_ms(10);							//Small delay for sending the data
	DISABLE;								// Reset control bits
	RS_CLEAR;
	return;
	}

void StringData(char *data)
{				                            // 8-bit interface for writing strings
    int i;
    while(*data!='\0')
    {
        DATA = *data;		               // Write data to port
        RS_SET;							   // Set control bits
        RW_CLEAR;
	    _delay_ms(10);
        ENABLE;							   // Clock data into LCD
        _delay_ms(10);					   //Small delay for sending the data
        DISABLE;						   // Reset control bits
        RS_CLEAR;  
        data++;                         
    }
    return;
}

void lcd_init()
{
	DATADIR = 0xFF;			//OUTPUT MODE
	CONTROLDIR = 0xFF;		//OUTPUT MODE

	CMD(0x80);
	CMD(0x38);
	CMD(0x01);
	CMD(0x0E);

}
