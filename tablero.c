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
		fichas_vacio_print,
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
			fichas_vacio_print();
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

	/*Posición de negras*/
	fichas_config(&g_ficha_generica, peon, negras);
	for(i = 0; i < 8; i++)
	{
		g_array_ajedrez[i + 8] = g_ficha_generica;
	}
	fichas_config(&g_ficha_generica, reina, negras);
	g_array_ajedrez[3] = g_ficha_generica;

	fichas_config(&g_ficha_generica, alfil, negras);
	g_array_ajedrez[2] = g_ficha_generica;
	g_array_ajedrez[5] = g_ficha_generica;

	fichas_config(&g_ficha_generica, torre, negras);
	g_array_ajedrez[0] = g_ficha_generica;
	g_array_ajedrez[7] = g_ficha_generica;

	fichas_config(&g_ficha_generica, caballo, negras);
	g_array_ajedrez[1] = g_ficha_generica;
	g_array_ajedrez[6] = g_ficha_generica;

	fichas_config(&g_ficha_generica, rey, negras);
	g_array_ajedrez[4] = g_ficha_generica;

	/*Posición de blancas*/
	fichas_config(&g_ficha_generica, peon, blancas);
	for(i = 0; i < 8; i++)
	{
		g_array_ajedrez[i + 48] = g_ficha_generica;
	}

	fichas_config(&g_ficha_generica, reina, blancas);
	g_array_ajedrez[3 + 56] = g_ficha_generica;

	fichas_config(&g_ficha_generica, alfil, blancas);
	g_array_ajedrez[2 + 56] = g_ficha_generica;
	g_array_ajedrez[5 + 56] = g_ficha_generica;

	fichas_config(&g_ficha_generica, torre, blancas);
	g_array_ajedrez[0 + 56] = g_ficha_generica;
	g_array_ajedrez[7 + 56] = g_ficha_generica;

	fichas_config(&g_ficha_generica, caballo, blancas);
	g_array_ajedrez[1 + 56] = g_ficha_generica;
	g_array_ajedrez[6 + 56] = g_ficha_generica;

	fichas_config(&g_ficha_generica, rey, blancas);
	g_array_ajedrez[4 + 56] = g_ficha_generica;
}

void tablero_print_fichas(void)
{
	uint8_t i = 0;
	uint8_t coordenada_x = 0;
	uint8_t coordenada_y = 0;
	/*Impresión de fichas negras*/
	for(i = 0; i < 16; i++)
	{
		coordenada_x = ((i % 8) * 16) + 1;
		coordenada_y = ((i / 8) * 8) + 1;
		coordenada_x = coordenada_x + g_array_ajedrez[i].offset[offset_x];
		coordenada_y = coordenada_y + g_array_ajedrez[i].offset[offset_y];
		tablero_mover_cursor(coordenada_x, coordenada_y);
		fichas_color(g_array_ajedrez[i].color);
		g_array_ajedrez[i].print_ficha();
	}

	/*Impresión de fichas blancas*/
	for(i = 0; i < 16; i++)
	{
		coordenada_x = (((i + 48) % 8) * 16) + 1;
		coordenada_y = (((i + 48) / 8) * 8) + 1;
		coordenada_x = coordenada_x + g_array_ajedrez[i + 48].offset[offset_x];
		coordenada_y = coordenada_y + g_array_ajedrez[i + 48].offset[offset_y];
		tablero_mover_cursor(coordenada_x, coordenada_y);
		fichas_color(g_array_ajedrez[i + 48].color);
		g_array_ajedrez[i + 48].print_ficha();
	}
}
