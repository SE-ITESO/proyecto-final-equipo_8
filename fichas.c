/*
 * fichas.c
 *
 *  Created on: 11 nov 2023
 *      Author: brand
 */
#include "fichas.h"

static uint8_t g_salto[] = {'\e','[','1','B','\e','[','0','D','\0'};

static uint8_t g_salto_16[] = {'\e','[','1','B','\e','[','1','6','D','\0'};

static uint8_t g_array_color_white[] = "\033[37m";

static uint8_t g_array_color_black[] = "\033[30m";

static uint8_t g_array_color_blue[] = "\033[34m";

static uint8_t g_array_color_cyan[] = "\033[36m";

static uint8_t g_posicion[] = {'\e','[','0','0',';','0','0','0','H','\0'};

void fichas_mover_cursor(UART_channel_t UART_name, uint16_t x, uint8_t y)
{
	g_posicion[5] = NUM_TO_ASCII(x / 100);
	x = x % 100;
	g_posicion[6] = NUM_TO_ASCII(x / 10);
	x = x % 10;
	g_posicion[7] = NUM_TO_ASCII(x);

	g_posicion[2] = NUM_TO_ASCII(y / 10);
	y = y % 10;
	g_posicion[3] = NUM_TO_ASCII(y);
	UART_put_string(UART_name, g_posicion);
}

void fichas_config(struct_ficha_t* ficha, name_ficha_t name, color_ficha_t color)
{
	switch(name)
	{
	case peon:
		ficha->print_ficha = fichas_peon_print;
		break;
	case torre:
		ficha->print_ficha = fichas_torre_print;
		break;
	case alfil:
		ficha->print_ficha = fichas_alfil_print;
		break;
	case caballo:
		ficha->print_ficha = fichas_caballo_print;
		break;
	case reina:
		ficha->print_ficha = fichas_reina_print;
		break;
	case rey:
		ficha->print_ficha = fichas_rey_print;
		break;
	default:
		ficha->print_ficha = fichas_vacio_print;
		break;
	}
	ficha->ficha_name = name;
	ficha->color = color;
}

void fichas_color(UART_channel_t UART_name, color_ficha_t color)
{
	switch(color)
	{
	case blancas:
		UART_put_string(UART_name, g_array_color_white);
		break;
	case negras:
		UART_put_string(UART_name, g_array_color_black);
		break;
	case azul:
		UART_put_string(UART_name, g_array_color_blue);
		break;
	case cyan:
		UART_put_string(UART_name, g_array_color_cyan);
		break;
	default:
		break;
	}
}

void fichas_peon_print(color_ficha_t color, uint16_t x, uint8_t y)
{
	fichas_color(UART_0, color);
	fichas_mover_cursor(UART_0, x + 6, y + 2);
	fichas_peon_UART(UART_0);

	fichas_color(UART_4, color);
	fichas_mover_cursor(UART_4, 114 + 6 - x, 58 + 2 - y);
	fichas_peon_UART(UART_4);
}

