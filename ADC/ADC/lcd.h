/*
 * File name lcd.h
 * Created: 05/05/2017 11:44:44 AM
 * Author : Etiq Technologies   
 */ 

#include <avr/io.h>

/*____________________________LCD command write funtion_____________________________*/
void CMD(unsigned char);
/*
 * Include          :       lcd.h
 * Description      :       Writes command byte to lcd command register
 * Arguments        :       command code
 * Returns          :       None
*/

/*____________________________LCD data write funtion_____________________________*/
void CharData(char);
/*
 * Include          :       lcd.h
 * Description      :       Writes data into the lcd data register
 * Arguments        :       data
 * Returns          :       None
*/

/*____________________________Function to write string at current cursor location_____________________________*/
void StringData(char*);
/*
 * Include          :       lcd.h
 * Description      :       Writes a string at the current cursor position
 * Arguments        :       string
 * Returns          :       None
*/

/*____________________________LCD Initialization funtion_____________________________*/
void lcd_init();
/*
 * Include          :       lcd.h
 * Description      :       Configures and Initializes the LCD.
 * Arguments        :       None
 * Returns          :       None
*/
