/**
 * \file disco_LED.c
 * \brief LED Code
 
 * Created: 12/1/2015 11:10:24 AM
 * \author Team Disco
 *
 * C file for LED code for the Disco Bike.
 */ 
#include "disco_LED.h"

/** Configures the LED matrix
	8x8 Bi-color LED matrix.
	Turns it on, changes settings, and outputs a debug pattern to the matrix.
*/
void disco_configure_LED (void) {
	
	disco_set_slave_address(LED_ADDRESS);
	
	uint8_t address;
	int16_t data = 0;
	uint8_t length;
	uint8_t dataArray[DATA_LENGTH];
	
	//Write to System Setup Register
	// 0 0 1 0 X X X S
	address = 0b00100001;
	length = 1;
	write_i2c_disco(address, data, length);

	//Write to Dimming Set
	// 1 1 1 0 P3 P2 P1 P0
	address = 0b11101111;
	length = 1;
	write_i2c_disco(address, data, length);
	
	//Write to Display Setup
	// 1 0 0 0 X B1 B0 D
	address = 0b10000001;
	length = 1;
	write_i2c_disco(address, data, length);

	address = 0x00; //Sets the start row (The index for dataArray)
	length = 17;
	//Green Values
	dataArray[14] = 0b00000000;
	dataArray[12] = 0b00000000;
	dataArray[10] = 0b00000000;
	dataArray[8] =  0b00011000;
	dataArray[6] =  0b00011000;
	dataArray[4] =  0b00000000;
	dataArray[2] =  0b00000000;
	dataArray[0] =  0b00000000;
	//Red Values
	dataArray[15] = 0b00000000;
	dataArray[13] = 0b00000000;
	dataArray[11] = 0b00000000;
	dataArray[9] =  0b00010000;
	dataArray[7] =  0b00001000;
	dataArray[5] =  0b00000000;
	dataArray[3] =  0b00000000;
	dataArray[1] =  0b00000000;
	write_i2c_array_disco(address, dataArray, length);
}

/** Clears the LED matrix
	Turns off all green and red LEDs.
*/
void clear_LED(void){
	
	disco_set_slave_address(LED_ADDRESS);
	
	uint8_t address;
	uint8_t length;
	uint8_t dataArray[DATA_LENGTH];

	address = 0x00; //Sets the start row (The index for dataArray)
	length = 17;
	//Green Values
	dataArray[14] = 0b00000000;
	dataArray[12] = 0b00000000;
	dataArray[10] = 0b00000000;
	dataArray[8] =  0b00000000;
	dataArray[6] =  0b00000000;
	dataArray[4] =  0b00000000;
	dataArray[2] =  0b00000000;
	dataArray[0] =  0b00000000;
	//Red Values
	dataArray[15] = 0b00000000;
	dataArray[13] = 0b00000000;
	dataArray[11] = 0b00000000;
	dataArray[9] =  0b00000000;
	dataArray[7] =  0b00000000;
	dataArray[5] =  0b00000000;
	dataArray[3] =  0b00000000;
	dataArray[1] =  0b00000000;
	write_i2c_array_disco(address, dataArray, length);
}

/** Puts on the brakes
	Turns on all red LEDs, turns off all green LEDS.
*/
void brake_LED(void){
	
	disco_set_slave_address(LED_ADDRESS);
	
	uint8_t address;
	uint8_t length;
	uint8_t dataArray[DATA_LENGTH];

	address = 0x00; //Sets the start row (The index for dataArray)
	length = 17;
	//Green Values
	//Green Values
	dataArray[14] = 0b00000000;
	dataArray[12] = 0b00000000;
	dataArray[10] = 0b00000000;
	dataArray[8] =  0b00000000;
	dataArray[6] =  0b00000000;
	dataArray[4] =  0b00000000;
	dataArray[2] =  0b00000000;
	dataArray[0] =  0b00000000;
	//Red Values
	dataArray[15] = 0b11111111;
	dataArray[13] = 0b11111111;
	dataArray[11] = 0b11111111;
	dataArray[9] =  0b11111111;
	dataArray[7] =  0b11111111;
	dataArray[5] =  0b11111111;
	dataArray[3] =  0b11111111;
	dataArray[1] =  0b11111111;
	write_i2c_array_disco(address, dataArray, length);
}

