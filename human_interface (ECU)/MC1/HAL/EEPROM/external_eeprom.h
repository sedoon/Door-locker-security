 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.h
 *
 * Description: Header file for the External EEPROM Memory
 *
 * Author: SAYED IBRAHIM
 *
 *******************************************************************************/


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "../../LIB/std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);

uint8 EEPROM_writeArray(uint16 u16addr,uint8 *u8arr,uint16 arr_size);
uint8 EEPROM_readArray(uint16 u16addr,uint8 *u8arr,uint16 arr_size);
 
#endif /* EXTERNAL_EEPROM_H_ */
