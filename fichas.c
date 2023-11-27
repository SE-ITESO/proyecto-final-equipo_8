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

void fichas_movimiento_vertical(uint8_t* y_min, uint8_t x, uint8_t y, struct_ficha_t ajedrez[64])
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


void fichas_movimiento_horizontal(uint8_t* x_min, uint8_t x, uint8_t y, struct_ficha_t ajedrez[64])
{
	uint8_t i;

	(*x_min) = 0;
	for(i = 0; i < x; i++)
	{
		if(ninguno != ajedrez[i + (8 * y)].ficha_name)
		{
			(*x_min) = i;
		}
	}

	*(x_min + 1) = 7;
	for(i = 0; i < (7 - x); i++)
	{
		if(ninguno != ajedrez[(7 - i) + (8 * y)].ficha_name)
		{
			*(x_min + 1) = 7 - i;
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
	uint8_t x_min[2];

	torre = ajedrez + x + (y * 8);

	fichas_movimiento_vertical(y_min, x, y, ajedrez);

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

	fichas_movimiento_horizontal(x_min, x, y, ajedrez);

	temp = x - *(x_min);
	for(i = 0; i < (temp - 1); i++)
	{
		torre->opciones.valor_opciones[torre->opciones.number_opciones] = (x - i - 1) + (y * 8);
		ajedrez[(x - i - 1) + (y * 8)].posible_mov = TRUE;
		torre->opciones.number_opciones++;
	}

	if(ajedrez[(x - temp) + (y  * 8)].color != torre->color)
	{
		torre->opciones.valor_opciones[torre->opciones.number_opciones] = (x - temp) + (y  * 8);
		ajedrez[(x - temp) + (y  * 8)].posible_mov = TRUE;
		torre->opciones.number_opciones++;
	}

	temp = *(x_min + 1) - x;
	for(i = 0; i < (temp - 1); i++)
	{
		torre->opciones.valor_opciones[torre->opciones.number_opciones] = (x + i + 1) + (y * 8);
		ajedrez[(x + i + 1) + (y * 8)].posible_mov = TRUE;
		torre->opciones.number_opciones++;
	}

	if(ajedrez[(x + temp) + (y * 8)].color != torre->color)
	{
		torre->opciones.valor_opciones[torre->opciones.number_opciones] = (x + temp) + (y * 8);
		ajedrez[(x + temp) + (y * 8)].posible_mov = TRUE;
		torre->opciones.number_opciones++;
	}

}

void fichas_alfil_mov(uint8_t x, uint8_t y, struct_ficha_t ajedrez[64])
{
	uint8_t lim[4];
	uint8_t i;
	uint8_t limite;
	uint8_t coordenada;
	struct_ficha_t* alfil;

	alfil = ajedrez + x + (y * 8);
	lim[limite_menos_x] = x;
	lim[limite_menos_y] = y;
	lim[limite_mas_x] = 7 - x;
	lim[limite_mas_y] = 7 - y;

	/*Caso [-k,-k]*/
	if(lim[limite_menos_x] < lim[limite_menos_y])
	{
		limite = lim[limite_menos_x];
	}
	else
	{
		limite = lim[limite_menos_y];
	}
	coordenada = limite;
	for(i = 0; i < limite; i++)
	{
		if(ninguno != ajedrez[(x - limite + i) + ((y - limite + i) * 8)].ficha_name)
		{
			coordenada = (limite - i);
		}
	}

	for(i = 0; i < (coordenada - 1); i++)
	{
		alfil->opciones.valor_opciones[alfil->opciones.number_opciones] = (x - i - 1) + ((y - i - 1) * 8);
		ajedrez[(x - i - 1) + ((y - i - 1) * 8)].posible_mov = TRUE;
		alfil->opciones.number_opciones++;
	}
	if(ajedrez[(x - coordenada) + ((y - coordenada) * 8)].color != alfil->color)
	{
		alfil->opciones.valor_opciones[alfil->opciones.number_opciones] = (x - coordenada) + ((y - coordenada) * 8);
		ajedrez[(x - coordenada) + ((y - coordenada) * 8)].posible_mov = TRUE;
		alfil->opciones.number_opciones++;
	}

	/*Caso [+k,-k]*/
	if(lim[limite_mas_x] < lim[limite_menos_y])
	{
		limite = lim[limite_mas_x];
	}
	else
	{
		limite = lim[limite_menos_y];
	}
	coordenada = limite;
	for(i = 0; i < limite; i++)
	{
		if(ninguno != ajedrez[(x + limite - i) + ((y - limite + i) * 8)].ficha_name)
		{
			coordenada = (limite - i);
		}
	}

	for(i = 0; i < (coordenada - 1); i++)
	{
		alfil->opciones.valor_opciones[alfil->opciones.number_opciones] = (x + i + 1) + ((y - i - 1) * 8);
		ajedrez[(x + i + 1) + ((y - i - 1) * 8)].posible_mov = TRUE;
		alfil->opciones.number_opciones++;
	}
	if(ajedrez[(x + coordenada) + ((y - coordenada) * 8)].color != alfil->color)
	{
		alfil->opciones.valor_opciones[alfil->opciones.number_opciones] = (x + coordenada) + ((y - coordenada) * 8);
		ajedrez[(x + coordenada) + ((y - coordenada) * 8)].posible_mov = TRUE;
		alfil->opciones.number_opciones++;
	}

	/*Caso [-k,+k]*/
	if(lim[limite_menos_x] < lim[limite_mas_y])
	{
		limite = lim[limite_menos_x];
	}
	else
	{
		limite = lim[limite_mas_y];
	}
	coordenada = limite;
	for(i = 0; i < limite; i++)
	{
		if(ninguno != ajedrez[(x - limite + i) + ((y + limite - i) * 8)].ficha_name)
		{
			coordenada = (limite - i);
		}
	}

	for(i = 0; i < (coordenada - 1); i++)
	{
		alfil->opciones.valor_opciones[alfil->opciones.number_opciones] = (x - i - 1) + ((y + i + 1) * 8);
		ajedrez[(x - i - 1) + ((y + i + 1) * 8)].posible_mov = TRUE;
		alfil->opciones.number_opciones++;
	}
	if(ajedrez[(x - coordenada) + ((y + coordenada) * 8)].color != alfil->color)
	{
		alfil->opciones.valor_opciones[alfil->opciones.number_opciones] = (x - coordenada) + ((y + coordenada) * 8);
		ajedrez[(x - coordenada) + ((y + coordenada) * 8)].posible_mov = TRUE;
		alfil->opciones.number_opciones++;
	}

	/*Caso [+k,+k]*/
	if(lim[limite_mas_x] < lim[limite_mas_y])
	{
		limite = lim[limite_mas_x];
	}
	else
	{
		limite = lim[limite_mas_y];
	}
	coordenada = limite;
	for(i = 0; i < limite; i++)
	{
		if(ninguno != ajedrez[(x + limite - i) + ((y + limite - i) * 8)].ficha_name)
		{
			coordenada = (limite - i);
		}
	}

	for(i = 0; i < (coordenada - 1); i++)
	{
		alfil->opciones.valor_opciones[alfil->opciones.number_opciones] = (x + i + 1) + ((y + i + 1) * 8);
		ajedrez[(x + i + 1) + ((y + i + 1) * 8)].posible_mov = TRUE;
		alfil->opciones.number_opciones++;
	}
	if(ajedrez[(x + coordenada) + ((y + coordenada) * 8)].color != alfil->color)
	{
		alfil->opciones.valor_opciones[alfil->opciones.number_opciones] = (x + coordenada) + ((y + coordenada) * 8);
		ajedrez[(x + coordenada) + ((y + coordenada) * 8)].posible_mov = TRUE;
		alfil->opciones.number_opciones++;
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

void fichas_caballo_mov(uint8_t x, uint8_t y, struct_ficha_t ajedrez[64])
{
	struct_ficha_t* caballo;
	caballo = ajedrez + x + (y * 8);
	uint8_t coordenada_x;
	uint8_t coordenada_y;

	coordenada_x = x + 1;
	coordenada_y = y + 2;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		if((caballo->color) != (ajedrez[(coordenada_x) + (coordenada_y * 8)].color))
		{
			caballo->opciones.valor_opciones[caballo->opciones.number_opciones] = (coordenada_x) + (coordenada_y * 8);
			ajedrez[(coordenada_x) + (coordenada_y * 8)].posible_mov = TRUE;
			caballo->opciones.number_opciones++;
		}
	}

	coordenada_x = x + 1;
	coordenada_y = y - 2;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		if((caballo->color) != (ajedrez[(coordenada_x) + (coordenada_y * 8)].color))
		{
			caballo->opciones.valor_opciones[caballo->opciones.number_opciones] = (coordenada_x) + (coordenada_y * 8);
			ajedrez[(coordenada_x) + (coordenada_y * 8)].posible_mov = TRUE;
			caballo->opciones.number_opciones++;
		}
	}

	coordenada_x = x + 2;
	coordenada_y = y + 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		if((caballo->color) != (ajedrez[(coordenada_x) + (coordenada_y * 8)].color))
		{
			caballo->opciones.valor_opciones[caballo->opciones.number_opciones] = (coordenada_x) + (coordenada_y * 8);
			ajedrez[(coordenada_x) + (coordenada_y * 8)].posible_mov = TRUE;
			caballo->opciones.number_opciones++;
		}
	}

	coordenada_x = x + 2;
	coordenada_y = y - 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		if((caballo->color) != (ajedrez[(coordenada_x) + (coordenada_y * 8)].color))
		{
			caballo->opciones.valor_opciones[caballo->opciones.number_opciones] = (coordenada_x) + (coordenada_y * 8);
			ajedrez[(coordenada_x) + (coordenada_y * 8)].posible_mov = TRUE;
			caballo->opciones.number_opciones++;
		}
	}

	coordenada_x = x - 1;
	coordenada_y = y + 2;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		if((caballo->color) != (ajedrez[(coordenada_x) + (coordenada_y * 8)].color))
		{
			caballo->opciones.valor_opciones[caballo->opciones.number_opciones] = (coordenada_x) + (coordenada_y * 8);
			ajedrez[(coordenada_x) + (coordenada_y * 8)].posible_mov = TRUE;
			caballo->opciones.number_opciones++;
		}
	}

	coordenada_x = x - 1;
	coordenada_y = y - 2;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		if((caballo->color) != (ajedrez[(coordenada_x) + (coordenada_y * 8)].color))
		{
			caballo->opciones.valor_opciones[caballo->opciones.number_opciones] = (coordenada_x) + (coordenada_y * 8);
			ajedrez[(coordenada_x) + (coordenada_y * 8)].posible_mov = TRUE;
			caballo->opciones.number_opciones++;
		}
	}

	coordenada_x = x - 2;
	coordenada_y = y + 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		if((caballo->color) != (ajedrez[(coordenada_x) + (coordenada_y * 8)].color))
		{
			caballo->opciones.valor_opciones[caballo->opciones.number_opciones] = (coordenada_x) + (coordenada_y * 8);
			ajedrez[(coordenada_x) + (coordenada_y * 8)].posible_mov = TRUE;
			caballo->opciones.number_opciones++;
		}
	}

	coordenada_x = x - 2;
	coordenada_y = y - 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		if((caballo->color) != (ajedrez[(coordenada_x) + (coordenada_y * 8)].color))
		{
			caballo->opciones.valor_opciones[caballo->opciones.number_opciones] = (coordenada_x) + (coordenada_y * 8);
			ajedrez[(coordenada_x) + (coordenada_y * 8)].posible_mov = TRUE;
			caballo->opciones.number_opciones++;
		}
	}
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

