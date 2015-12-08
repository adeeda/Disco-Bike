/**
 * \file i2c_disco.c
 * \brief I2C Code
 
 * Created: 12/1/2015 10:18:31 AM
 * \author: Team Disco
 *
 * C file for I2C code for the Disco Bike.
 */ 
#include "i2c_disco.h"

uint8_t write_buffer[DATA_LENGTH];
uint8_t read_buffer[DATA_LENGTH];

/** Configures the i2c on the board.
	This function was given to us by Atmel Studio.
	It configures the pins to be PA14 and PA15.
*/
void configure_i2c_master(void)
{
	/* Initialize config structure and software module. */
	struct i2c_master_config config_i2c_master;
	i2c_master_get_config_defaults(&config_i2c_master);
	/* Change buffer timeout to something longer. */
	config_i2c_master.buffer_timeout = 10000;
	
	config_i2c_master.pinmux_pad0 = PINMUX_PA14C_SERCOM0_PAD0;
	config_i2c_master.pinmux_pad1 = PINMUX_PA15C_SERCOM0_PAD1;
	
	/* Initialize and enable device with config. */
	i2c_master_init(&i2c_master_instance, SERCOM0, &config_i2c_master);
	i2c_master_enable(&i2c_master_instance);
}

/** Configures our i2c driver.
	Initializes the i2c packet and runs the Atmel i2c configure function.
*/
void disco_configure_i2c_master(void) {
	/* Init i2c packet. */
	packet.address = LED_ADDRESS;
	packet.data_length = DATA_LENGTH;
	packet.data = write_buffer;
	packet.ten_bit_address = false;
	packet.high_speed = false;
	packet.hs_master_code = 0x0;
	configure_i2c_master();
}

/** Sets i2c slave address
	@param address The 7bit i2c address of the slave that we want to communicate with currently.
*/
void disco_set_slave_address(uint8_t address) {
	packet.address = address;
}

/** Reads 8 or 16 bit data from I2C
	@param address 8bit data register for the slave
	@param length Number of bytes in data (1 or 2)
	@return 8 or 16 bit data, depending on length.
*/
int16_t read_i2c_disco(uint8_t address, uint8_t length) {
	uint16_t timeout = 0;
	write_buffer[0] = address;
	packet.data_length = 1;
	packet.data = write_buffer;
	/* Write READ address */
	while (i2c_master_write_packet_wait(&i2c_master_instance, &packet) !=
	STATUS_OK) {
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
	timeout = 0;
	/* Read from slave until success. */
	packet.data = read_buffer; //Set packet to read_buffer
	packet.data_length = length;
	while (i2c_master_read_packet_wait(&i2c_master_instance, &packet) !=
	STATUS_OK) {
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
	timeout = 0;
	if(length == 1) {
		return (int16_t) read_buffer[0];
	} else {
		return ( (int16_t) read_buffer[0]<<8 ) | (int16_t) read_buffer[1];
	}
}

/** Writes 8 or 16 bit data to I2C slave
	Has a different length usage because some slaves use the register as "data"
	@param address 8bit data register for the slave
	@param data 8 or 16 bit data (length 2 or 3). Ignored if length is 1.
	@param length Number of bytes in data (1 to 3)
*/
void write_i2c_disco(uint8_t address, int16_t data, uint8_t length) {
	uint16_t timeout = 0;
	write_buffer[0] = address;
	packet.data_length = length;
	if(length > 1) {
		if(length < 3) {
			write_buffer[1] = (uint8_t) data;
			} else {
			write_buffer[1] = MSB(data);
			write_buffer[2] = LSB(data);
		}
	}
	packet.data = write_buffer;
	/* Write buffer to slave until success. */
	while (i2c_master_write_packet_wait(&i2c_master_instance, &packet) !=
	STATUS_OK) {
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
	timeout = 0;
}

/** Reads an array of bytes from I2C slave
	@param address 8bit data register for the slave
	@param data Pointer to an 8-bit array
	@param length Number of bytes in data (Do not exceed DATA_LENGTH!)
*/
void read_i2c_array_disco(uint8_t address, uint8_t* data, uint8_t length) {
	uint16_t timeout = 0;
	write_buffer[0] = address;
	packet.data_length = 1;
	packet.data = write_buffer;
	/* Write READ address */
	while (i2c_master_write_packet_wait(&i2c_master_instance, &packet) !=
	STATUS_OK) {
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
	timeout = 0;
	/* Read from slave until success. */
	packet.data = read_buffer; //Set packet to read_buffer
	packet.data_length = length;
	while (i2c_master_read_packet_wait(&i2c_master_instance, &packet) !=
	STATUS_OK) {
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
	timeout = 0;
	for(int i=0; i<length; i++) {
		data[i] = read_buffer[i];
	}
}

/** Writes an array of bytes to I2C
	@param address 8bit data register for the slave
	@param data Pointer to an 8-bit array
	@param length Number of bytes in data (Do not exceed DATA_LENGTH!)
*/
void write_i2c_array_disco(uint8_t address, uint8_t* data, uint8_t length) {
	uint16_t timeout = 0;
	write_buffer[0] = address;
	packet.data_length = length;
	if(length > 1) {
		for(int i=1; i<length; i++) {
			write_buffer[i] = data[i-1];
		}
	}
	packet.data = write_buffer;
	/* Write buffer to slave until success. */
	while (i2c_master_write_packet_wait(&i2c_master_instance, &packet) !=
	STATUS_OK) {
		/* Increment timeout counter and check if timed out. */
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
	timeout = 0;
}