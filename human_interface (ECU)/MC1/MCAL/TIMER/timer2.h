/******************************************************************************
 *
 * Component: TIMER_2
 *
 * File Name: TIMER2.h
 *
 * Description: Header file for the TIMER_2 AVR driver
 *
 * Author:SAYED IBRAHIM
 *
 *******************************************************************************/

#ifndef TIMER2_H_
#define TIMER2_H_


#include "../../LIB/std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum{ TIMER2_NORMAL,TIMER2_CTC }Timer2_Mode;

typedef enum{ TIMER2_N1=1,TIMER2_N8,TIMER2_N32,TIMER2_N64,TIMER2_N128,TIMER2_N256,TIMER2_N1024 }Timer2_Prescale;

typedef enum{ TIMER2_POLL/*polling disable interrupt*/,
		   	  TIMER2_OVF,
			  TIMER2_COMP }Timer2_Interrupt;

typedef struct{
	Timer2_Mode mode;
	Timer2_Prescale prescale;
	Timer2_Interrupt interrupt;
	uint8 OCR;
}Timer2_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void TIMER2_init(const Timer2_ConfigType* Config_Ptr);
void TIMER2_setCallBack(void(*a_ptr)(void));
void TIMER2_delay_ms(uint16 msec);
void TIMER2_deInit();

#endif /* TIMER2_H_ */
