/*
 * fichas.c
 *
 *  Created on: 11 nov 2023
 *      Author: brand
 */
#include "fichas.h"

static uint8_t g_salto[] = {'\e','[','1','B','\e','[','0','D','\0'};

static uint8_t g_salto_16[] = {'\e','[','1','B','\e','[','1','6','D','\0'};

static uint8_t g_salto_n[] = {'\e','[','1','B','\e','[','5','D','\0'};

static uint8_t g_regreso_n[] = {'\e','[','5','A','\0'};

static uint8_t g_array_color_white[] = "\033[37m";

static uint8_t g_array_color_black[] = "\033[30m";

static uint8_t g_array_color_blue[] = "\033[34m";

static uint8_t g_array_color_cyan[] = "\033[36m";

static uint8_t g_array_color_rojo[] = "\033[31m";

static uint8_t g_array_color_verde[] = "\033[32m";

static uint8_t g_array_color_amarillo[] = "\033[33m";

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
	ficha->posible_mov = FALSE;
	ficha->opciones.number_opciones = 0;
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
	case rojo:
		UART_put_string(UART_name, g_array_color_rojo);
		break;
	case verde:
		UART_put_string(UART_name, g_array_color_verde);
		break;
	case amarillo:
		UART_put_string(UART_name, g_array_color_amarillo);
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

