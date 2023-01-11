 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: Source file for the External EEPROM Memory
 *
 * Author: SAYED IBRAHIM
 *
 *******************************************************************************/
#include "external_eeprom.h"

#include "../../MCAL/TWI/twi.h"



uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)
{
	/* 1-start
	 * 2-7-bit address
	 * 3-read/write
	 * 4-ACK
	 * 5-Send and Receive Data then ACK
	 * 6-if Combined massage (repeated start)
	 * 7-stop
	 */

    TWI_start(); /*  First Send the Start Bit */

    if (TWI_getStatus() != TWI_START)
        return ERROR;
		
    /*
     * Send the device(slave)address, ACK ,and R/W=0 (write)
     * we need to get A8 A9 A10 address bits from the memory location address
     */
    TWI_writeByte((uint8)(0xA0 | ((u16addr & 0x700)>>7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR; 
		 
    /* Send the required memory location address .this address location inside the EEPROM
     *  we using casting cause we send the other 8bits of the memory location address
     *  and last 3bit send it in the previous step
     */
    TWI_writeByte((uint8)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;
		
    /* write one byte to EEPROM .. master send so slave re-send with ACK */
    TWI_writeByte(u8data);
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    TWI_stop(); /* Send the Stop Bit */

	
    return SUCCESS;
}

uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)/*combined massage*/
{									/* pointer for return the byte i want read */

    TWI_start(); /* Send the Start Bit */
    if (TWI_getStatus() != TWI_START)
        return ERROR;
		
    /* we can not read in first so we will write then read
	 * Send the device(slave)address, ACK ,and R/W=0 (write)
	 * we need to get A8 A9 A10 address bits from the memory location address
	 */
    TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x700)>>7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;
		
    /* Send the required memory location address */
    TWI_writeByte((uint8)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;
		
    /*  we need to read so we Send the Repeated Start Bit to change the value of W/R*/
    TWI_start();
    if (TWI_getStatus() != TWI_REP_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
    if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
        return ERROR;

    /*  just Read one Byte from Memory so NOT send ACK ..master read from slave so cann't send ACK
     * just master send NACK when woden't need to read from the slave  */
    *u8data = TWI_readByteWithNACK();
    if (TWI_getStatus() != TWI_MR_DATA_NACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_stop();

    return SUCCESS;
}



uint8 EEPROM_writeArray(uint16 u16addr,uint8 *u8arr_data,uint16 arr_size)
{
	uint8 i;
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_writeByte((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;

    /* Send the required memory location address */
    TWI_writeByte((uint8)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    /* (write a lot of bytes) write array to EEPROM */
    for(i=0;i<arr_size;i++)
    {
    	TWI_writeByte(u8arr_data[i]);
    	 if (TWI_getStatus() != TWI_MT_DATA_ACK)
    		 return ERROR;
    }
    TWI_stop();
    return SUCCESS;

}

uint8 EEPROM_readArray(uint16 u16addr,uint8 *u8arr_data,uint16 arr_size)
{
	uint8 i;
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;

    /* Send the required memory location address */
    TWI_writeByte((uint8)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    /* Send the Repeated Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_REP_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
    if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
        return ERROR;

    /*  read array from Memory with sending ACK cause reading a lot of bytes */
    for(i=0;i<arr_size-1;i++)
    {
    	u8arr_data[i] = TWI_readByteWithACK();
    	if (TWI_getStatus() != TWI_MR_DATA_ACK)
    		return ERROR;
    }

    u8arr_data[arr_size-1] = TWI_readByteWithNACK(); /*is read just one byte so will not sending ACK*/
        	if (TWI_getStatus() != TWI_MR_DATA_NACK)
        		return ERROR;

    /* Send the Stop Bit */
    TWI_stop();

    return SUCCESS;
}



