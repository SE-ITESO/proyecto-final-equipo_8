/*
 * fichas.c
 *
 *  Created on: 11 nov 2023
 *      Author: brand
 */
#include "fichas.h"

static uint8_t g_salto[] = {'\e','[','1','B','\e','[','0','D','\0'};

static uint8_t g_salto_16[] = {'\e','[','1','B','\e','[','1','6','D','\0'};

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

void ficha_vacio_print(void)
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
