/**
 * \file i2c_disco.h
 * \brief I2C Code
 
 * Created: 12/1/2015 10:18:31 AM
 * \author: Team Disco
 *
 * Header file for I2C code for the Disco Bike.
 */ 

#ifndef I2C_DISCO_H_
#define I2C_DISCO_H_

#define DATA_LENGTH 17
#define LED_ADDRESS 0b1110000 //LED Square#define MPU_ADDRESS 0b1101000 //MPU 9150 Breakout Board
#define TIMEOUT 1000

#include "i2c_master.h"

/** Required structs to operate i2c */
struct i2c_master_module i2c_master_instance;
struct i2c_master_packet packet;

/** Configures the i2c on the board.
	This function was given to us by Atmel Studio.
	It configures the pins to be PA14 and PA15.
*/
void configure_i2c_master(void);

/** Configures our i2c driver.
	Initializes the i2c packet and runs the Atmel i2c configure function.
*/
void disco_configure_i2c_master(void);

/** Sets i2c slave address
	@param address The 7bit i2c address of the slave that we want to communicate with currently.
*/
void disco_set_slave_address(uint8_t address);

/** Reads 8 or 16 bit data from I2C
	@param address 8bit data register for the slave
	@param length Number of bytes in data (1 or 2)
	@return 8 or 16 bit data, depending on length.
*/
int16_t read_i2c_disco(uint8_t address, uint8_t length);

/** Writes 8 or 16 bit data to I2C slave
	Has a different length usage because some slaves use the register as "data"
	@param address 8bit data register for the slave
	@param data 8 or 16 bit data (length 2 or 3). Ignored if length is 1.
	@param length Number of bytes in data (1 to 3)
*/
void write_i2c_disco(uint8_t address, int16_t data, uint8_t length);

/** Reads an array of bytes from I2C slave
	@param address 8bit data register for the slave
	@param data Pointer to an 8-bit array
	@param length Number of bytes in data (Do not exceed DATA_LENGTH!)
*/
void read_i2c_array_disco(uint8_t address, uint8_t* data, uint8_t length);

/** Writes an array of bytes to I2C
	@param address 8bit data register for the slave
	@param data Pointer to an 8-bit array
	@param length Number of bytes in data (Do not exceed DATA_LENGTH!)
*/
void write_i2c_array_disco(uint8_t address, uint8_t* data, uint8_t length);


#endif /* I2C_DISCO_H_ */