/** Makes a right arrow.
	The arrow is yellow, so both green and red LEDs are turned on.
*/
void right_arrow(void) {
	
	disco_set_slave_address(LED_ADDRESS);
	
	uint8_t address;
	uint8_t length;
	uint8_t dataArray[DATA_LENGTH];

	address = 0x00; //Sets the start row (The index for dataArray)
	length = 17;
	//Green Values
	dataArray[14] = 0b11000000;
	dataArray[12] = 0b11110000;
	dataArray[10] = 0b01111100;
	dataArray[8] =  0b00111111;
	dataArray[6] =  0b00111111;
	dataArray[4] =  0b01111100;
	dataArray[2] =  0b11110000;
	dataArray[0] =  0b11000000;
	//Red Values
	dataArray[15] = 0b11000000;
	dataArray[13] = 0b11110000;
	dataArray[11] = 0b01111100;
	dataArray[9] =  0b00111111;
	dataArray[7] =  0b00111111;
	dataArray[5] =  0b01111100;
	dataArray[3] =  0b11110000;
	dataArray[1] =  0b11000000;
	write_i2c_array_disco(address, dataArray, length);
}

/** Makes a left arrow.
	The arrow is yellow, so both green and red LEDs are turned on.
*/
void left_arrow(void) {
	
	disco_set_slave_address(LED_ADDRESS);
	
	uint8_t address;
	uint8_t length;
	uint8_t dataArray[DATA_LENGTH];

	address = 0x00; //Sets the start row (The index for dataArray)
	length = 17;
	//Green Values
	dataArray[14] = 0b00000011;
	dataArray[12] = 0b00001111;
	dataArray[10] = 0b00111110;
	dataArray[8] =  0b11111100;
	dataArray[6] =  0b11111100;
	dataArray[4] =  0b00111110;
	dataArray[2] =  0b00001111;
	dataArray[0] =  0b00000011;
	//Red Values
	dataArray[15] = 0b00000011;
	dataArray[13] = 0b00001111;
	dataArray[11] = 0b00111110;
	dataArray[9] =  0b11111100;
	dataArray[7] =  0b11111100;
	dataArray[5] =  0b00111110;
	dataArray[3] =  0b00001111;
	dataArray[1] =  0b00000011;
	write_i2c_array_disco(address, dataArray, length);
}

/** Makes a right arrow while braking.
	Same as right arrow, but with red LEDs on around it.
*/
void right_arrow_brake(void) {
	
		disco_set_slave_address(LED_ADDRESS);
		
		uint8_t address;
		uint8_t length;
		uint8_t dataArray[DATA_LENGTH];

		address = 0x00; //Sets the start row (The index for dataArray)
		length = 17;
		//Green Values
		dataArray[14] = 0b11000000;
		dataArray[12] = 0b11110000;
		dataArray[10] = 0b01111100;
		dataArray[8] =  0b00111111;
		dataArray[6] =  0b00111111;
		dataArray[4] =  0b01111100;
		dataArray[2] =  0b11110000;
		dataArray[0] =  0b11000000;
		//Red Values
		dataArray[15] = 0b11111111;
		dataArray[13] = 0b11111111;
		dataArray[11] = 0b11111111;
		dataArray[9] =  0b11111111;
		dataArray[7] =  0b11111111;
		dataArray[5] =  0b11111111;
		dataArray[3] =  0b11111111;
		dataArray[1] =  0b11111111;
		write_i2c_array_disco(address, dataArray, length);
}

/** Makes a left arrow while braking.
	Same as left arrow, but with red LEDs on around it.
*/
void left_arrow_brake(void) {
	
	disco_set_slave_address(LED_ADDRESS);
	
	uint8_t address;
	uint8_t length;
	uint8_t dataArray[DATA_LENGTH];

	address = 0x00; //Sets the start row (The index for dataArray)
	length = 17;
	//Green Values
	dataArray[14] = 0b00000011;
	dataArray[12] = 0b00001111;
	dataArray[10] = 0b00111110;
	dataArray[8] =  0b11111100;
	dataArray[6] =  0b11111100;
	dataArray[4] =  0b00111110;
	dataArray[2] =  0b00001111;
	dataArray[0] =  0b00000011;
	//Red Values
	dataArray[15] = 0b11111111;
	dataArray[13] = 0b11111111;
	dataArray[11] = 0b11111111;
	dataArray[9] =  0b11111111;
	dataArray[7] =  0b11111111;
	dataArray[5] =  0b11111111;
	dataArray[3] =  0b11111111;
	dataArray[1] =  0b11111111;
	write_i2c_array_disco(address, dataArray, length);
}

