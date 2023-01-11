/******************************************************************************
 *
 * Component: TIMER_0
 *
 * File Name: TIMER_0.c
 *
 * Description: Source file for the TIMER_0 AVR driver
 *
 * Author: SAYED IBRAHIM
 *
 *******************************************************************************/
#include "timer0.h"

#include <avr/io.h> /* To use Timer0,1,2 Registers */
#include <avr/interrupt.h> /* For TIMERS ISR */

#include "../../LIB/common_macros.h" /* To use the macros like SET_BIT */


static volatile void (*g_callBackPtr)(void) = NULL_PTR;/*this global function created
for the set_call_back function cause the pointer is local to the function */

ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

void TIMER0_init(const Timer0_ConfigType* Config_Ptr)
{
	TCNT0 = 0;
	switch(Config_Ptr->mode)
	{
	case TIMER0_NORMAL:
		TCCR0 = (1<<FOC0) | (0x07 & Config_Ptr->prescale);
		break;
	case TIMER0_CTC:
		TCCR0 = (1<<FOC0) | (1<<WGM01) | (0x07 & Config_Ptr->prescale);
		OCR0  = Config_Ptr->OCR;
		break;
	}
	/* enable interrupts */
	switch(Config_Ptr->interrupt)
	{
	case TIMER0_OVF:
		TIMSK |= (1<<TOIE0);
		break;
	case TIMER0_COMP:
		TIMSK |= (1<<OCIE0);
		break;
	case TIMER0_POLL:
		TIMSK &= 0xFc;/*1111 1100 polling disable interrupt*/
		break;
	}



}

void TIMER0_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}

void TIMER0_delayMS(uint16 msec)/*timer0 delay*/
{
	Timer0_ConfigType config = {TIMER0_CTC,TIMER0_N8,TIMER0_POLL,249};/*initial value 250 = 0 -->249*/
	uint32 n = msec*1000UL/250;
	uint32 i;
	TIMER0_init(&config);
	for(i=0;i<n;i++)
	{
		while(BIT_IS_CLEAR(TIFR,OCF0));/*polling when flag is 1 break the loop*/
		SET_BIT(TIFR,OCF0);/*clear the flag cause the polling not like interrupt the hard ware MC clear it */
	}
	TIMER0_DeInit(); /* disable timer*/
}

void TIMER0_DeInit()
{
	TCNT0 = 0;
	TCCR0 = 0;
	TIMSK &= 0b11111100;
}
