
//#include <avr/io.h>
/*
 ============================================================================
 Name        : APPICATION.c
 Author      : SAYED IBRAHIM
 Description : Door locker security System --> control unit on the motor ,buzzer & EEEPROM
 Date        : 28/04/2022
 ============================================================================
 */
#include "../HAL/BUZZER/buzzer.h"
#include "../HAL/DC_MOTOR/dc_motor.h"
#include "../HAL/EEPROM/external_eeprom.h"
#include "../MCAL/TWI/twi.h"
#include "../MCAL/UART/uart.h"
#include "../MCAL/TIMER/timer2.h"
#include "../MCAL/GIE/GIE.h"



#define  PW_SIZE 	              4

#define  DEFAULT_BYTE            0xFF/*default password*/

/*this liters for synchronization*/
#define  CONTROL_UINT_READY 	 'R'

#define  FIRST_TIME        		 'F'
#define  SECOND_TIME       		 'S'
#define  TRY_AGAIN         		 'T'
#define  OPERATION_MODE    		 'M'
#define  ERROR_ALARM       		 'E'
#define  PW_SET                  'I'
#define  OPEN_DOOR               'O'
#define  CHANGE_PW               'P'
#define  CORRECT_PW              'C'


int main(void)
{
	uint8 errorCounter=0,firstTime=0,pwMatched=0 ,takeAction;

	uint8 savedPW  [PW_SIZE];
	uint8 firstPW  [PW_SIZE];
	uint8 confirmPW[PW_SIZE];

	UART_ConfigType config = {9600,DISABLED,ONE_BIT,EIGHT_BIT};
	UART_init(&config);/* Initialize the UART driver  */

	Buzzer_init(); /* Initialize the buzzer driver  */
	DcMotor_Init();/* Initialize the motor driver  */

	GIE_Enable();  /*global interrupt enable*/


	/* Sending Ready State to ECU1 */
	TIMER2_delay_ms(20);/* to display work*/
	UART_sendByte(CONTROL_UINT_READY);

	/*First reading Password from EEPROM and stuck reading until to send finished process to another MC
	 *after finishing  they send a message in EEPROM_read to start */
	EEPROM_readArray(0x100,savedPW,PW_SIZE);

	while(1)
	{

		/***** First time *****/
		firstTime = 1;
		for(int i=0;i<PW_SIZE;i++)
		{
			firstTime = firstTime && (savedPW[i] == DEFAULT_BYTE);
		}
		if(firstTime)
		{
			/* receive Entering new Password for first time */
			UART_sendByte(FIRST_TIME);
			for(int i=0;i<PW_SIZE;i++)
			{
				firstPW[i] = UART_recieveByte();
			}
			/* receive Second time re-enter password to confirm*/
			UART_sendByte(SECOND_TIME);
			for(int i=0;i<PW_SIZE;i++)
			{
				confirmPW[i] = UART_recieveByte();
			}
			/* Checking if two Passwords are matched */
			pwMatched = 1;
			for(int i=0;i<PW_SIZE;i++)
			{
				pwMatched = pwMatched && ( firstPW[i] == confirmPW[i] );
			}
			if(pwMatched)
			{
				/* Setting new Password in EEPROM */
				EEPROM_writeArray(0x100,confirmPW,PW_SIZE);
				TIMER2_delay_ms(10);
				/* Reading Password from External EEPROM */
				EEPROM_readArray(0x100,savedPW,PW_SIZE);
				UART_sendByte(PW_SET);
			}
			/* Asking to Try again if not saved PW not equal default PW
			 * and the new PW and confirm the new PW are matched
			 */
			else
			{
				UART_sendByte(TRY_AGAIN);
				TIMER2_delay_ms(2000);
			}
		}
		/* OPERATION MODE ***********************/
		else
		{
			UART_sendByte(OPERATION_MODE);
			//check
			for(int i=0;i<PW_SIZE;i++)
			{
				confirmPW[i] = UART_recieveByte();
			}
			pwMatched = 1;
			for(int i=0;i<PW_SIZE;i++)
			{
				pwMatched = pwMatched && (confirmPW[i] == savedPW[i]);
			}
			if(pwMatched)
			{
				UART_sendByte(CORRECT_PW);
				takeAction = UART_recieveByte(); /*receive the action*/
				if(takeAction == OPEN_DOOR)/*opening the door*/
				{
					DcMotor_Rotate(DC_MOTOR_CLOCKWISE,100);
					TIMER2_delay_ms(1000);
					DcMotor_Rotate(DC_MOTOR_CLOCKWISE,0);

					TIMER2_delay_ms(3000);

					DcMotor_Rotate( DC_MOTOR_ANTI_CLOCKWISE,100);
					TIMER2_delay_ms(1000);
					DcMotor_Rotate(DC_MOTOR_CLOCKWISE,0);

				}
				else if (takeAction == CHANGE_PW)/*change the PW*/
				{
					/*receive current PW*/
					for(int i=0;i<PW_SIZE;i++)
					{
						confirmPW[i] = UART_recieveByte();
					}
					//check
					pwMatched =1;
					for(int i=0;i<PW_SIZE;i++)
					{
						pwMatched = pwMatched && (confirmPW[i] == savedPW[i]);
					}
					//check if current PW is correct
					if(pwMatched == 1)
					{
						UART_sendByte(CORRECT_PW);

						//receive first new PW
						for(int i=0;i<PW_SIZE;i++)
						{
							firstPW[i] = UART_recieveByte();
						}
						//receive second new PW
						for(int i=0;i<PW_SIZE;i++)
						{
							confirmPW[i] = UART_recieveByte();
						}
						//check
						pwMatched =1;
						for(int i=0;i<PW_SIZE;i++)
						{
							pwMatched = pwMatched && (firstPW[i] == confirmPW[i]);
						}
						if(pwMatched )
						{
							EEPROM_writeArray(0x100,confirmPW,PW_SIZE);
							TIMER2_delay_ms(10);
						    EEPROM_readArray(0x100,savedPW,PW_SIZE);
							UART_sendByte(CHANGE_PW);
						}
					}
					else
					{
						UART_sendByte(TRY_AGAIN);
						TIMER2_delay_ms(1000);
					}
				}
			}
			else if (pwMatched == 0 && errorCounter < 2)
			{       /*  true               true   */
				UART_sendByte(TRY_AGAIN);
				errorCounter++;
			}
			else if(pwMatched == 0 && errorCounter == 2 )
			{
				/* turn the buzzer on and display warning message */
				Buzzer_on();
				UART_sendByte(ERROR_ALARM);
				TIMER2_delay_ms(5000);
				Buzzer_off();
				errorCounter =0;
			}
		}
	}
}





