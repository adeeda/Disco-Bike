/**
 * \file main.c
 *
 * \brief Main Code
 *
 * This file does not do much except call other functions to set up all the drivers.
 * The main code operates in disco_extint.c
 */

/**
 * \mainpage Disco Bike!
 *
 * \par Introduction
 *
 * This is our fantastic code for running the Disco Bike.
 *
 * \par Content
 *
 * -# Main File
 * -# External Interrupt driver
 * -# LED driver
 * -# MPU driver
 * -# I2C driver
 *
 */

#include <asf.h>
#include "i2c_disco.h"
#include "disco_LED.h"
#include "disco_MPU.h"
#include "compiler.h"
#include "disco_extint.h"

int main (void)
{
	system_init();

	// Configure I2C and enable
	disco_configure_i2c_master();

	// Configure LED matrix
	disco_configure_LED();
	
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);
	pin_conf.direction = PORT_PIN_DIR_INPUT;
	port_pin_set_config(PIN_PA02, &pin_conf);
	port_pin_set_config(PIN_PA03, &pin_conf);
	port_pin_set_config(PIN_PA04, &pin_conf);
	port_pin_set_config(PIN_PA05, &pin_conf);
	
	// Configure MPU
	disco_configure_MPU();
	
	/*Configures the External Interrupt*/
	configure_extint();

	/*Configures the External Interrupt callback*/
	configure_eic_callback();
	
	/*Enable system interrupt*/
	system_interrupt_enable_global();
	
	//Does nothing in main, everything happens upon external interrupt.
	while (true) {
		
	}
}