void fichas_reina_mov(uint8_t x, uint8_t y, struct_ficha_t ajedrez[64])
{
	fichas_torre_mov(x, y, ajedrez);
	fichas_alfil_mov(x, y, ajedrez);
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

void fichas_rey_mov(uint8_t x, uint8_t y, struct_ficha_t ajedrez[64])
{
	struct_ficha_t* rey;
	rey = ajedrez + x + (y * 8);
	uint8_t coordenada_x;
	uint8_t coordenada_y;

	coordenada_x = x - 1;
	coordenada_y = y - 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		if((rey->color) != (ajedrez[(coordenada_x) + (coordenada_y * 8)].color))
		{
			rey->opciones.valor_opciones[rey->opciones.number_opciones] = (coordenada_x) + (coordenada_y * 8);
			ajedrez[(coordenada_x) + (coordenada_y * 8)].posible_mov = TRUE;
			rey->opciones.number_opciones++;
		}
	}

	coordenada_x = x;
	coordenada_y = y - 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		if((rey->color) != (ajedrez[(coordenada_x) + (coordenada_y * 8)].color))
		{
			rey->opciones.valor_opciones[rey->opciones.number_opciones] = (coordenada_x) + (coordenada_y * 8);
			ajedrez[(coordenada_x) + (coordenada_y * 8)].posible_mov = TRUE;
			rey->opciones.number_opciones++;
		}
	}

	coordenada_x = x + 1;
	coordenada_y = y - 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		if((rey->color) != (ajedrez[(coordenada_x) + (coordenada_y * 8)].color))
		{
			rey->opciones.valor_opciones[rey->opciones.number_opciones] = (coordenada_x) + (coordenada_y * 8);
			ajedrez[(coordenada_x) + (coordenada_y * 8)].posible_mov = TRUE;
			rey->opciones.number_opciones++;
		}
	}

	coordenada_x = x - 1;
	coordenada_y = y;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		if((rey->color) != (ajedrez[(coordenada_x) + (coordenada_y * 8)].color))
		{
			rey->opciones.valor_opciones[rey->opciones.number_opciones] = (coordenada_x) + (coordenada_y * 8);
			ajedrez[(coordenada_x) + (coordenada_y * 8)].posible_mov = TRUE;
			rey->opciones.number_opciones++;
		}
	}

	coordenada_x = x + 1;
	coordenada_y = y;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		if((rey->color) != (ajedrez[(coordenada_x) + (coordenada_y * 8)].color))
		{
			rey->opciones.valor_opciones[rey->opciones.number_opciones] = (coordenada_x) + (coordenada_y * 8);
			ajedrez[(coordenada_x) + (coordenada_y * 8)].posible_mov = TRUE;
			rey->opciones.number_opciones++;
		}
	}

	coordenada_x = x - 1;
	coordenada_y = y + 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		if((rey->color) != (ajedrez[(coordenada_x) + (coordenada_y * 8)].color))
		{
			rey->opciones.valor_opciones[rey->opciones.number_opciones] = (coordenada_x) + (coordenada_y * 8);
			ajedrez[(coordenada_x) + (coordenada_y * 8)].posible_mov = TRUE;
			rey->opciones.number_opciones++;
		}
	}

	coordenada_x = x;
	coordenada_y = y + 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		if((rey->color) != (ajedrez[(coordenada_x) + (coordenada_y * 8)].color))
		{
			rey->opciones.valor_opciones[rey->opciones.number_opciones] = (coordenada_x) + (coordenada_y * 8);
			ajedrez[(coordenada_x) + (coordenada_y * 8)].posible_mov = TRUE;
			rey->opciones.number_opciones++;
		}
	}

	coordenada_x = x + 1;
	coordenada_y = y + 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		if((rey->color) != (ajedrez[(coordenada_x) + (coordenada_y * 8)].color))
		{
			rey->opciones.valor_opciones[rey->opciones.number_opciones] = (coordenada_x) + (coordenada_y * 8);
			ajedrez[(coordenada_x) + (coordenada_y * 8)].posible_mov = TRUE;
			rey->opciones.number_opciones++;
		}
	}
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

