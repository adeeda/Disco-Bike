/**
 * \file disco_extint.c
 * \brief External Interrupt Code
 
 * Created: 12/2/2015 5:29:32 PM
 * \author Team Disco
 *
 * C File to hold all interrupt related code for the Disco Bike.
 */ 

#include "disco_extint.h"

#define MAX_COUNT 5

uint8_t dataArray[DATA_LENGTH];
int16_t data;
int16_t GX;
int16_t GY;
int16_t GZ;
bool buttonPress1 = false; //Button State Flags
bool buttonPress2 = false;
bool Button_1 = false; //Blinker State Flags
bool Button_2 = false;
bool Button_3 = false;
bool Left_Signal = false; //LED State Flags
bool Right_Signal = false;
bool Hazard_Signal = false;
bool tilt_flag = false;
uint16_t i = 0;

/** The external interrupt callback.
	This code runs whenever the MPU generates an interrupt.
	It checks the state of the buttons, reads the MPU data, and operates the LED accordingly.
*/
void extint_callback(void)
{	
	//system_interrupt_disable_global();
	if(port_pin_get_input_level(PIN_PA02)){
		if(!buttonPress1) {
			buttonPress1 = true;
		}
	} else {
		if(buttonPress1) {
			if(Button_1){
				Button_1 = false;
			}
			else {
				Button_1 = true;
				Button_2 = false;
			}
			buttonPress1 = false;
		}
	}
		
	if(port_pin_get_input_level(PIN_PA03)){
		if(!buttonPress2) {
			buttonPress2 = true;
		}
	} else {
		if(buttonPress2) {
			if(Button_2){
				Button_2 = false;
			}
			else {
				Button_2 = true;
				Button_1 = false;
			}
			buttonPress2 = false;
		}
	}
	
	if(port_pin_get_input_level(PIN_PA04)){
		Button_3 = true;
		Button_1 = false;
		Button_2 = false;
	} else {
		Button_3 = false;
	}
	
	//Accel, Temp, Gyro; X, Y, Z; H L;
	//0:5    6:7   8:13
	read_MPU_data(dataArray);
	//data = ((int16_t) dataArray[0]<<8 | (int16_t) dataArray[1]);//Accel X
	//data = ((int16_t) dataArray[2]<<8 | (int16_t) dataArray[3]);//Accel Y
	//data = ((int16_t) dataArray[4]<<8 | (int16_t) dataArray[5]);//Accel Z
	GX = ((int16_t) dataArray[8]<<8 | (int16_t) dataArray[9]);//Gyro X
	//GY = ((int16_t) dataArray[10]<<8 | (int16_t) dataArray[11]);//Gyro Y
	GZ = ((int16_t) dataArray[12]<<8 | (int16_t) dataArray[13]); //Gyro Z
	data = (int16_t) ( (int32_t) GX * -95 / 100 + GZ * 3 / 10) - 6600; //Rotated Gyro Z so that it is Yaw -- using rotation matrix, yAngle 72.5
	
	/*
	UPRIGHT is the tilt of the bike
	triggerpoint is the point at which the bike is considered upright or not
	bool tilt_flag is a flag that determines if the bike is upright or not.
	bool Button_1 is true if button 1 is pressed, false otherwise.
	bool Left_Signal is true if button 1 is on, false if off
	bool Button_2 is true if button 2 is pressed, false otherwise.
	bool Right Signal is true if button 2 is on, false if off
	bool Button_3 is true if button 3 is pressed, false otherwise.
	bool Hazard_Signal is true if hazard light is on, false otherwise
	*/

	if(abs(data)>3000)	//If the bike is tilted - 3000 is a chosen number.
	{
		tilt_flag = true;		//Set the tilt flag
	}
		
	if (Button_3 && !Hazard_Signal)		//if button 3 is pressed once and the hazard is off, wait thirty counts and
	{						//turn the hazard signal on
		i++;
		if(i>=MAX_COUNT) {
			hazard_LED();
			Hazard_Signal = true;
			i=0;
		}
	}
	else if (Button_3 && Hazard_Signal)			//if button 3 is pressed once and the hazard is on, wait thirty counts and
	{											//turn the hazard signal off
		i++;
		if(i>=MAX_COUNT) {
			clear_LED();
			Hazard_Signal = false;
			i=0;
		}
	}
	else if(Button_1 && !Left_Signal)				//if button 1 is pressed once and the left signal is off, wait thirty counts
	{											//and turn the light on.
		i++;
		if(i>=MAX_COUNT) {
			left_arrow();
			Left_Signal = true;
			i=0;
		}
	}
	else if (Button_1 && Left_Signal)			//if button 1 is pressed once and the left signal is on, wait thirty counts
	{											//and turn the light off
		i++;
		if(i>=MAX_COUNT) {
			clear_LED();
			Left_Signal = false;
			i=0;
		}
	}
	else if (Button_2 && !Right_Signal)			//if button 2 is pressed once and the right signal is not on, wait thirty counts
	{							//and turn the light on
		i++;
		if(i>=MAX_COUNT) {
			right_arrow();
			Right_Signal = true;
			i=0;
		}
	}
	else if (Button_2 && Right_Signal)			//if button 2 is pressed once and the right signal is on, wait thirty counts
	{							//and turn the light off
		i++;
		if(i>=MAX_COUNT) {
			clear_LED();
			Right_Signal = false;
			i=0;
		}
	}
	else if (!Button_1 && Left_Signal)							//if button 1 pressed twice, turn left blinker off
	{
		clear_LED();
		Left_Signal = 0;
	}
	else if (!Button_2 && Right_Signal)							//if button 2 pressed twice, turn right blinker off
	{
		clear_LED();
		Right_Signal = 0;
	}
	else if (!Button_3 && Hazard_Signal)							//if button 3 pressed twice, turn hazard lights off
	{
		clear_LED();
		Hazard_Signal = 0;
	}
	else 
	{
		i++;
		if(i>=MAX_COUNT) {
			disco_disco_disco();
			i=0;
		}
	}

	if(abs(data)<=3000 && tilt_flag)		//if the bike is upright again, and the tilt flag is true, then turn the blinkers off.
	{
		if(Button_1 || Button_2) {
			clear_LED();
			Button_1 = false;
			Button_2 = false;
			Right_Signal = false;
			Left_Signal = false;
		}
		tilt_flag = false;
	}
}

/** Configures and registers the External Interrupt callback function with the
 *  driver.
 */
void configure_eic_callback(void)
{
	extint_register_callback(extint_callback,
			5,			//5 is related to extint5, which is related to PA25
			EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(5,
			EXTINT_CALLBACK_TYPE_DETECT);
}

/** Configures the External Interrupt Controller to detect changes in the board
 *  button state.
 */
void configure_extint(void)
{
	configure_dataready_int();
	
	struct extint_chan_conf eint_chan_conf;
	extint_chan_get_config_defaults(&eint_chan_conf);

	eint_chan_conf.gpio_pin           = PIN_PA05A_EIC_EXTINT5;
	eint_chan_conf.gpio_pin_mux       = MUX_PA05A_EIC_EXTINT5;
	eint_chan_conf.detection_criteria = EXTINT_DETECT_RISING;
	eint_chan_conf.filter_input_signal = true;
	extint_chan_set_config(5, &eint_chan_conf);
}