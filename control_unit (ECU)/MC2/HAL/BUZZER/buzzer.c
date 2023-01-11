
/******************************************************************************
 *
 * Component: BUZZER
 *
 * File Name: buzzer.h
 *
 * Description: source file for the BUZZER driver
 *
 * Author: SAYED IBRAHIM
 *
 *******************************************************************************/

#include "buzzer.h"

#include "../../MCAL/GPIO/gpio.h"

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * Setup Buzzer configuration.
 */
void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}


void Buzzer_on(void)
{

	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);
}

void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}

