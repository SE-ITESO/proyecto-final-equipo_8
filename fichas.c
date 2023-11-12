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

void fichas_config(struct_ficha_t* ficha, name_ficha_t name, color_ficha_t color)
{
	switch(name)
	{
	case peon:
		ficha->print_ficha = fichas_peon_print;
		ficha->offset[offset_x] = 6;
		ficha->offset[offset_y] = 2;
		break;
	case torre:
		ficha->print_ficha = fichas_torre_print;
		ficha->offset[offset_x] = 5;
		ficha->offset[offset_y] = 2;
		break;
	case alfil:
		ficha->print_ficha = fichas_alfil_print;
		ficha->offset[offset_x] = 6;
		ficha->offset[offset_y] = 2;
		break;
	case caballo:
		ficha->print_ficha = fichas_caballo_print;
		ficha->offset[offset_x] = 7;
		ficha->offset[offset_y] = 1;
		break;
	case reina:
		ficha->print_ficha = fichas_reina_print;
		ficha->offset[offset_x] = 4;
		ficha->offset[offset_y] = 2;
		break;
	case rey:
		ficha->print_ficha = fichas_rey_print;
		ficha->offset[offset_x] = 7;
		ficha->offset[offset_y] = 1;
		break;
	default:
		ficha->print_ficha = fichas_vacio_print;
		ficha->offset[offset_x] = 0;
		ficha->offset[offset_y] = 0;
		break;
	}
	ficha->ficha_name = name;
	ficha->color = color;
}

void fichas_color(color_ficha_t color)
{
	switch(color)
	{
	case blancas:
		UART_put_string(UART_0, g_array_color_white);
		break;
	case negras:
		UART_put_string(UART_0, g_array_color_black);
		break;
	case azul:
		UART_put_string(UART_0, g_array_color_blue);
		break;
	case cyan:
		UART_put_string(UART_0, g_array_color_cyan);
		break;
	default:
		break;
	}
}

