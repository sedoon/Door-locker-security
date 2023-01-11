 /******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Source file for the TWI(I2C) AVR driver
 *
 * Author: SAYED IBRAHIM
 *
 *******************************************************************************/
 
#include "twi.h"

#include <avr/io.h>
#include "../../LIB/common_macros.h" /* To use the macros like SET_BIT */

void TWI_init(const Twi_ConfigType * Config_Ptr)
{
	/* just limited speed in TWI are 100k & 400k */
	if(Config_Ptr->clock == 400000)
	{
		/* when bit Rate: 400kbps using zero pre-scaler TWPS(TWPS0,TWPS1)=00 and F_CPU=8Mhz
		   from the equation :
		   400000 = 8000000(CPU) / 16+2(TWBR)*4^0(TWPS)
		   TWBR=2
		 */
		TWBR = 2;
		TWSR = 0x00;/* pre-scaler first two bits in this register TWSR */
	}
	else if(Config_Ptr->clock == 100000)
	{
		/* when bit Rate: 100kbps using zero pre-scaler TWPS(TWPS0,TWPS1)=00 and F_CPU=8Mhz
		from the equation :
		100000 = 8000000(CPU) / 16+2(TWBR)*4^0(TWPS)
		TWBR=32
		*/
		TWBR = 32;
		TWSR = 0x00;/* pre-scaler first two bits in this register TWSR */
	}

	/* in the 7 MSB of this register is slave address
     * the first bit in this register General Call Recognition: Off
     * my address = Config_Ptr->slave_address
    */
    TWAR = Config_Ptr->slave_address;

    TWCR = (1<<TWEN); /* enable TWI */
}

void TWI_start(void)
{
    /* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    /* polling hena mlhash lazma ha loss time 3ala fady lw 3aiz ab3t haga tani
       ha send start byte
     */
}

void TWI_writeByte(uint8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /* 
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readByteWithACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_readByteWithNACK(void)
{
	/*
	 * using this function when master read from slave. If the master woden't need to read from the slave he
     * will send negative ACK to till the slave to stop sending data to read
     */
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_getStatus(void)
{
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits 1111 1000 (status bits) */
    status = TWSR & 0xF8;
    return status;
}