uint8_t fichas_jaque_sencillo(uint8_t jugador, uint8_t x, uint8_t y, struct_ficha_t ajedrez[64])
{
	uint8_t color;
	struct_ficha_t posibilidad;
	uint8_t y_min[2];
	uint8_t x_min[2];
	uint8_t status = libre;

	if(0 == jugador)
	{
		color = negras;
	}
	else
	{
		color = blancas;
	}

	/*---------------------------------TORRE REINA-------------------------------*/
	fichas_movimiento_vertical(y_min, x, y, ajedrez);
	posibilidad = ajedrez[x + (y_min[0] * 8)];

	if((posibilidad.ficha_name == torre) | (posibilidad.ficha_name == reina))
	{
		if(color == posibilidad.color)
		{
			status |= jaque;
		}
	}

	posibilidad = ajedrez[x + (y_min[1] * 8)];

	if((posibilidad.ficha_name == torre) | (posibilidad.ficha_name == reina))
	{
		if(color == posibilidad.color)
		{
			status |= jaque;
		}
	}

	fichas_movimiento_horizontal(x_min, x, y, ajedrez);

	posibilidad = ajedrez[x_min[0] + (y * 8)];
	if((posibilidad.ficha_name == torre) | (posibilidad.ficha_name == reina))
	{
		if(color == posibilidad.color)
		{
			status |= jaque;
		}
	}

	posibilidad = ajedrez[x_min[1] + (y * 8)];
	if((posibilidad.ficha_name == torre) | (posibilidad.ficha_name == reina))
	{
		if(color == posibilidad.color)
		{
			status |= jaque;
		}
	}
	/*---------------------------------ALFIL REINA-------------------------------*/
	uint8_t lim[4];
	uint8_t i;
	uint8_t limite;
	uint8_t coordenada;

	lim[limite_menos_x] = x;
	lim[limite_menos_y] = y;
	lim[limite_mas_x] = 7 - x;
	lim[limite_mas_y] = 7 - y;

	/*Caso [-k,-k]*/
	if(lim[limite_menos_x] < lim[limite_menos_y])
	{
		limite = lim[limite_menos_x];
	}
	else
	{
		limite = lim[limite_menos_y];
	}
	coordenada = limite;
	for(i = 0; i < limite; i++)
	{
		if(ninguno != ajedrez[(x - limite + i) + ((y - limite + i) * 8)].ficha_name)
		{
			coordenada = (limite - i);
		}
	}
	posibilidad = *(ajedrez + (x - coordenada) + ((y - coordenada) * 8));
	if((posibilidad.ficha_name == alfil) | (posibilidad.ficha_name == reina))
	{
		if(color == posibilidad.color)
		{
			status |= jaque;
		}
	}

	/*Caso [+k,-k]*/
	if(lim[limite_mas_x] < lim[limite_menos_y])
	{
		limite = lim[limite_mas_x];
	}
	else
	{
		limite = lim[limite_menos_y];
	}
	coordenada = limite;
	for(i = 0; i < limite; i++)
	{
		if(ninguno != ajedrez[(x + limite - i) + ((y - limite + i) * 8)].ficha_name)
		{
			coordenada = (limite - i);
		}
	}
	posibilidad = *(ajedrez + (x + coordenada) + ((y - coordenada) * 8));
	if((posibilidad.ficha_name == alfil) | (posibilidad.ficha_name == reina))
	{
		if(color == posibilidad.color)
		{
			status |= jaque;
		}
	}

	/*Caso [-k,+k]*/
	if(lim[limite_menos_x] < lim[limite_mas_y])
	{
		limite = lim[limite_menos_x];
	}
	else
	{
		limite = lim[limite_mas_y];
	}
	coordenada = limite;
	for(i = 0; i < limite; i++)
	{
		if(ninguno != ajedrez[(x - limite + i) + ((y + limite - i) * 8)].ficha_name)
		{
			coordenada = (limite - i);
		}
	}
	posibilidad = *(ajedrez + (x - coordenada) + ((y + coordenada) * 8));
	if((posibilidad.ficha_name == alfil) | (posibilidad.ficha_name == reina))
	{
		if(color == posibilidad.color)
		{
			status |= jaque;
		}
	}

	/*Caso [+k,+k]*/
	if(lim[limite_mas_x] < lim[limite_mas_y])
	{
		limite = lim[limite_mas_x];
	}
	else
	{
		limite = lim[limite_mas_y];
	}
	coordenada = limite;
	for(i = 0; i < limite; i++)
	{
		if(ninguno != ajedrez[(x + limite - i) + ((y + limite - i) * 8)].ficha_name)
		{
			coordenada = (limite - i);
		}
	}
	posibilidad = *(ajedrez + (x + coordenada) + ((y + coordenada) * 8));
	if((posibilidad.ficha_name == alfil) | (posibilidad.ficha_name == reina))
	{
		if(color == posibilidad.color)
		{
			status |= jaque;
		}
	}


	/*-----------------------------CABALLO----------------------------------*/
	uint8_t coordenada_y;
	uint8_t coordenada_x;

	coordenada_x = x + 1;
	coordenada_y = y + 2;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(caballo == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				status |= jaque;
			}
		}
	}

	coordenada_x = x + 1;
	coordenada_y = y - 2;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(caballo == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				status |= jaque;
			}
		}
	}

	coordenada_x = x + 2;
	coordenada_y = y + 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(caballo == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				status |= jaque;
			}
		}
	}

	coordenada_x = x + 2;
	coordenada_y = y - 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(caballo == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				status |= jaque;
			}
		}
	}

	coordenada_x = x - 1;
	coordenada_y = y + 2;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(caballo == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				status |= jaque;
			}
		}
	}

	coordenada_x = x - 1;
	coordenada_y = y - 2;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(caballo == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				status |= jaque;
			}
		}
	}

	coordenada_x = x - 2;
	coordenada_y = y + 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(caballo == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				status |= jaque;
			}
		}
	}

	coordenada_x = x - 2;
	coordenada_y = y - 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(caballo == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				status |= jaque;
			}
		}
	}


	/*------------------------------Peon----------------------------------*/
	if(0 == jugador)
	{
		coordenada_y = y - 1;
	}
	else
	{
		coordenada_y = y + 1;
	}

	coordenada_x = x + 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(peon == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				status |= jaque;
			}
		}
	}

	coordenada_x = x - 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(peon == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				status |= jaque;
			}
		}
	}

	return status;
}

