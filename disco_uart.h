/*
 * disco_uart.h
 *
 * Created: 12/2/2015 12:58:52 PM
 *  Author: ANDROOOO
 */ 


#ifndef DISCO_UART_H_
#define DISCO_UART_H_

#include <asf.h>
#include "stdio_serial.h"

#define STRING_EOL    "\r"

#define COMMAND_LIST "COMMANDS: \r\n" \
"-- Press T to TOGGLE the LED --\r\n" \
"-- Press R to READ from the motor driver --\r\n" \
"-- Press W to WRITE to the motor driver --\r\n" \
"-- Press S to start a SQUARE wave with the motor --\r\n" \
"-- Press L to show the LIST of commands --\r\n"STRING_EOL

#define STRING_HEADER "-- Blinking an LED --\r\n" \
"-- "BOARD_NAME" --\r\n" \
"-- Compiled: "__DATE__" "__TIME__" --\r\n" \
COMMAND_LIST

struct usart_module cdc_uart_module;

void configure_console(void);

uint8_t Ascii_to_Hex(char input);

#endif /* DISCO_UART_H_ */