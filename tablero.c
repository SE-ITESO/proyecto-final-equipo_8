/*
 * tablero.c
 *
 *  Created on: 11 nov 2023
 *      Author: brand
 */

#include "tablero.h"

static struct_ficha_t g_ficha_generica =
{
		indefinido,
		ficha_vacio_print,
		ninguno,
		{0, 0}
};

static struct_ficha_t g_array_ajedrez[64];

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
			ficha_vacio_print();
		}
	}

	tablero_acomodo_arreglo();
	tablero_print_fichas();
}

void tablero_mover_cursor(uint16_t x, uint8_t y)
{
	g_posicion[5] = NUM_TO_ASCII(x / 100);
	x = x % 100;
	g_posicion[6] = NUM_TO_ASCII(x / 10);
	x = x % 10;
	g_posicion[7] = NUM_TO_ASCII(x);

	g_posicion[2] = NUM_TO_ASCII(y / 10);
	y = y % 10;
	g_posicion[3] = NUM_TO_ASCII(y);
	UART_put_string(UART_0, g_posicion);
}

void tablero_acomodo_arreglo(void)
{
	uint8_t i;
	for(i = 0; i < 64; i++)
	{
		g_array_ajedrez[i] = g_ficha_generica;
	}

	g_ficha_generica.color = negras;
	g_ficha_generica.ficha_name = peon;
	g_ficha_generica.print_ficha = fichas_peon_print;
	g_ficha_generica.offset[offset_x] = 6;
	g_ficha_generica.offset[offset_y] = 2;

	for(i = 0; i < 8; i++)
	{
		g_array_ajedrez[i + 8] = g_ficha_generica;
	}
}

void tablero_print_fichas(void)
{
	uint8_t i = 0;
	uint8_t coordenada_x = 0;
	uint8_t coordenada_y = 0;

	for(i = 0; i < 8; i++)
	{
		coordenada_x = (((i + 8) % 8) * 16) + 1;
		coordenada_y = (((i + 8) / 8) * 8) + 1;
		coordenada_x = coordenada_x + g_array_ajedrez[i + 8].offset[offset_x];
		coordenada_y = coordenada_y + g_array_ajedrez[i + 8].offset[offset_y];
		tablero_mover_cursor(coordenada_x, coordenada_y);
		fichas_color(g_array_ajedrez[i + 8].color);
		g_array_ajedrez[i + 8].print_ficha();
	}
}