uint8_t fichas_jaque_mate(uint8_t jugador, uint8_t x, uint8_t y, struct_ficha_t ajedrez[64])
{
	uint8_t s_jaque;
	uint8_t status = 0;
	uint8_t coordenada_x;
	uint8_t coordenada_y;
	struct_ficha_t ficha;
	struct_ficha_t rey = ajedrez[x + (8 * y)];
	uint8_t color = rey.color;

	coordenada_x = x - 1;
	coordenada_y = y - 1;
	ficha = ajedrez[coordenada_x + (8 * coordenada_y)];
	if((coordenada_y < 8) & (coordenada_x < 8) & (color != ficha.color))
	{
		s_jaque = fichas_jaque_sencillo(jugador, coordenada_x, coordenada_y, ajedrez);
		if(jaque == s_jaque)
		{
			status++;
		}
	}
	else
	{
		status++;
	}

	coordenada_x = x;
	coordenada_y = y - 1;
	ficha = ajedrez[coordenada_x + (8 * coordenada_y)];
	if((coordenada_y < 8) & (coordenada_x < 8) & (color != ficha.color))
	{
		s_jaque = fichas_jaque_sencillo(jugador, coordenada_x, coordenada_y, ajedrez);
		if(jaque == s_jaque)
		{
			status++;
		}
	}
	else
	{
		status++;
	}

	coordenada_x = x + 1;
	coordenada_y = y - 1;
	ficha = ajedrez[coordenada_x + (8 * coordenada_y)];
	if((coordenada_y < 8) & (coordenada_x < 8) & (color != ficha.color))
	{
		s_jaque = fichas_jaque_sencillo(jugador, coordenada_x, coordenada_y, ajedrez);
		if(jaque == s_jaque)
		{
			status++;
		}
	}
	else
	{
		status++;
	}

	coordenada_x = x - 1;
	coordenada_y = y;
	ficha = ajedrez[coordenada_x + (8 * coordenada_y)];
	if((coordenada_y < 8) & (coordenada_x < 8) & (color != ficha.color))
	{
		s_jaque = fichas_jaque_sencillo(jugador, coordenada_x, coordenada_y, ajedrez);
		if(jaque == s_jaque)
		{
			status++;
		}
	}
	else
	{
		status++;
	}

	coordenada_x = x + 1;
	coordenada_y = y;
	ficha = ajedrez[coordenada_x + (8 * coordenada_y)];
	if((coordenada_y < 8) & (coordenada_x < 8) & (color != ficha.color))
	{
		s_jaque = fichas_jaque_sencillo(jugador, coordenada_x, coordenada_y, ajedrez);
		if(jaque == s_jaque)
		{
			status++;
		}
	}
	else
	{
		status++;
	}

	coordenada_x = x - 1;
	coordenada_y = y + 1;
	ficha = ajedrez[coordenada_x + (8 * coordenada_y)];
	if((coordenada_y < 8) & (coordenada_x < 8) & (color != ficha.color))
	{
		s_jaque = fichas_jaque_sencillo(jugador, coordenada_x, coordenada_y, ajedrez);
		if(jaque == s_jaque)
		{
			status++;
		}
	}
	else
	{
		status++;
	}

	coordenada_x = x;
	coordenada_y = y + 1;
	ficha = ajedrez[coordenada_x + (8 * coordenada_y)];
	if((coordenada_y < 8) & (coordenada_x < 8) & (color != ficha.color))
	{
		s_jaque = fichas_jaque_sencillo(jugador, coordenada_x, coordenada_y, ajedrez);
		if(jaque == s_jaque)
		{
			status++;
		}
	}
	else
	{
		status++;
	}

	coordenada_x = x + 1;
	coordenada_y = y + 1;
	ficha = ajedrez[coordenada_x + (8 * coordenada_y)];
	if((coordenada_y < 8) & (coordenada_x < 8) & (color != ficha.color))
	{
		s_jaque = fichas_jaque_sencillo(jugador, coordenada_x, coordenada_y, ajedrez);
		if(jaque == s_jaque)
		{
			status++;
		}
	}
	else
	{
		status++;
	}

	if(8 == status)
	{
		status = jaque_mate;
	}
	else
	{
		status = jaque;
	}

	return status;
}


