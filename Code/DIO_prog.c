#include "typedef.h"
#include "bit.h"
#include "DIO_Private.h"
#include "DIO_interface.h"

#define SET_BIT(reg, bit)    ((reg) |= (1 << (bit)))
#define GET_BIT(reg, bit)    (((reg) >> (bit)) & 1)
#define TOGGLE_BIT(reg, bit) ((reg) ^= (1 << (bit)))
#define CLEAR_BIT(reg, bit)  ((reg) &= ~(1 << (bit)))

void DIO_VidSetPinDirection(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Direction)
{
    volatile u8 *ddr_reg;

    switch (Copy_u8Port) {
        case Port_A:
            ddr_reg = &DDRA;
            break;
        case Port_B:
            ddr_reg = &DDRB;
            break;
        case Port_C:
            ddr_reg = &DDRC;
            break;
        case Port_D:
            ddr_reg = &DDRD;
            break;
        default:
            return;
    }

    if (Copy_u8Direction == Input) {
    	CLEARBIT(*ddr_reg, Copy_u8Pin);
    } else {
    	SETBIT(*ddr_reg, Copy_u8Pin);
    }
}


void DIO_VidSetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Value)
{
    volatile u8 *port_reg;

    switch (Copy_u8Port) {
        case Port_A:
            port_reg = &PORTA;
            break;
        case Port_B:
            port_reg = &PORTB;
            break;
        case Port_C:
            port_reg = &PORTC;
            break;
        case Port_D:
            port_reg = &PORTD;
            break;
        default:
            return;
    }

    if (Copy_u8Value == Pin_High) {
        SETBIT(*port_reg, Copy_u8Pin);
    } else {
        CLEARBIT(*port_reg, Copy_u8Pin);
    }
}

void DIO_VidGetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin , u8 * pu8Data)
{
    volatile u8 *pin_reg;

    switch (Copy_u8Port) {
        case Port_A:
            pin_reg = &PINA;
            break;
        case Port_B:
            pin_reg = &PINB;
            break;
        case Port_C:
            pin_reg = &PINC;
            break;
        case Port_D:
            pin_reg = &PIND;
            break;
        default:
            return;
    }

    *pu8Data = GET_BIT(*pin_reg, Copy_u8Pin);
}

void DIO_VidSetPortDirection(u8 Copy_u8Port , u8 Copy_u8Direction)
{
	    volatile u8 *ddr_reg;

	    switch (Copy_u8Port) {
	        case Port_A:
	            ddr_reg = &DDRA;
	            break;
	        case Port_B:
	            ddr_reg = &DDRB;
	            break;
	        case Port_C:
	            ddr_reg = &DDRC;
	            break;
	        case Port_D:
	            ddr_reg = &DDRD;
	            break;
	        default:
	            return;
	    }

	    if (Copy_u8Direction == Input) {
	        *ddr_reg = 0x00;
	    } else {
	        *ddr_reg = 0xff;
	    }
}

void DIO_VidSetPortValue(u8 Copy_u8Port , u8 Copy_u8Value)
{
	switch (Copy_u8Port) {
	        case Port_A:
	            PORTA = Copy_u8Value;
	            break;
	        case Port_B:
	            PORTB = Copy_u8Value;
	            break;
	        case Port_C:
	            PORTC = Copy_u8Value;
	            break;
	        case Port_D:
	            PORTD = Copy_u8Value;
	            break;
	        default:
	            return;
	    }
}


void DIO_VidGetPortValue(u8 Copy_u8Port , u8 * pu8Data)
{
	switch(Copy_u8Port)
	{
		case Port_A : 
			*pu8Data = PINA;
			break ;

		case Port_B : 
			*pu8Data = PINB;
			break ;

		case Port_C : 
			*pu8Data = PINC;
			break ;

		case Port_D : 
			*pu8Data = PIND;
			break ;
	}
}


void DIO_VidSetMSB(u8 Copy_u8Port , u8 Copy_u8Value){
	switch(Copy_u8Port)
	{
		case Port_A :
			PORTA = (PORTA & 0x0F) | (Copy_u8Value & 0xF0);
			break ;

		case Port_B :
			PORTB = (PORTB & 0x0F) | (Copy_u8Value & 0xF0);
			break ;

		case Port_C :
			PORTC = (PORTC & 0x0F) | (Copy_u8Value & 0xF0);
			break ;

		case Port_D :
			PORTD = (PORTD & 0x0F) | (Copy_u8Value & 0xF0);
			break ;
	}
}


void DIO_VidSetLSB(u8 Copy_u8Port , u8 Copy_u8Value){
	switch(Copy_u8Port)
	{
		case Port_A :
			PORTA = (PORTA & 0x0F) | (Copy_u8Value << 4);
			break ;

		case Port_B :
			PORTB = (PORTB & 0x0F) | (Copy_u8Value << 4);
			break ;

		case Port_C :
			PORTC = (PORTC & 0x0F) | (Copy_u8Value << 4);
			break ;

		case Port_D :
			PORTD = (PORTD & 0x0F) | (Copy_u8Value << 4);
			break ;
	}
}