void fichas_peon_mov(uint8_t x, uint8_t y, struct_ficha_t ajedrez[64])
{
	struct_ficha_t* peon;
	struct_ficha_t* alt;
	uint8_t index;
	peon = ajedrez + x + (y * 8);
	if(blancas == peon->color)
	{
		if(ninguno == (peon - 8)->ficha_name)
		{
			peon->opciones.valor_opciones[peon->opciones.number_opciones] = x + ((y - 1) * 8);
			ajedrez[x + ((y - 1) * 8)].posible_mov = TRUE;
			peon->opciones.number_opciones++;
			if((ninguno == (peon - 16)->ficha_name) & (6 == y))
			{
				peon->opciones.valor_opciones[peon->opciones.number_opciones] = x + ((y - 2) * 8);
				ajedrez[x + ((y - 2) * 8)].posible_mov = TRUE;
				peon->opciones.number_opciones++;
			}
		}

		index = x - 1;
		if(index < 8)
		{
			alt = ajedrez + index + ((y - 1) * 8);
			if((ninguno != alt->ficha_name) & (negras == alt->color))
			{
				peon->opciones.valor_opciones[peon->opciones.number_opciones] = index + ((y - 1) * 8);
				ajedrez[index + ((y - 1) * 8)].posible_mov = TRUE;
				peon->opciones.number_opciones++;
			}
		}
		index = x + 1;
		if(index < 8)
		{
			alt = ajedrez + index + ((y - 1) * 8);
			if((ninguno != alt->ficha_name) & (negras == alt->color))
			{
				peon->opciones.valor_opciones[peon->opciones.number_opciones] = index + ((y - 1) * 8);
				ajedrez[index + ((y - 1) * 8)].posible_mov = TRUE;
				peon->opciones.number_opciones++;
			}
		}

	}
	else
	{
		if(ninguno == (peon + 8)->ficha_name)
		{
			peon->opciones.valor_opciones[peon->opciones.number_opciones] = x + ((y + 1) * 8);
			ajedrez[x + ((y + 1) * 8)].posible_mov = TRUE;
			peon->opciones.number_opciones++;
			if((ninguno == (peon + 16)->ficha_name) & (1 == y))
			{
				peon->opciones.valor_opciones[peon->opciones.number_opciones] = x + ((y + 2) * 8);
				ajedrez[x + ((y + 2) * 8)].posible_mov = TRUE;
				peon->opciones.number_opciones++;
			}
		}


		index = x - 1;
		if(index < 8)
		{
			alt = ajedrez + index + ((y + 1) * 8);
			if((ninguno != alt->ficha_name) & (blancas == alt->color))
			{
				peon->opciones.valor_opciones[peon->opciones.number_opciones] = index + ((y + 1) * 8);
				ajedrez[index + ((y + 1) * 8)].posible_mov = TRUE;
				peon->opciones.number_opciones++;
			}
		}
		index = x + 1;
		if(index < 8)
		{
			alt = ajedrez + index + ((y + 1) * 8);
			if((ninguno != alt->ficha_name) & (blancas == alt->color))
			{
				peon->opciones.valor_opciones[peon->opciones.number_opciones] = index + ((y + 1) * 8);
				ajedrez[index + ((y + 1) * 8)].posible_mov = TRUE;
				peon->opciones.number_opciones++;
			}
		}

	}
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

void fichas_movimiento_horizontal(uint8_t* y_min, uint8_t x, uint8_t y, struct_ficha_t ajedrez[64])
{
	uint8_t i;

	(*y_min) = 0;

	for(i = 0; i < y; i++)
	{
		if(ninguno != ajedrez[x + (8 * (i))].ficha_name)
		{
			(*y_min) = i;
		}
	}

	*(y_min + 1) = 7;
	for(i = 0; i < (7 - y); i++)
	{
		if(ninguno != ajedrez[x + (8 * (7 - i))].ficha_name)
		{
			*(y_min + 1) = 7 - i;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fichas_torre_mov(uint8_t x, uint8_t y, struct_ficha_t ajedrez[64])
{
	struct_ficha_t* torre;
	uint8_t temp;
	uint8_t i;
	uint8_t y_min[2];

	torre = ajedrez + x + (y * 8);

	fichas_movimiento_horizontal(y_min, x, y, ajedrez);

	temp = y - *(y_min);
	for(i = 0; i < (temp - 1); i++)
	{
		torre->opciones.valor_opciones[torre->opciones.number_opciones] = x + ((y - i - 1) * 8);
		ajedrez[x + ((y - i - 1) * 8)].posible_mov = TRUE;
		torre->opciones.number_opciones++;
	}

	if(ajedrez[x + ((y - temp) * 8)].color != torre->color)
	{
		torre->opciones.valor_opciones[torre->opciones.number_opciones] = x + ((y - temp) * 8);
		ajedrez[x + ((y - temp) * 8)].posible_mov = TRUE;
		torre->opciones.number_opciones++;
	}

	temp = *(y_min + 1) - y;
	for(i = 0; i < (temp - 1); i++)
	{
		torre->opciones.valor_opciones[torre->opciones.number_opciones] = x + ((y + i + 1) * 8);
		ajedrez[x + ((y + i + 1) * 8)].posible_mov = TRUE;
		torre->opciones.number_opciones++;
	}

	if(ajedrez[x + ((y + temp) * 8)].color != torre->color)
	{
		torre->opciones.valor_opciones[torre->opciones.number_opciones] = x + ((y + temp) * 8);
		ajedrez[x + ((y + temp) * 8)].posible_mov = TRUE;
		torre->opciones.number_opciones++;
	}

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
		fichas_color(UART_0, azul);
		fichas_color(UART_4, azul);
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

void fichas_seleccion_print(UART_channel_t UART_name, color_ficha_t color)
{
	uint8_t i;
	uint8_t l;

	fichas_color(UART_name, color);
	for(l = 0; l < 5; l++)
	{
		for(i = 0; i < 5; i++)
		{
			UART_put_char(UART_name, LLENO);
		}
		UART_put_string(UART_name, g_salto_n);
	}
	UART_put_string(UART_name, g_regreso_n);
}

void fichas_print_opcion(uint8_t UART_num)
{
	uint8_t i;
	uint8_t l;

	fichas_color(UART_num, amarillo);
	for(l = 0; l < 8; l++)
	{
		for(i = 0; i < 16; i++)
		{
			UART_put_char(UART_num, LLENO);
		}
		UART_put_string(UART_num, g_salto_16);
	}
}

void fichas_clear_opciones(struct_opciones_t* posibilidades, UART_channel_t UART_name, struct_ficha_t ajedrez[64])
{
	uint8_t i;
	uint8_t x;
	uint8_t y;
	struct_ficha_t ficha;
	for(i = 0; i < posibilidades->number_opciones; i++)
	{
		ajedrez[posibilidades->valor_opciones[i]].posible_mov = FALSE;
		x = posibilidades->valor_opciones[i] % 8;
		y = posibilidades->valor_opciones[i] / 8;
		ficha = *(ajedrez + x + (y * 8));
		fichas_mover_cursor(UART_name, (x * 16) + 1, (y * 8) + 1);
		fichas_vacio_print(indefinido, (x * 16) + 1, (y * 8) + 1);
		if(ninguno != ficha.ficha_name)
		{
				ficha.print_ficha(ficha.color, (x * 16) + 1, (y * 8) + 1);
		}
	}
	posibilidades->number_opciones = 0;
}

void fichas_mostrar_opciones(struct_opciones_t* posibilidades, uint8_t jugador, struct_ficha_t ajedrez[64])
{
	uint8_t index;
	uint8_t UART_num = jugador * 4;
	uint8_t x;
	uint8_t y;
	struct_ficha_t ficha;
	for(index = 0; index < posibilidades->number_opciones; index++)
	{
		x = posibilidades->valor_opciones[index] % 8;
		y = posibilidades->valor_opciones[index] / 8;
		ficha = *(ajedrez + x + (y * 8));
		if(0 == jugador)
		{
			fichas_mover_cursor(UART_num, (x * 16) + 1, (y * 8) + 1);
		}
		else
		{
			fichas_mover_cursor(UART_num, ((7 - x) * 16) + 1, ((7 - y) * 8) + 1);
		}
		fichas_print_opcion(UART_num);
		if(ninguno != ficha.ficha_name)
		{
				ficha.print_ficha(ficha.color, (x * 16) + 1, (y * 8) + 1);
		}
	}
}
