/*
 * tablero.c
 *
 *  Created on: 11 nov 2023
 *      Author: brand
 */

#include "tablero.h"

static uint8_t g_array_init[] = "\033[0;34;46m"
		"\033[2J";

static uint8_t g_posicion[] = {'\e','[','0','0',';','0','0','0','H','\0'};

void tablero_init(void)
{
	UART_put_string(UART_0, g_array_init);

	uint8_t i;
	uint8_t l;
	uint8_t temp_x;
	uint8_t temp_y;
	for(l = 0; l < 8; l++)
	{
		temp_y = (l * 8) + 1;
		for(i = 0; i < 4; i++)
		{
			temp_x = (((l + 1) % 2) * 16) + (i * 32) + 1;
			tablero_mover_cursor(temp_x, temp_y);
			UART_put_string(UART_0, g_posicion);
			ficha_vacio_print();
		}
	}
}

void tablero_mover_cursor (uint16_t x, uint8_t y)
{
	g_posicion[5] = NUM_TO_ASCII(x / 100);
	x = x % 100;
	g_posicion[6] = NUM_TO_ASCII(x / 10);
	x = x % 10;
	g_posicion[7] = NUM_TO_ASCII(x);

	g_posicion[2] = NUM_TO_ASCII(y / 10);
	y = y % 10;
	g_posicion[3] = NUM_TO_ASCII(y);
}
