/**
 * \file disco_MPU.c
 * \brief MPU Code
 
 * Created: 12/1/2015 12:15:39 PM
 * \author Team Disco
 *
 * C file for MPU code for the Disco Bike.
 */ 

#include "disco_MPU.h"

uint8_t dataArray[DATA_LENGTH];
uint8_t address;
int16_t data;
uint8_t length;

/** Configures the MPU
	Wakes it up and adjusts settings
*/
void disco_configure_MPU (void) {
	
	disco_set_slave_address(MPU_ADDRESS);
	
	//Set Sample Rate Divider
	address = 25;
	// Sample Rate = Gyro Output Rate / (1+data)
	// Gyro Output Rate = 8kHz if DLPF_CFG = 0, 1kHz if not.
	data = 99;
	length = 2; //address + data
	write_i2c_disco(address, data, length);
	
	//Configuration
	address = 26;
	// - - EXT_SYNC_SET[2:0] DLPF_CFG[2:0]
	data = 0b00000001;
	//See page 11 of MPU 9150 Register Map
	length = 2;
	write_i2c_disco(address, data, length);
	
	//Gyro Config
	address = 27;
	// XG_ST YG_ST ZG_ST FS_SEL[1:0] - - -
	data = 0b11100000;
	//Current Full Scale Range: +/- 250 deg/s
	//Current LSB Sensitivity: 131 LSB/deg/s
	//See page 30 of MPU 9150 Register Map
	length = 2;
	write_i2c_disco(address, data, length);
	
	//Accelerometer Config
	address = 28;
	// XA_ST YA_ST ZA_ST AFS_SEL[1:0] - - -
	data = 0b11100000;
	//Current Full Scale Range: +/- 2g
	//Current LSB Sensitivity: 16384 LSB/mg
	//See page 28 of MPU 9150 Register Map
	length = 2;
	write_i2c_disco(address, data, length);
	
	//Power Management 1
	address = 107;
	// DEVICE_RESET SLEEP CYCLE - TEMP_DIS CLKSEL[2:0]
	data = 0b00000000;
	length = 2;
	write_i2c_disco(address, data, length);
}

/** Function for reading all readings from the MPU
	@param array Pointer to an 8-bit array that will hold the sensor readings.
*/
void read_MPU_data (uint8_t* array) {
	
	disco_set_slave_address(MPU_ADDRESS);
	
	//Read Acceleration, Temp, and Gyro data in one burst
	address = 59;
	length = 14;
	read_i2c_array_disco(address, array, length);
}

/** Configures "data ready" interrupts on the MPU
	Such that the MPU generates an interrupt every time new sensor data is available.
*/
void configure_dataready_int(void){
	
	disco_set_slave_address(MPU_ADDRESS);
	
	address = 56;
	data = 0b00000001;
	length = 2;
	write_i2c_disco(address, data, length);
}