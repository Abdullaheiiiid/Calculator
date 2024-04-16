#include "bit.h"
#include "typedef.h"
#include "DIO_interface.h"
#include "LCD_config.h"
#include "LCD_interface.h"
#include <stdio.h>
#include <util/delay.h>

int LOC=0;
//SEND COMMAN FUNCTION
void LCD_VidSendCommand( u8 Copy_u8Command){

#if LCD_MODE == 8

	//RW LOW  -->  WRITE ON LCD
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,Pin_Low);

	//RS LOW  -->  SEND COMMAND
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,Pin_Low);

	//SET CONTROL PORT
	DIO_VidSetPortValue(LCD_DATA_PORT,Copy_u8Command);

	//E HIGH  -->  ENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_High);

	_delay_ms(2);

	//E LOW  -->  UNENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_Low);

#elif LCD_MODE == 4

	/* SEND 4 MSBs */
	DIO_VidSetMSB(LCD_DATA_PORT,Copy_u8Command);

	//RW LOW  -->  WRITE ON LCD
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,Pin_Low);

	//RS LOW  -->  SEND COMMAND
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,Pin_Low);

	//E HIGH  -->  ENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_High);

	_delay_ms(2);

	//E LOW  -->  UNENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_Low);

	                //--------------------------//

	/* SEND 4 LSBs */
	DIO_VidSetLSB(LCD_DATA_PORT,Copy_u8Command);

	//E HIGH  -->  ENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_High);

	_delay_ms(2);

	//E LOW  -->  UNENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_Low);

#endif

}


//SEND DATA FUNCTION
void LCD_VidSendData( u8 Copy_u8Data){

#if LCD_MODE == 8



	//RW LOW  -->  WRITE ON LCD
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,Pin_Low);

	//RS LOW  -->  SEND DATA
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,Pin_High);

	//SET CONTROL PORT
	DIO_VidSetPortValue(LCD_DATA_PORT,Copy_u8Data);

	//E HIGH  -->  ENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_High);

	_delay_ms(2);

	//E LOW  -->  UNENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_Low);

#elif LCD_MODE == 4



	/* SEND 4 MSBs */
	DIO_VidSetMSB(LCD_DATA_PORT,Copy_u8Data);

	//RW LOW  -->  WRITE ON LCD
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,Pin_Low);

	//RS HIGH  -->  SEND DATA
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,Pin_High);

	//E HIGH  -->  ENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_High);

	_delay_ms(2);

	//E LOW  -->  UNENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_Low);

	                //--------------------------//

	/* SEND 4 LSBs */
	DIO_VidSetLSB(LCD_DATA_PORT,Copy_u8Data);

	//E HIGH  -->  ENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_High);

	_delay_ms(2);

	//E LOW  -->  UNENABLE
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,Pin_Low);

#endif

}


//INITIALIZATION FUNCTION
void LCD_VidInit(){

#if LCD_MODE == 8

	//SET PIN RS DIRECTION TO BE OUTPUT
	DIO_VidSetPinDirection(LCD_CTRL_PORT,LCD_RW_PIN,Output);

	//SET PIN RS DIRECTION TO BE OUTPUT
	DIO_VidSetPinDirection(LCD_CTRL_PORT,LCD_RS_PIN,Output);

	//SET PIN E DIRECTION TO BE OUTPUT
	DIO_VidSetPinDirection(LCD_CTRL_PORT,LCD_E_PIN,Output);

	//SET PORT A DIRECTION TO BE OUTPUT
	DIO_VidSetPortDirection(LCD_DATA_PORT,Output);

	_delay_ms(40);

	//FUNCTION SET COMMAND: 8bit mode 2 LINES, 5*8 FONT SIZE
	LCD_VidSendCommand(LCD_EIGHT_BIT_MODE_TWO_LINES);

	//DISPLAY ON OFF CONTROL: DISPLAY ENABLE, DISPLAY CURSOR, ON BLINK CURSOR
	LCD_VidSendCommand(LCD_CURSOR_OFF_BLINK);

	//CLEAR DISPLAY
	LCD_VidSendCommand(LCD_CLEAR);

#elif LCD_MODE == 4

	//SET PIN RS DIRECTION TO BE OUTPUT
	DIO_VidSetPinDirection(LCD_CTRL_PORT,LCD_RW_PIN,Output);

	//SET PIN RS DIRECTION TO BE OUTPUT
	DIO_VidSetPinDirection(LCD_CTRL_PORT,LCD_RS_PIN,Output);

	//SET PIN E DIRECTION TO BE OUTPUT
	DIO_VidSetPinDirection(LCD_CTRL_PORT,LCD_E_PIN,Output);

	//SET MSBs OF PORT A DIRECTION TO BE OUTPUT
	DIO_VidSetPinDirection(LCD_DATA_PORT,Pin4,Output);
	DIO_VidSetPinDirection(LCD_DATA_PORT,Pin5,Output);
	DIO_VidSetPinDirection(LCD_DATA_PORT,Pin6,Output);
	DIO_VidSetPinDirection(LCD_DATA_PORT,Pin7,Output);

	_delay_ms(40);

	//FUNCTION SET COMMAND: 4bot mode
	LCD_VidSendCommand(0x02);

	//FUNCTION SET COMMAND: 4bit mode 2 LINES, 5*8 FONT SIZE
	LCD_VidSendCommand(0x28);

	_delay_ms(40);
	//DISPLAY ON OFF CONTROL: DISPLAY ENABLE, DISPLAY CURSOR, ON BLINK CURSOR
	LCD_VidSendCommand(0x0D);

	_delay_ms(40);
	//CLEAR DISPLAY
	LCD_VidSendCommand(0x01);

#endif
}

//SEND STRING FUNCTION
void LCD_VidSendString(char *Copy_u8Data){
	int Iterator = 0;
	while(Copy_u8Data[Iterator] != '\0'){
		LCD_VidSendData(Copy_u8Data[Iterator]);
		Iterator++;
	}
}

//SET POSITION FUNCTION
void LCD_VidSetPosition(u8 Copy_u8Row, u8 Copy_u8Columm){

	if(Copy_u8Row == LCD_ROW1){
		LOC = Copy_u8Columm;
		LCD_VidSendCommand(0x80+Copy_u8Columm);
	}
	else if(Copy_u8Row == LCD_ROW2){
		LOC = 16+Copy_u8Columm;
		LCD_VidSendCommand(0x80+0x40+Copy_u8Columm);
	}
}

//SEND NUMBER FUNCTION
void LCD_VidSendNumber(int Copy_u8Data){
	char str[16];
	sprintf(str,"%d",Copy_u8Data);
	LCD_VidSendString(str);
}

void LCD_VidClear()
{
	LCD_VidSendCommand(LCD_CLEAR);		/* Clear display */
	_delay_ms(2);
	LCD_VidSendCommand(LCD_FORCE_START_LOCATION);		/* Cursor at home position */
}


