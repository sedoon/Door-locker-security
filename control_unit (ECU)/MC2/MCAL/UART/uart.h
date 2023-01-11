 /******************************************************************************
 *
 * Component: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author:SAYED IBRAHIM
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "../../LIB/std_types.h"


/* enum for DataSize parameter in UART_ConfigType structure*/
typedef enum {  FIVE_BIT , SIX_BIT , SEVEN_BIT , EIGHT_BIT ,
	RESERVED1 , RESERVED2 , RESERVED3 , NINE_BIT  }UART_NumOfBits;
/*  enum for Parity parameter in UART_ConfigType structure   */
typedef enum {	DISABLED,NON,EVEN,ODD  }UART_ParityMode;
/*  enum for StopBits parameter in UART_ConfigType structure */
typedef enum {  ONE_BIT,TWO_BIT }UART_StopBitSelect;
/* enum for baud rate parameter in UART_ConfigType structure*/

typedef struct
{
	uint32              baudRate;
	UART_ParityMode     parityMode;
	UART_StopBitSelect  stopBit;
	UART_NumOfBits 		dataSize;

}UART_ConfigType;




/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
