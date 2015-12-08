/**
 * \file disco_MPU.h
 * \brief MPU Code
 
 * Created: 12/1/2015 12:15:57 PM
 * \author Team Disco
 *
 * Header file for MPU code for the Disco Bike.
 */ 

#ifndef DISCO_MPU_H_
#define DISCO_MPU_H_

#include "i2c_disco.h"

/** Configures the MPU
	Wakes it up and adjusts settings
*/
void disco_configure_MPU (void);

/** Function for reading all readings from the MPU
	@param array Pointer to an 8-bit array that will hold the sensor readings.
*/
void read_MPU_data (uint8_t* data);

/** Configures "data ready" interrupts on the MPU
	Such that the MPU generates an interrupt every time new sensor data is available.
*/
void configure_dataready_int(void);

#endif /* DISCO_MPU_H_ */