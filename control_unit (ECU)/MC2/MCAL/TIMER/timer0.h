/******************************************************************************
 *
 * Component: TIMER_0
 *
 * File Name: TIMER0.h
 *
 * Description: Header file for the TIMER_0 AVR driver
 *
 * Author:SAYED IBRAHIM
 *
 *******************************************************************************/

#ifndef TIMER0_H_
#define TIMER0_H_


#include "../../LIB/std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum{ TIMER0_NORMAL,TIMER0_CTC  }Timer0_Mode;

typedef enum{ TIMER0_N1 = 1,TIMER0_N8,TIMER0_N64,TIMER0_N256,TIMER0_N1024}Timer0_Prescale;

typedef enum{ TIMER0_POLL,/*polling disable interrupt*/
			  TIMER0_OVF,
			  TIMER0_COMP }Timer0_Interrupt;

typedef struct{
	Timer0_Mode mode;
	Timer0_Prescale prescale;
	Timer0_Interrupt interrupt;
	uint8 OCR;
}Timer0_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void TIMER0_init(const Timer0_ConfigType* Config_Ptr);
void TIMER0_setCallBack(void(*a_ptr)(void));
void TIMER0_delayMS(uint16 msec);
void TIMER0_DeInit();

#endif /* TIMER0_H_ */
