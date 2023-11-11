/*
 * fichas.c
 *
 *  Created on: 11 nov 2023
 *      Author: brand
 */
#include "fichas.h"

static uint8_t g_salto[] = {'\e','[','1','B','\e','[','0','D','\0'};

void fichas_peon_print(void)
{
	uint8_t i = 0;
	/*Nivel 1*/
	for(i = 0; i < 2; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '3';
	UART_put_string(UART_0, g_salto);

	/*Nivel 2*/
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '4';
	UART_put_string(UART_0, g_salto);

	/*Nivel 3*/
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '3';
	UART_put_string(UART_0, g_salto);

	/*Nivel 4*/
	for(i = 0; i < 2; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '3';
	UART_put_string(UART_0, g_salto);

	/*Nivel 5*/
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '4';
	UART_put_string(UART_0, g_salto);

	/*Nivel 6*/
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '5';
	UART_put_string(UART_0, g_salto);

	/*Nivel 7*/
	for(i = 0; i < 6; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '6';
	UART_put_string(UART_0, g_salto);

	/*Nivel 8*/
	for(i = 0; i < 6; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '7';
	UART_put_string(UART_0, g_salto);

	/*Nivel 9*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '8';
	UART_put_string(UART_0, g_salto);

	/*Nivel 10*/
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
	UART_put_char(UART_0, VACIO);
	for(i = 0; i < 2; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	UART_put_char(UART_0, VACIO);
	UART_put_char(UART_0, LLENO);

	g_salto[6] = '6';
	UART_put_string(UART_0, g_salto);

	/*Nivel 2*/
	for(i = 0; i < 6; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '6';
	UART_put_string(UART_0, g_salto);

	/*Nivel 3*/
	for(i = 0; i < 6; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '5';
	UART_put_string(UART_0, g_salto);

	/*Nivel 4*/
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '4';
	UART_put_string(UART_0, g_salto);

	/*Nivel 5*/
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '4';
	UART_put_string(UART_0, g_salto);

	/*Nivel 6*/
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '4';
	UART_put_string(UART_0, g_salto);

	/*Nivel 7*/
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '4';
	UART_put_string(UART_0, g_salto);

	/*Nivel 8*/
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '6';
	UART_put_string(UART_0, g_salto);

	/*Nivel 9*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '8';
	UART_put_string(UART_0, g_salto);

	/*Nivel 10*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_0, LLENO);
	}
	g_salto[6] = '8';
	UART_put_string(UART_0, g_salto);
}

