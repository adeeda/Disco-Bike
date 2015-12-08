/**
 * \file disco_extint.h
 * \brief External Interrupt Code
 
 * Created: 12/2/2015 5:29:54 PM
 * \author Team Disco
 *
 * Header file for interrupt code for the Disco Bike.
 */ 

#ifndef DISCO_EXTINT_H_
#define DISCO_EXTINT_H_

#include <asf.h>
#include "disco_LED.h"
#include "disco_MPU.h"

/** The external interrupt callback.
	This code runs whenever the MPU generates an interrupt.
	It checks the state of the buttons, reads the MPU data, and operates the LED accordingly.
*/
void extint_callback(void);

/** Configures and registers the External Interrupt callback function with the
 *  driver.
 */
void configure_eic_callback(void);

/** Configures the External Interrupt Controller to detect changes in the board
 *  button state.
 */
void configure_extint(void);

#endif /* DISCO_EXTINT_H_ */