/** Turns on the hazard lights.
	The hazard lights are two small yellow arrows.
*/
void hazard_LED(void) {
	
	disco_set_slave_address(LED_ADDRESS);
	
	uint8_t address;
	uint8_t length;
	uint8_t dataArray[DATA_LENGTH];

	address = 0x00; //Sets the start row (The index for dataArray)
	length = 17;
	//Green Values
	dataArray[14] = 0b00000000;
	dataArray[12] = 0b00100100;
	dataArray[10] = 0b01100110;
	dataArray[8] =  0b11100111;
	dataArray[6] =  0b11100111;
	dataArray[4] =  0b01100110;
	dataArray[2] =  0b00100100;
	dataArray[0] =  0b00000000;
	//Red Values
	dataArray[15] = 0b00000000;
	dataArray[13] = 0b00100100;
	dataArray[11] = 0b01100110;
	dataArray[9] =  0b11100111;
	dataArray[7] =  0b11100111;
	dataArray[5] =  0b01100110;
	dataArray[3] =  0b00100100;
	dataArray[1] =  0b00000000;
	write_i2c_array_disco(address, dataArray, length);
}

/** Function for changing LED brightness
	The LED matrix does this with PWM.
	@param bright Brightness value between 0 and 15.
*/
void set_LED_brightness (uint8_t bright){
	
	disco_set_slave_address(LED_ADDRESS);
	
	uint8_t address;
	int16_t data = 0;
	uint8_t length;

	//Write to Dimming Set
	// 1 1 1 0 P3 P2 P1 P0
	address = 0b11100000 | bright;
	length = 1;
	write_i2c_disco(address, data, length);
}

/** Disco Disco Disco
	discodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodisco
	discodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodisco
	discodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodisco
	discodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodisco
	discodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodisco
	discodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscodiscobike
*/
void disco_disco_disco (void) {
	
	disco_set_slave_address(LED_ADDRESS);
	
	static bool disco_state;

	uint8_t address = 0x00; //Sets the start row (The index for dataArray)
	uint8_t length = 17;
	uint8_t dataArray[DATA_LENGTH];
	
	if(disco_state) {
		disco_state = false;
		//Green Values
		dataArray[14] = 0b00001111;
		dataArray[12] = 0b00001111;
		dataArray[10] = 0b00001111;
		dataArray[8] =  0b00001111;
		dataArray[6] =  0b11110000;
		dataArray[4] =  0b11110000;
		dataArray[2] =  0b11110000;
		dataArray[0] =  0b11110000;
		//Red Values
		dataArray[15] = 0b00000000;
		dataArray[13] = 0b00000000;
		dataArray[11] = 0b00000000;
		dataArray[9] =  0b00000000;
		dataArray[7] =  0b00000000;
		dataArray[5] =  0b00000000;
		dataArray[3] =  0b00000000;
		dataArray[1] =  0b00000000;
	}  else {
		disco_state = true;
		//Green Values
		dataArray[14] = 0b11110000;
		dataArray[12] = 0b11110000;
		dataArray[10] = 0b11110000;
		dataArray[8] =  0b11110000;
		dataArray[6] =  0b00001111;
		dataArray[4] =  0b00001111;
		dataArray[2] =  0b00001111;
		dataArray[0] =  0b00001111;
		//Red Values
		dataArray[15] = 0b00000000;
		dataArray[13] = 0b00000000;
		dataArray[11] = 0b00000000;
		dataArray[9] =  0b00000000;
		dataArray[7] =  0b00000000;
		dataArray[5] =  0b00000000;
		dataArray[3] =  0b00000000;
		dataArray[1] =  0b00000000;
	}
	write_i2c_array_disco(address, dataArray, length);
}