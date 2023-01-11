
/******************************************************************************
 *
 * Component: TIMER_2
 *
 * File Name: TIMER2.c
 *
 * Description: Source file for the TIMER_2 AVR driver
 *
 * Author: SAYED IBRAHIM
 *
 *******************************************************************************/
#include "timer2.h"

#include <avr/io.h> /* To use Timer0,1,2 Registers */
#include <avr/interrupt.h> /* For TIMERS ISR */

#include "../../LIB/common_macros.h" /* To use the macros like SET_BIT */


static volatile void (*g_callBackPtr)(void) = NULL_PTR;/*this global function created
for the set_call_back function cause the pointer is local to the function */

ISR(TIMER2_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER2_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

void TIMER2_init(const Timer2_ConfigType* Config_Ptr)
{
	TCNT2 = 0;
	switch(Config_Ptr->mode)
	{
	case TIMER2_NORMAL:
		TCCR2 = (1<<FOC2) | (0x07 & Config_Ptr->prescale);
		break;
	case TIMER2_CTC:
		TCCR2 = (1<<FOC2) | (1<<WGM21) | (0x07 & Config_Ptr->prescale);
		OCR2  = Config_Ptr->OCR;
		break;
	}
	/* enable interrupts */
	switch(Config_Ptr->interrupt)
	{
	case TIMER2_OVF:
		TIMSK |= (1<<TOIE2);
		break;
	case TIMER2_COMP:
		TIMSK |= (1<<OCIE2);
		break;
	case TIMER2_POLL:
		TIMSK &= 0x3F;/* 0b 0011 1111  polling disable interrupt*/
		break;
	}



}

void TIMER2_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}

void TIMER2_delay_ms(uint16 msec)/*timer2 delay*/
{
	Timer2_ConfigType config = {TIMER2_CTC,TIMER2_N8,TIMER2_POLL,249};/*initial value 250 = 0 -->249*/
	uint32 n = msec*1000UL/250;
	uint32 i;
	TIMER2_init(&config);
	for(i=0;i<n;i++)
	{
		while(BIT_IS_CLEAR(TIFR,OCF2));/*polling when flag is 1 break the loop*/
		SET_BIT(TIFR,OCF2);SET_BIT(TIFR,OCF0);
		/*clear the flag cause the polling not like interrupt the hard ware MC clear it */
	}
	TIMER2_deInit();/* disable timer*/
}

void TIMER2_deInit()
{
	TCNT2 = 0;
	TCCR2 = 0;
	TIMSK &= 0b00111111;
}

