
/******************************************************************************
 *
 * Component: BUZZER
 *
 * File Name: buzzer.h
 *
 * Description: header file for the BUZZER driver
 *
 * Author: SAYED IBRAHIM
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

#include "../../LIB/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT_ID                 PORTA_ID
#define BUZZER_PIN_ID                  PIN0_ID


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * Setup Buzzer configuration.
 */
void Buzzer_init(void);

/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or
 * stop the motor based on the state input state value
 */
void Buzzer_on(void);

void Buzzer_off(void);


#endif /*BUZZER_H_ */
