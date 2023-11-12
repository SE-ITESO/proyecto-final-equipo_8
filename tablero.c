/*
 * tablero.c
 *
 *  Created on: 11 nov 2023
 *      Author: brand
 */

#include "tablero.h"

static uint8_t g_array_init[] = "\033[0;34;46m"
		"\033[2J";

static uint8_t g_salto_16[] = {'\e','[','1','B','\e','[','1','6','D','\0'};

void tablero_init(void)
{
	UART_put_string(UART_0, g_array_init);


	UART_put_string(UART_0, "\033[01;17H");
	ficha_vacio_print();

	UART_put_string(UART_0, "\033[9;01H");
	ficha_vacio_print();

	UART_put_string(UART_0, "\033[17;17H");
	ficha_vacio_print();

	UART_put_string(UART_0, "\033[25;01H");
	ficha_vacio_print();

	UART_put_string(UART_0, "\033[33;17H");
	ficha_vacio_print();
}
