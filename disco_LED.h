/**
 * \file disco_LED.h
 * \brief LED Code
 
 * Created: 12/1/2015 11:10:29 AM
 * \author Team Disco
 *
 * Header file for LED code for the Disco Bike.
 */ 

#ifndef disco_LED_H_
#define disco_LED_H_

#include "i2c_disco.h"

/** Configures the LED matrix
	8x8 Bi-color LED matrix.
	Turns it on, changes settings, and outputs a debug pattern to the matrix.
*/
void disco_configure_LED (void);

/** Clears the LED matrix
	Turns off all green and red LEDs.
*/
void clear_LED(void);

/** Puts on the brakes
	Turns on all red LEDs, turns off all green LEDS.
*/
void brake_LED(void);

/** Makes a right arrow.
	The arrow is yellow, so both green and red LEDs are turned on.
*/
void right_arrow(void);

/** Makes a left arrow.
	The arrow is yellow, so both green and red LEDs are turned on.
*/
void left_arrow(void);

/** Makes a right arrow while braking.
	Same as right arrow, but with red LEDs on around it.
*/
void right_arrow_brake(void);

/** Makes a left arrow while braking.
	Same as left arrow, but with red LEDs on around it.
*/
void left_arrow_brake(void);

/** Turns on the hazard lights.
	The hazard lights are two small yellow arrows.
*/
void hazard_LED(void);

/** Function for changing LED brightness
	The LED matrix does this with PWM.
	@param bright Brightness value between 0 and 15.
*/
void set_LED_brightness(uint8_t bright);

/** Disco Disco Disco
	discodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodisco
	discodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodisco
	discodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscobike
*/
void disco_disco_disco(void);

#endif /* disco_LED_H_ */