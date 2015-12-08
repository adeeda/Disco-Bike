/*
 * disco_uart.c
 *
 * Created: 12/2/2015 12:58:41 PM
 *  Author: ANDROOOO
 */ 

#include "disco_uart.h"

/*
 *  Configure UART console.
 */
void configure_console(void)
{
	struct usart_config usart_conf;

	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	usart_conf.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	usart_conf.baudrate    = 38400;

	stdio_serial_init(&cdc_uart_module, EDBG_CDC_MODULE, &usart_conf);
	usart_enable(&cdc_uart_module);
}

uint8_t Ascii_to_Hex(char input)
{
	/* Function to convert Ascii to Hexidecimal */
	if (input >= 48 && input <= 57)
	{
		return input - 48;
	}
	else if (input >= 65 && input <= 70)
	{
		return input - 55;
	}
	return 0;
}