void fichas_ficha_jaque(struct_ficha_jaque_t* ficha, uint8_t x, uint8_t y, struct_ficha_t ajedrez[64])
{
	struct_ficha_t rey = ajedrez[x + (8 * y)];

	uint8_t color;
	struct_ficha_t posibilidad;
	uint8_t y_min[2];
	uint8_t x_min[2];

	color = rey.color;
	if(blancas == color)
	{
		color = negras;
		ficha->color = negras;
	}
	else
	{
		color = blancas;
		ficha->color = blancas;
	}



	/*---------------------------------TORRE REINA-------------------------------*/
	fichas_movimiento_vertical(y_min, x, y, ajedrez);
	posibilidad = ajedrez[x + (y_min[0] * 8)];

	if((posibilidad.ficha_name == torre) | (posibilidad.ficha_name == reina))
	{
		if(color == posibilidad.color)
		{
			ficha->ficha_name = torre;
			ficha->coordenada_x = x;
			ficha->coordenada_y = y_min[0];
		}
	}

	posibilidad = ajedrez[x + (y_min[1] * 8)];

	if((posibilidad.ficha_name == torre) | (posibilidad.ficha_name == reina))
	{
		if(color == posibilidad.color)
		{
			ficha->ficha_name = torre;
			ficha->coordenada_x = x;
			ficha->coordenada_y = y_min[1];
		}
	}

	fichas_movimiento_horizontal(x_min, x, y, ajedrez);

	posibilidad = ajedrez[x_min[0] + (y * 8)];
	if((posibilidad.ficha_name == torre) | (posibilidad.ficha_name == reina))
	{
		if(color == posibilidad.color)
		{
			ficha->ficha_name = torre;
			ficha->coordenada_x = x_min[0];
			ficha->coordenada_y = y;
		}
	}

	posibilidad = ajedrez[x_min[1] + (y * 8)];
	if((posibilidad.ficha_name == torre) | (posibilidad.ficha_name == reina))
	{
		if(color == posibilidad.color)
		{
			ficha->ficha_name = torre;
			ficha->coordenada_x = x_min[1];
			ficha->coordenada_y = y;
		}
	}
	/*---------------------------------ALFIL REINA-------------------------------*/
	uint8_t lim[4];
	uint8_t i;
	uint8_t limite;
	uint8_t coordenada;

	lim[limite_menos_x] = x;
	lim[limite_menos_y] = y;
	lim[limite_mas_x] = 7 - x;
	lim[limite_mas_y] = 7 - y;

	/*Caso [-k,-k]*/
	if(lim[limite_menos_x] < lim[limite_menos_y])
	{
		limite = lim[limite_menos_x];
	}
	else
	{
		limite = lim[limite_menos_y];
	}
	coordenada = limite;
	for(i = 0; i < limite; i++)
	{
		if(ninguno != ajedrez[(x - limite + i) + ((y - limite + i) * 8)].ficha_name)
		{
			coordenada = (limite - i);
		}
	}
	posibilidad = *(ajedrez + (x - coordenada) + ((y - coordenada) * 8));
	if((posibilidad.ficha_name == alfil) | (posibilidad.ficha_name == reina))
	{
		if(color == posibilidad.color)
		{
			ficha->ficha_name = alfil;
			ficha->coordenada_x = x - coordenada;
			ficha->coordenada_y = y - coordenada;
		}
	}

	/*Caso [+k,-k]*/
	if(lim[limite_mas_x] < lim[limite_menos_y])
	{
		limite = lim[limite_mas_x];
	}
	else
	{
		limite = lim[limite_menos_y];
	}
	coordenada = limite;
	for(i = 0; i < limite; i++)
	{
		if(ninguno != ajedrez[(x + limite - i) + ((y - limite + i) * 8)].ficha_name)
		{
			coordenada = (limite - i);
		}
	}
	posibilidad = *(ajedrez + (x + coordenada) + ((y - coordenada) * 8));
	if((posibilidad.ficha_name == alfil) | (posibilidad.ficha_name == reina))
	{
		if(color == posibilidad.color)
		{
			ficha->ficha_name = alfil;
			ficha->coordenada_x = x + coordenada;
			ficha->coordenada_y = y - coordenada;
		}
	}

	/*Caso [-k,+k]*/
	if(lim[limite_menos_x] < lim[limite_mas_y])
	{
		limite = lim[limite_menos_x];
	}
	else
	{
		limite = lim[limite_mas_y];
	}
	coordenada = limite;
	for(i = 0; i < limite; i++)
	{
		if(ninguno != ajedrez[(x - limite + i) + ((y + limite - i) * 8)].ficha_name)
		{
			coordenada = (limite - i);
		}
	}
	posibilidad = *(ajedrez + (x - coordenada) + ((y + coordenada) * 8));
	if((posibilidad.ficha_name == alfil) | (posibilidad.ficha_name == reina))
	{
		if(color == posibilidad.color)
		{
			ficha->ficha_name = alfil;
			ficha->coordenada_x = x - coordenada;
			ficha->coordenada_y = y + coordenada;
		}
	}

	/*Caso [+k,+k]*/
	if(lim[limite_mas_x] < lim[limite_mas_y])
	{
		limite = lim[limite_mas_x];
	}
	else
	{
		limite = lim[limite_mas_y];
	}
	coordenada = limite;
	for(i = 0; i < limite; i++)
	{
		if(ninguno != ajedrez[(x + limite - i) + ((y + limite - i) * 8)].ficha_name)
		{
			coordenada = (limite - i);
		}
	}
	posibilidad = *(ajedrez + (x + coordenada) + ((y + coordenada) * 8));
	if((posibilidad.ficha_name == alfil) | (posibilidad.ficha_name == reina))
	{
		if(color == posibilidad.color)
		{
			ficha->ficha_name = alfil;
			ficha->coordenada_x = x + coordenada;
			ficha->coordenada_y = y + coordenada;
		}
	}


	/*-----------------------------CABALLO----------------------------------*/
	uint8_t coordenada_y;
	uint8_t coordenada_x;

	coordenada_x = x + 1;
	coordenada_y = y + 2;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(caballo == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				ficha->ficha_name = caballo;
				ficha->coordenada_x = coordenada_x;
				ficha->coordenada_y = coordenada_y;
			}
		}
	}

	coordenada_x = x + 1;
	coordenada_y = y - 2;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(caballo == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				ficha->ficha_name = caballo;
				ficha->coordenada_x = coordenada_x;
				ficha->coordenada_y = coordenada_y;
			}
		}
	}

	coordenada_x = x + 2;
	coordenada_y = y + 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(caballo == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				ficha->ficha_name = caballo;
				ficha->coordenada_x = coordenada_x;
				ficha->coordenada_y = coordenada_y;
			}
		}
	}

	coordenada_x = x + 2;
	coordenada_y = y - 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(caballo == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				ficha->ficha_name = caballo;
				ficha->coordenada_x = coordenada_x;
				ficha->coordenada_y = coordenada_y;
			}
		}
	}

	coordenada_x = x - 1;
	coordenada_y = y + 2;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(caballo == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				ficha->ficha_name = caballo;
				ficha->coordenada_x = coordenada_x;
				ficha->coordenada_y = coordenada_y;
			}
		}
	}

	coordenada_x = x - 1;
	coordenada_y = y - 2;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(caballo == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				ficha->ficha_name = caballo;
				ficha->coordenada_x = coordenada_x;
				ficha->coordenada_y = coordenada_y;
			}
		}
	}

	coordenada_x = x - 2;
	coordenada_y = y + 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(caballo == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				ficha->ficha_name = caballo;
				ficha->coordenada_x = coordenada_x;
				ficha->coordenada_y = coordenada_y;
			}
		}
	}

	coordenada_x = x - 2;
	coordenada_y = y - 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(caballo == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				ficha->ficha_name = caballo;
				ficha->coordenada_x = coordenada_x;
				ficha->coordenada_y = coordenada_y;
			}
		}
	}


	/*------------------------------Peon----------------------------------*/
	if(blancas == color)
	{
		coordenada_y = y - 1;
	}
	else
	{
		coordenada_y = y + 1;
	}

	coordenada_x = x + 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(peon == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				ficha->ficha_name = peon;
				ficha->coordenada_x = coordenada_x;
				ficha->coordenada_y = coordenada_y;
			}
		}
	}

	coordenada_x = x - 1;
	if((coordenada_y < 8) & (coordenada_x < 8))
	{
		posibilidad = ajedrez[(coordenada_x) + (coordenada_y * 8)];
		if(peon == posibilidad.ficha_name)
		{
			if(color == posibilidad.color)
			{
				ficha->ficha_name = peon;
				ficha->coordenada_x = coordenada_x;
				ficha->coordenada_y = coordenada_y;
			}
		}
	}
}

