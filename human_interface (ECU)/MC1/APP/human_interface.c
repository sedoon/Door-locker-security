
//#include <util/delay.h>
/*
 ============================================================================
 Name        : APPICATION.c
 Author      : SAYED IBRAHIM
 Description : Door locker security System --> Human interface using keypad & LCD
 Date        : 28/04/2022
 ============================================================================
 */

#include "../HAL/KEYPAD/keypad.h"
#include "../HAL/LCD/lcd.h"
#include "../MCAL/UART/uart.h"
#include "../MCAL/TIMER/timer2.h"


#define  PW_SIZE 	              4/*size password in array*/

#define  CONTROL_UINT_READY 	 'R' /*this symbol define receive byte from
										control unit M.c have the same value*/
#define  FIRST_TIME              'F' /*enter first time  Your New Password*/
#define  SECOND_TIME       		 'S' /*Confirm Your New Password*/
#define  TRY_AGAIN         		 'T'
#define  OPERATION_MODE     	 'M'
#define  ERROR_ALARM       		 'E'
#define  PW_SET                  'I'  /*save password*/
#define  OPEN_DOOR               'O'
#define  CHANGE_PW               'P'
#define  CORRECT_PW              'C'


uint8 recievedByte;


uint8  readKey()
{
	uint8 pressedKey=0;

	pressedKey=KEYPAD_getPressedKey() ;
	TIMER2_delay_ms(70);
	LCD_displayCharacter('*');
	TIMER2_delay_ms(400);   /* delay function  */

	return pressedKey;
}


void changePW()
{

	uint8 ChangePW [PW_SIZE];
	LCD_clearScreen();
	LCD_displayString("Your Current PW");
	LCD_moveCursor(1,0);
	LCD_displayString("PW:");

	for(int i=0;i<PW_SIZE;i++)
	{
		TIMER2_delay_ms(400);/*delay to call readkey function*/
		/*current PW*/
		ChangePW[i] =readKey();
		UART_sendByte(ChangePW[i]);
	}

	recievedByte=UART_recieveByte();

	if(	recievedByte == CORRECT_PW)
	{
		LCD_clearScreen();
		LCD_displayString("Enter New PW");
		LCD_moveCursor(1,0);
		LCD_displayString("PW:");
		/*send first new PW*/
		for(int i=0;i<PW_SIZE;i++)
		{
			ChangePW[i] =readKey();
			UART_sendByte(ChangePW[i]);
		}
		LCD_clearScreen();
		LCD_displayString("Confirm New PW");
		LCD_moveCursor(1,0);
		LCD_displayString("PW:");

		/*send second new PW*/
		for(int i=0;i<PW_SIZE;i++)
		{
			ChangePW[i] =readKey();
			UART_sendByte(ChangePW[i]);
		}

		recievedByte=UART_recieveByte();

		if(recievedByte == CHANGE_PW)
		{
			LCD_clearScreen();
			LCD_displayString("PW has been");
			LCD_moveCursor(1,0);
			LCD_displayString("Changed");
			TIMER2_delay_ms(1500);
		}
		else
		{
			recievedByte = TRY_AGAIN;
			TIMER2_delay_ms(500);
		}
	}
	else
	{
		recievedByte = TRY_AGAIN;
		TIMER2_delay_ms(500);
	}
}



void optionsMenue()
{
	LCD_clearScreen();
	LCD_displayString("+ Open the Door");
	LCD_moveCursor(1,0);
	LCD_displayString("- Change the Pin");

	switch (KEYPAD_getPressedKey())
	{
		case('+'):

			LCD_clearScreen();
			/*send UART message motor to control unit to take action*/
			UART_sendByte(OPEN_DOOR);
			LCD_displayString("Opening the Door");

			TIMER2_delay_ms(3500);
			LCD_clearScreen();
			LCD_displayString("Closing the Door");

		break;
		case('-'):

			UART_sendByte(CHANGE_PW);
			changePW();
		break;

		default:
		break;
	}
}



int main(void)
{

	UART_ConfigType config = {9600,DISABLED,ONE_BIT,EIGHT_BIT};
	UART_init(&config); /* Initialize the UART driver  */

	LCD_init();			/* Initialize the LCD driver  */


	do{
		recievedByte = UART_recieveByte();
		/* Wait until MC2 is ready to receive the string
		 *  because the receive buffer is one byte
		 *  (Polling)so wait to avoid Over right in string */
	  }while(recievedByte != CONTROL_UINT_READY);


	while (1)
	{

		recievedByte = UART_recieveByte();/* Receive Byte from MC2 */
		/*** First time  enter password ***/
		if (recievedByte == FIRST_TIME )
		{
			LCD_displayString("     Welcome");
			TIMER2_delay_ms(1500);
			LCD_clearScreen();
			LCD_displayString("Enter PW");
			LCD_moveCursor(1,0);
			LCD_displayString("PW:");

			for(int i=0;i<PW_SIZE;i++)  /* Re-send the received byte to Terminal2 */
			{
				UART_sendByte(readKey());
			}
			recievedByte = UART_recieveByte();/* Second time re-enter password to confirm  */
			if (recievedByte == SECOND_TIME )
			{
				LCD_clearScreen();
				LCD_displayString("Re-enter PW");
				LCD_moveCursor(1,0);
				LCD_displayString("PW:");

				for(int i=0;i<PW_SIZE;i++)
				{
					UART_sendByte(readKey());
				}
				recievedByte = UART_recieveByte();/**  password saved **/
				if (recievedByte == PW_SET)
				{
					LCD_clearScreen();
					LCD_displayString(" PW Saved");
					TIMER2_delay_ms(1500);/*delay 500msec*/
				}
				else
				{
					recievedByte = TRY_AGAIN;
				}
			}
			else
			{
				recievedByte = TRY_AGAIN;
			}
	      }
		else if (recievedByte == OPERATION_MODE)	/************ OPERATION MODE *********/
		{

			LCD_clearScreen();
			LCD_displayString("Enter the PW");
			LCD_moveCursor(1,0);
			LCD_displayString("PW:");

			for(int i=0;i<PW_SIZE;i++)
			{
				UART_sendByte(readKey());
			}
			recievedByte = UART_recieveByte();
			if(recievedByte == CORRECT_PW)
			{
				optionsMenue();
			}
			else if (recievedByte == ERROR_ALARM  )
			{
				LCD_clearScreen();
				LCD_displayString("Sorry,warning ");
				LCD_moveCursor(1,0);
				LCD_displayString("Wait 5 Minutes");
				TIMER2_delay_ms(5000);
			}
			if(recievedByte == TRY_AGAIN)
			{
				LCD_clearScreen();
				LCD_displayString("Try again!");
				TIMER2_delay_ms(700);

			}
		}
	}
}
