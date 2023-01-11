
/******************************************************************************
 * Component: GIE
 *
 * File Name: GIE.h
 *
 * Description: Source file for the ATmega16 global interrupt enable driver
 *
 * Author:SAYED IBRAHIM
 *
 *******************************************************************************/
#include "GIE.h"

#include "avr/io.h"
#include "../../LIB/common_macros.h"


void GIE_Enable(void)
{
	SET_BIT(SREG,SREG_I);
}

void GIE_Disable(void)
{
	CLEAR_BIT(SREG,SREG_I);
}