uint8_t fichas_salvar_jaque(struct_ficha_jaque_t* ficha, uint8_t x, uint8_t y, struct_ficha_t ajedrez[64])
{
	uint8_t status = jaque_mate;
	uint8_t i;
	uint8_t l;
	uint8_t m;
	uint8_t name_ficha = ficha->ficha_name;
	uint8_t x_ficha = ficha->coordenada_x;
	uint8_t y_ficha = ficha->coordenada_y;

	ficha->casillas.number_opciones = 0;
	uint8_t color = ajedrez[x + (8 * y)].color;
	uint8_t y_aux;
	uint8_t x_aux;

	struct_ficha_t* ficha_aux;

	switch(name_ficha)
	{
	/*-----------------------------------------Rescate de un peón-----------------------------------------------*/
	case peon:
		ficha->casillas.number_opciones = 1;
		ficha->casillas.valor_opciones[0] = x_ficha + (y_ficha * 8);
		break;
	/*-----------------------------------------Rescate de una caballo-------------------------------------------*/
	case caballo:
		ficha->casillas.number_opciones = 1;
		ficha->casillas.valor_opciones[0] = x_ficha + (y_ficha * 8);
		break;
	/*-----------------------------------------Rescate de un alfil----------------------------------------------*/
	case alfil:

		break;
	/*-----------------------------------------Rescate de una torre---------------------------------------------*/
	case torre:
		if(x_ficha == x)
		{
			if(y_ficha < y)
			{
				for(y_aux = y_ficha; y_aux < y; y_aux++)
				{
					ficha->casillas.valor_opciones[ficha->casillas.number_opciones] = x_ficha + (y_ficha * 8);
					ficha->casillas.number_opciones++;
				}
			}
			else
			{
				for(y_aux = y_ficha; y_aux > y; y_aux--)
				{
					ficha->casillas.valor_opciones[ficha->casillas.number_opciones] = x_ficha + (y_ficha * 8);
					ficha->casillas.number_opciones++;
				}
			}
		}
		else
		{
			if(x_ficha < x)
			{
				for(x_aux = x_ficha; x_aux < x; x_aux++)
				{
					ficha->casillas.valor_opciones[ficha->casillas.number_opciones] = x_ficha + (y_ficha * 8);
					ficha->casillas.number_opciones++;
				}
			}
			else
			{
				for(x_aux = x_ficha; x_aux > x; x_aux--)
				{
					ficha->casillas.valor_opciones[ficha->casillas.number_opciones] = x_ficha + (y_ficha * 8);
					ficha->casillas.number_opciones++;
				}
			}
		}
		break;
	default:
		break;
	}

	for(l = 0; l < 64; l++)
	{
		ficha_aux = (ajedrez + l);
		if(color == ficha_aux->color)
		{
			name_ficha = ficha_aux->ficha_name;
			switch(name_ficha)
			{
			case peon:
				fichas_peon_mov((l % 8), (l / 8), ajedrez);
				break;
			case caballo:
				fichas_caballo_mov((l % 8), (l / 8), ajedrez);
				break;
			case alfil:
				fichas_alfil_mov((l % 8), (l / 8), ajedrez);
				break;
			case torre:
				fichas_torre_mov((l % 8), (l / 8), ajedrez);
				break;
			default:
				break;

			for(m = 0; m < ficha_aux->opciones.number_opciones; m++)
			{
				for(i = 0; i < ficha->casillas.number_opciones; i++)
				{
					if(ficha->casillas.valor_opciones[i] == ficha_aux->opciones.valor_opciones[m])
					{
						status = jaque;
					}
				}
			}

			for(m = 0; m < ficha_aux->opciones.number_opciones; m++)
			{
				ajedrez[ficha_aux->opciones.valor_opciones[i]].posible_mov = FALSE;
			}
			ficha_aux->opciones.number_opciones = 0;
			}
		}
	}

	return status;
}
