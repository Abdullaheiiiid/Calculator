/*
 * main.c
 *
 *  Created on: ٢١‏/٠٨‏/٢٠٢٣
 *      Author: abdul
 */
#include "typedef.h"
#include "bit.h"
#include "DIO_Private.h"
#include "DIO_interface.h"
#include "LCD_config.h"
#include "LCD_interface.h"
#include "KPD_interface.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	LCD_VidInit();
	KPD_VidInit();
	 int value;
	 char valprev[20];
	 u8 op;
	 int result;
	 while (1){
	    value = KPD_VidGetPressedKey();
	    while (value == 0xFF){
	      value = KPD_VidGetPressedKey();
	    }

	    if(value == '+' || value == '-' || value == '*' || value == '/' || value == '%'){
	      result = atoi(valprev);
	      strcpy(valprev,"");
	      LCD_VidSendData(' ');
	      LCD_VidSendData(value);
	      LCD_VidSendData(' ');
	      op = value;
	    }else{
	    	if(value == '='){
	    		int var = atoi(valprev);
	    		if(op == '+'){
	    			LCD_VidSendData(' ');
	    			LCD_VidSendData('=');
	    			LCD_VidSendData(' ');
	    			int x = result + var;
	    			LCD_VidSendNumber(x);
	    			_delay_ms(500);
	    			LCD_VidSendCommand(LCD_CLEAR);
	    		}
	    		if(op == '-'){
	    			LCD_VidSendData(' ');
	    			LCD_VidSendData('=');
	    			LCD_VidSendData(' ');
	    			int x = result - var;
	    			LCD_VidSendNumber(x);
	    			_delay_ms(500);
	    			LCD_VidSendCommand(LCD_CLEAR);
	    		}
	    		if(op == '*'){
	    			LCD_VidSendData(' ');
	    			LCD_VidSendData('=');
	    			LCD_VidSendData(' ');
	    			int x = result * var;
	    			LCD_VidSendNumber(x);
	    			_delay_ms(500);
	    			LCD_VidSendCommand(LCD_CLEAR);
	    		}
	    		if(op == '/'){
	    			LCD_VidSendData(' ');
	    			LCD_VidSendData('=');
	    			LCD_VidSendData(' ');
	    			int x = result / var;
	    			LCD_VidSendNumber(x);
	    			_delay_ms(500);
	    			LCD_VidSendCommand(LCD_CLEAR);
	    		}
	    		if(op == '%'){
	    			LCD_VidSendData(' ');
	    			LCD_VidSendData('=');
	    			LCD_VidSendData(' ');
	    			int x = result % var;
	    			LCD_VidSendNumber(x);
	    			_delay_ms(500);
	    			LCD_VidSendCommand(LCD_CLEAR);
	    		}
	    		result = 0;
	    	    var = 0;
	    	    strcpy(valprev,"");
	    	}
	    	else{
	    		char c = value +'0';
	    		strncat(valprev, &c, 1);
	    		LCD_VidSendNumber(value);
	    	}
	    }
	    //LCD_moveCursor(0, 0);
	  }
	return 0;
}