void fichas_peon_print(void)
{
	uint8_t i = 0;

	/*Nivel 1*/
	UART_put_char(UART_0, DOWN_LLENO);
	UART_put_char(UART_0, LLENO);
	UART_put_char(UART_0, LLENO);
	UART_put_char(UART_0, DOWN_LLENO);
	g_salto[6] = '4';
	UART_put_string(UART_0, g_salto);

	/*Nivel 2*/
	UART_put_char(UART_0, UP_LLENO);
	UART_put_char(UART_0, LLENO);
	UART_put_char(UART_0, LLENO);
	UART_put_char(UART_0, UP_LLENO);
	g_salto[6] = '4';
	UART_put_string(UART_0, g_salto);

	/*Nivel 3*/
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '5';
	UART_put_string(UART_0, g_salto);

	/*Nivel 4*/
	for(i = 0; i < 6; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '7';
	UART_put_string(UART_0, g_salto);

	/*Nivel 5*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '8';
	UART_put_string(UART_0, g_salto);
}


void fichas_torre_print(void)
{
	uint8_t i = 0;

	/*Nivel 1*/
	UART_put_char(UART_0, LLENO);
	UART_put_char(UART_0, DOWN_LLENO);
	UART_put_char(UART_0, LLENO);
	UART_put_char(UART_0, LLENO);
	UART_put_char(UART_0, DOWN_LLENO);
	UART_put_char(UART_0, LLENO);
	g_salto[6] = '6';
	UART_put_string(UART_0, g_salto);

	/*Nivel 2*/
	UART_put_char(UART_0, UP_LLENO);
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	UART_put_char(UART_0, UP_LLENO);
	g_salto[6] = '5';
	UART_put_string(UART_0, g_salto);

	/*Nivel 3*/
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '4';
	UART_put_string(UART_0, g_salto);

	/*Nivel 4*/
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '6';
	UART_put_string(UART_0, g_salto);

	/*Nivel 5*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '8';
	UART_put_string(UART_0, g_salto);
}


void fichas_alfil_print(void)
{
	uint8_t i = 0;

	/*Nivel 1*/
	UART_put_char(UART_0, DOWN_LLENO);
	UART_put_char(UART_0, LLENO);
	UART_put_char(UART_0, LLENO);
	UART_put_char(UART_0, DOWN_LLENO);
	g_salto[6] = '5';
	UART_put_string(UART_0, g_salto);

	/*Nivel 2*/
	UART_put_char(UART_0, DOWN_LLENO);
	UART_put_char(UART_0, VACIO);
	UART_put_char(UART_0, UP_LLENO);
	UART_put_char(UART_0, LLENO);
	UART_put_char(UART_0, LLENO);
	UART_put_char(UART_0, DOWN_LLENO);
	g_salto[6] = '6';
	UART_put_string(UART_0, g_salto);

	/*Nivel 3*/
	UART_put_char(UART_0, LLENO);
	UART_put_char(UART_0, LLENO);
	UART_put_char(UART_0, DOWN_LLENO);
	for(i = 0; i < 3; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '6';
	UART_put_string(UART_0, g_salto);

	/*Nivel 4*/
	UART_put_char(UART_0, UP_LLENO);
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	UART_put_char(UART_0, UP_LLENO);
	g_salto[6] = '7';
	UART_put_string(UART_0, g_salto);

	/*Nivel 5*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '8';
	UART_put_string(UART_0, g_salto);
}


void fichas_caballo_print(void)
{
	uint8_t i = 0;

	UART_put_char(UART_0, DOWN_LLENO);
	UART_put_char(UART_0, VACIO);
	UART_put_char(UART_0, DOWN_LLENO);
	g_salto[6] = '4';
	UART_put_string(UART_0, g_salto);

	/*Nivel 1*/
	UART_put_char(UART_0, DOWN_LLENO);
	for(i = 0; i < 3; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	UART_put_char(UART_0, DOWN_LLENO);
	g_salto[6] = '6';
	UART_put_string(UART_0, g_salto);

	/*Nivel 2*/
	for(i = 0; i < 6; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '5';
	UART_put_string(UART_0, g_salto);

	/*Nivel 3*/
	UART_put_char(UART_0, DOWN_LLENO);
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '6';
	UART_put_string(UART_0, g_salto);

	/*Nivel 4*/
	for(i = 0; i < 6; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '7';
	UART_put_string(UART_0, g_salto);

	/*Nivel 5*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '8';
	UART_put_string(UART_0, g_salto);
}


void fichas_reina_print(void)
{
	uint8_t i = 0;

	/*Nivel 1*/
	UART_put_char(UART_0, DOWN_LLENO);
	UART_put_char(UART_0, VACIO);
	UART_put_char(UART_0, LLENO);
	UART_put_char(UART_0, VACIO);
	UART_put_char(UART_0, VACIO);
	UART_put_char(UART_0, LLENO);
	UART_put_char(UART_0, VACIO);
	UART_put_char(UART_0, DOWN_LLENO);
	g_salto[6] = '8';
	UART_put_string(UART_0, g_salto);

	/*Nivel 2*/
	UART_put_char(UART_0, LLENO);
	UART_put_char(UART_0, DOWN_LLENO);
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	UART_put_char(UART_0, DOWN_LLENO);
	UART_put_char(UART_0, LLENO);
	g_salto[6] = '8';
	UART_put_string(UART_0, g_salto);

	/*Nivel 3*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '7';
	UART_put_string(UART_0, g_salto);

	/*Nivel 4*/
	UART_put_char(UART_0, UP_LLENO);
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	UART_put_char(UART_0, UP_LLENO);
	g_salto[6] = '7';
	UART_put_string(UART_0, g_salto);

	/*Nivel 5*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '8';
	UART_put_string(UART_0, g_salto);
}


void fichas_rey_print(void)
{
	uint8_t i = 0;

	UART_put_char(UART_0, DOWN_LLENO);
	UART_put_char(UART_0, DOWN_LLENO);
	g_salto[6] = '3';
	UART_put_string(UART_0, g_salto);

	/*Nivel 1*/
	UART_put_char(UART_0, UP_LLENO);
	for(i = 0; i < 2; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	UART_put_char(UART_0, UP_LLENO);
	g_salto[6] = '6';
	UART_put_string(UART_0, g_salto);

	/*Nivel 2*/
	UART_put_char(UART_0, DOWN_LLENO);
	UART_put_char(UART_0, DOWN_LLENO);
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	UART_put_char(UART_0, DOWN_LLENO);
	UART_put_char(UART_0, DOWN_LLENO);
	g_salto[6] = '8';
	UART_put_string(UART_0, g_salto);

	/*Nivel 3*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '7';
	UART_put_string(UART_0, g_salto);

	/*Nivel 4*/
	UART_put_char(UART_0, UP_LLENO);
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	UART_put_char(UART_0, UP_LLENO);
	g_salto[6] = '7';
	UART_put_string(UART_0, g_salto);

	/*Nivel 5*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '8';
	UART_put_string(UART_0, g_salto);
}

void fichas_vacio_print(void)
{
	uint8_t i;
	uint8_t l;
	for(l = 0; l < 8; l++)
	{
		for(i = 0; i < 16; i++)
		{
			UART_put_char(UART_0, LLENO);
		}
		UART_put_string(UART_0, g_salto_16);
	}
}