void fichas_peon_UART(UART_channel_t UART_name)
{
	uint8_t i = 0;

	/*Nivel 1*/
	UART_put_char(UART_name, DOWN_LLENO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, DOWN_LLENO);
	g_salto[6] = '4';
	UART_put_string(UART_name, g_salto);

	/*Nivel 2*/
	UART_put_char(UART_name, UP_LLENO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, UP_LLENO);
	g_salto[6] = '4';
	UART_put_string(UART_name, g_salto);

	/*Nivel 3*/
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '5';
	UART_put_string(UART_name, g_salto);

	/*Nivel 4*/
	for(i = 0; i < 6; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '7';
	UART_put_string(UART_name, g_salto);

	/*Nivel 5*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '8';
	UART_put_string(UART_name, g_salto);
}


void fichas_torre_print(color_ficha_t color, uint16_t x, uint8_t y)
{
	fichas_color(UART_0, color);
	fichas_mover_cursor(UART_0, x + 5, y + 2);
	fichas_torre_UART(UART_0);

	fichas_color(UART_4, color);
	fichas_mover_cursor(UART_4, 114 + 5 - x, 58 + 2 - y);
	fichas_torre_UART(UART_4);
}

void fichas_torre_UART(UART_channel_t UART_name)
{
	uint8_t i = 0;

	/*Nivel 1*/
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, DOWN_LLENO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, DOWN_LLENO);
	UART_put_char(UART_name, LLENO);
	g_salto[6] = '6';
	UART_put_string(UART_name, g_salto);

	/*Nivel 2*/
	UART_put_char(UART_name, UP_LLENO);
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	UART_put_char(UART_name, UP_LLENO);
	g_salto[6] = '5';
	UART_put_string(UART_name, g_salto);

	/*Nivel 3*/
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '4';
	UART_put_string(UART_name, g_salto);

	/*Nivel 4*/
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '6';
	UART_put_string(UART_name, g_salto);

	/*Nivel 5*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '8';
	UART_put_string(UART_name, g_salto);
}

void fichas_alfil_print(color_ficha_t color, uint16_t x, uint8_t y)
{
	fichas_color(UART_0, color);
	fichas_mover_cursor(UART_0, x + 6, y + 2);
	fichas_alfil_UART(UART_0);

	fichas_color(UART_4, color);
	fichas_mover_cursor(UART_4, 114 + 6 - x, 58 + 2 - y);
	fichas_alfil_UART(UART_4);
}

void fichas_alfil_UART(UART_channel_t UART_name)
{
	uint8_t i = 0;

	/*Nivel 1*/
	UART_put_char(UART_name, DOWN_LLENO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, DOWN_LLENO);
	g_salto[6] = '5';
	UART_put_string(UART_name, g_salto);

	/*Nivel 2*/
	UART_put_char(UART_name, DOWN_LLENO);
	UART_put_char(UART_name, VACIO);
	UART_put_char(UART_name, UP_LLENO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, DOWN_LLENO);
	g_salto[6] = '6';
	UART_put_string(UART_name, g_salto);

	/*Nivel 3*/
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, DOWN_LLENO);
	for(i = 0; i < 3; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '6';
	UART_put_string(UART_name, g_salto);

	/*Nivel 4*/
	UART_put_char(UART_name, UP_LLENO);
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	UART_put_char(UART_name, UP_LLENO);
	g_salto[6] = '7';
	UART_put_string(UART_name, g_salto);

	/*Nivel 5*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '8';
	UART_put_string(UART_name, g_salto);
}

void fichas_caballo_print(color_ficha_t color, uint16_t x, uint8_t y)
{
	fichas_color(UART_0, color);
	fichas_mover_cursor(UART_0, x + 7, y + 1);
	fichas_caballo_UART(UART_0);

	fichas_color(UART_4, color);
	fichas_mover_cursor(UART_4, 114 + 7 - x, 58 + 1 - y);
	fichas_caballo_UART(UART_4);
}

void fichas_caballo_UART(UART_channel_t UART_name)
{
	uint8_t i = 0;

	UART_put_char(UART_name, DOWN_LLENO);
	UART_put_char(UART_name, VACIO);
	UART_put_char(UART_name, DOWN_LLENO);
	g_salto[6] = '4';
	UART_put_string(UART_name, g_salto);

	/*Nivel 1*/
	UART_put_char(UART_name, DOWN_LLENO);
	for(i = 0; i < 3; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	UART_put_char(UART_name, DOWN_LLENO);
	g_salto[6] = '6';
	UART_put_string(UART_name, g_salto);

	/*Nivel 2*/
	for(i = 0; i < 6; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '5';
	UART_put_string(UART_name, g_salto);

	/*Nivel 3*/
	UART_put_char(UART_name, DOWN_LLENO);
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '6';
	UART_put_string(UART_name, g_salto);

	/*Nivel 4*/
	for(i = 0; i < 6; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '7';
	UART_put_string(UART_name, g_salto);

	/*Nivel 5*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '8';
	UART_put_string(UART_name, g_salto);
}


void fichas_reina_print(color_ficha_t color, uint16_t x, uint8_t y)
{
	fichas_color(UART_0, color);
	fichas_mover_cursor(UART_0, x + 4, y + 2);
	fichas_reina_UART(UART_0);

	fichas_color(UART_4, color);
	fichas_mover_cursor(UART_4, 114 + 4 - x, 58 + 2 - y);
	fichas_reina_UART(UART_4);
}

void fichas_reina_UART(UART_channel_t UART_name)
{
	uint8_t i = 0;

	/*Nivel 1*/
	UART_put_char(UART_name, DOWN_LLENO);
	UART_put_char(UART_name, VACIO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, VACIO);
	UART_put_char(UART_name, VACIO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, VACIO);
	UART_put_char(UART_name, DOWN_LLENO);
	g_salto[6] = '8';
	UART_put_string(UART_name, g_salto);

	/*Nivel 2*/
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, DOWN_LLENO);
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	UART_put_char(UART_name, DOWN_LLENO);
	UART_put_char(UART_name, LLENO);
	g_salto[6] = '8';
	UART_put_string(UART_name, g_salto);

	/*Nivel 3*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '7';
	UART_put_string(UART_name, g_salto);

	/*Nivel 4*/
	UART_put_char(UART_name, UP_LLENO);
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	UART_put_char(UART_name, UP_LLENO);
	g_salto[6] = '7';
	UART_put_string(UART_name, g_salto);

	/*Nivel 5*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '8';
	UART_put_string(UART_name, g_salto);
}

void fichas_rey_print(color_ficha_t color, uint16_t x, uint8_t y)
{
	fichas_color(UART_0, color);
	fichas_mover_cursor(UART_0, x + 7, y + 1);
	fichas_rey_UART(UART_0);

	fichas_color(UART_4, color);
	fichas_mover_cursor(UART_4, 114 + 7 - x, 58 + 1 - y);
	fichas_rey_UART(UART_4);
}

void fichas_rey_UART(UART_channel_t UART_name)
{
	uint8_t i = 0;

	UART_put_char(UART_name, DOWN_LLENO);
	UART_put_char(UART_name, DOWN_LLENO);
	g_salto[6] = '3';
	UART_put_string(UART_name, g_salto);

	/*Nivel 1*/
	UART_put_char(UART_name, UP_LLENO);
	for(i = 0; i < 2; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	UART_put_char(UART_name, UP_LLENO);
	g_salto[6] = '6';
	UART_put_string(UART_name, g_salto);

	/*Nivel 2*/
	UART_put_char(UART_name, DOWN_LLENO);
	UART_put_char(UART_name, DOWN_LLENO);
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	UART_put_char(UART_name, DOWN_LLENO);
	UART_put_char(UART_name, DOWN_LLENO);
	g_salto[6] = '8';
	UART_put_string(UART_name, g_salto);

	/*Nivel 3*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '7';
	UART_put_string(UART_name, g_salto);

	/*Nivel 4*/
	UART_put_char(UART_name, UP_LLENO);
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	UART_put_char(UART_name, UP_LLENO);
	g_salto[6] = '7';
	UART_put_string(UART_name, g_salto);

	/*Nivel 5*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '8';
	UART_put_string(UART_name, g_salto);
}

void fichas_vacio_print(color_ficha_t color, uint16_t x, uint8_t y)
{
	uint8_t colorear;
	uint8_t temporal;
	temporal = ((x - 1) / 16) + ((y - 1) / 8);
	temporal = temporal % 2;

	if(0 == temporal)
	{
		colorear = VACIO;
	}
	else
	{
		colorear = LLENO;
	}
	fichas_mover_cursor(UART_0, x, y);
	fichas_vacio_UART(UART_0, colorear);

	fichas_mover_cursor(UART_4, 114 - x, 58 - y);
	fichas_vacio_UART(UART_4, colorear);
}

void fichas_vacio_UART(UART_channel_t UART_name, uint8_t color)
{
	uint8_t i;
	uint8_t l;
	for(l = 0; l < 8; l++)
	{
		for(i = 0; i < 16; i++)
		{
			UART_put_char(UART_name, color);
		}
		UART_put_string(UART_name, g_salto_16);
	}
}
