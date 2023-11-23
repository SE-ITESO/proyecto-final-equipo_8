/*
 * tablero.c
 *
 *  Created on: 11 nov 2023
 *      Author: brand
 */

#include "tablero.h"

static uint8_t g_modo = 1;

static struct_ficha_t g_ficha_generica =
{
		indefinido,
		fichas_vacio_print,
		ninguno,
		FALSE
};

static funct_mov_ficha g_funct_movimiento[] =
{
		fichas_peon_mov,
		fichas_torre_mov,
		fichas_alfil_mov
};

static struct_ficha_t g_array_ajedrez[64];

void tablero_switch_string(uint8_t* array, uint8_t old_character, uint8_t new_character)
{
	int i = 0;
	while(0 != *(array + i)){
		if(old_character == (*(array + i)))
		{
			*(array + i) = new_character;
		}
		i++;
	}
}

void tablero_init(void)
{
	fichas_color(UART_0, azul);
	fichas_color(UART_4, azul);
	uint8_t i;
	uint8_t l;
	uint16_t temp_x;
	uint8_t temp_y;
	for(l = 0; l < 8; l++)
	{
		temp_y = (l * 8) + 1;
		for(i = 0; i < 4; i++)
		{
			temp_x = (((l + 1) % 2) * 16) + (i * 32) + 1;
			fichas_vacio_print(ninguno, temp_x, temp_y);
		}
	}

	tablero_acomodo_arreglo();
	tablero_print_fichas();
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
	uint16_t coordenada_x = 0;
	uint8_t coordenada_y = 0;
	/*Impresión de fichas negras*/
	for(i = 0; i < 16; i++)
	{
		coordenada_x = ((i % 8) * 16) + 1;
		coordenada_y = ((i / 8) * 8) + 1;
		g_array_ajedrez[i].print_ficha(g_array_ajedrez[i].color, coordenada_x, coordenada_y);
	}

	/*Impresión de fichas blancas*/
	for(i = 0; i < 16; i++)
	{
		coordenada_x = (((i + 48) % 8) * 16) + 1;
		coordenada_y = (((i + 48) / 8) * 8) + 1;
		g_array_ajedrez[i + 48].print_ficha(g_array_ajedrez[i + 48].color, coordenada_x, coordenada_y);
	}
}

uint8_t tablero_control(uint8_t* jugador, uint8_t* array_button)
{
	static uint8_t coordenada_x = 0;
	static uint8_t coordenada_y = 7;
	static struct_ficha_t ficha;
	static struct_ficha_t ficha_seleccionada;
	static uint8_t x_selec = 0;
	static uint8_t y_selec = 0;
	uint8_t temporal;
	switch(g_modo)
	{

	case 0:
		if(FALSE != *(array_button + RIGHT))
		{
			*(array_button + RIGHT) = FALSE;

			fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			temporal = (coordenada_x + coordenada_y) % 2;
			if(0 == temporal)
			{
				fichas_vacio_UART((*jugador) * 4, VACIO);
			}
			else
			{
				fichas_color((*jugador) * 4, azul);
				fichas_vacio_UART((*jugador) * 4, LLENO);
			}
			if(ninguno != ficha.ficha_name)
			{
				if(0 == *jugador)
				{
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
				}
			}
			if(7 == coordenada_x)
			{
				coordenada_x = 0;
			}
			else
			{
				coordenada_x ++;
			}
			g_modo = 1;
		}
		else if(FALSE != *(array_button + LEFT))
		{
			*(array_button + LEFT) = FALSE;

			fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			temporal = (coordenada_x + coordenada_y) % 2;
			if(0 == temporal)
			{
				fichas_vacio_UART((*jugador) * 4, VACIO);
			}
			else
			{
				fichas_color((*jugador) * 4, azul);
				fichas_vacio_UART((*jugador) * 4, LLENO);
			}
			if(ninguno != ficha.ficha_name)
			{
				if(0 == *jugador)
				{
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
				}
			}
			if(0 == coordenada_x)
			{
				coordenada_x = 7;
			}
			else
			{
				coordenada_x --;
			}
			g_modo = 1;
		}
		else if(FALSE != *(array_button + UP))
		{
			*(array_button + UP) = FALSE;

			fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			temporal = (coordenada_x + coordenada_y) % 2;
			if(0 == temporal)
			{
				fichas_vacio_UART((*jugador) * 4, VACIO);
			}
			else
			{
				fichas_color((*jugador) * 4, azul);
				fichas_vacio_UART((*jugador) * 4, LLENO);
			}
			if(ninguno != ficha.ficha_name)
			{
				if(0 == *jugador)
				{
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
				}
			}
			if(0 == coordenada_y)
			{
				coordenada_y = 7;
			}
			else
			{
				coordenada_y --;
			}
			g_modo = 1;
		}
		else if(FALSE != *(array_button + DOWN))
		{
			*(array_button + DOWN) = FALSE;

			fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			temporal = (coordenada_x + coordenada_y) % 2;
			if(0 == temporal)
			{
				fichas_vacio_UART((*jugador) * 4, VACIO);
			}
			else
			{
				fichas_color((*jugador) * 4, azul);
				fichas_vacio_UART((*jugador) * 4, LLENO);
			}
			if(ninguno != ficha.ficha_name)
			{
				if(0 == *jugador)
				{
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
				}
			}
			if(7 == coordenada_y)
			{
				coordenada_y = 0;
			}
			else
			{
				coordenada_y ++;
			}
			g_modo = 1;
		}
		else if(FALSE != *(array_button + A))
		{
			*(array_button + A) = FALSE;

			if(0 == *jugador)
			{
				if(blancas == ficha.color)
				{
					fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
					fichas_vacio_print(indefinido, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
					g_modo = 2;
				}
			}
			else
			{
				if(negras == ficha.color)
				{
					fichas_mover_cursor((*jugador) * 4, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
					fichas_vacio_print(indefinido, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
					g_modo = 2;
				}
			}
		}
		break;

	case 1:
		if(0 == *jugador)
		{
			ficha = *(g_array_ajedrez + coordenada_x + (coordenada_y * 8));
		}
		else
		{
			ficha = *(g_array_ajedrez + (7 - coordenada_x) + ((7 - coordenada_y) * 8));
		}
		fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
		fichas_color((*jugador) * 4, verde);
		fichas_vacio_UART((*jugador) * 4, LLENO);
		if(ninguno != ficha.ficha_name)
		{
			if(0 == *jugador)
			{
				ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			}
			else
			{
				ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
			}
		}
		g_modo = 0;
		break;

	case 2:
		if(0 == *jugador)
		{
			g_funct_movimiento[ficha.ficha_name - 1](coordenada_x, coordenada_y, g_array_ajedrez);
		}
		else
		{
			g_funct_movimiento[ficha.ficha_name - 1](7 - coordenada_x, 7 - coordenada_y, g_array_ajedrez);
		}

		if(0 == *jugador)
		{
			ficha = *(g_array_ajedrez + coordenada_x + (coordenada_y * 8));
			ficha_seleccionada = *(g_array_ajedrez + coordenada_x + (coordenada_y * 8));
		}
		else
		{
			ficha = *(g_array_ajedrez + (7 - coordenada_x) + ((7 - coordenada_y) * 8));
			ficha_seleccionada = *(g_array_ajedrez + (7 - coordenada_x) + ((7 - coordenada_y) * 8));
		}

		x_selec = coordenada_x;
		y_selec = coordenada_y;
		fichas_mostrar_opciones(&(ficha_seleccionada.opciones), *jugador, g_array_ajedrez);
		if(0 != ficha_seleccionada.opciones.number_opciones)
		{
			fichas_color((*jugador) * 4, rojo);
			g_modo = 3;
		}
		else
		{
			g_modo = 1;
		}
		break;

	case 3:
		if(FALSE != *(array_button + RIGHT))
		{
			*(array_button + RIGHT) = FALSE;

			fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			temporal = (coordenada_x + coordenada_y) % 2;
			if(0 == temporal)
			{
				fichas_vacio_UART((*jugador) * 4, VACIO);
			}
			else
			{
				fichas_color((*jugador) * 4, azul);
				fichas_vacio_UART((*jugador) * 4, LLENO);
			}
			/*Opcion para imprimir el color previo*/
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(ficha.posible_mov)
			{
				fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				fichas_print_opcion((*jugador) * 4);
			}
			if(ninguno != ficha.ficha_name)
			{
				if(0 == *jugador)
				{
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
				}
			}
			if(7 == coordenada_x)
			{
				coordenada_x = 0;
			}
			else
			{
				coordenada_x ++;
			}
			g_modo = 4;
		}
		else if(FALSE != *(array_button + LEFT))
		{
			*(array_button + LEFT) = FALSE;

			fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			temporal = (coordenada_x + coordenada_y) % 2;
			if(0 == temporal)
			{
				fichas_vacio_UART((*jugador) * 4, VACIO);
			}
			else
			{
				fichas_color((*jugador) * 4, azul);
				fichas_vacio_UART((*jugador) * 4, LLENO);
			}
			/*Opcion para imprimir el color previo*/
			if(ficha.posible_mov)
			{
				fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				fichas_print_opcion((*jugador) * 4);
			}
			if(ninguno != ficha.ficha_name)
			{
				if(0 == *jugador)
				{
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
				}
			}
			if(0 == coordenada_x)
			{
				coordenada_x = 7;
			}
			else
			{
				coordenada_x --;
			}
			g_modo = 4;
		}
		else if(FALSE != *(array_button + UP))
		{
			*(array_button + UP) = FALSE;

			fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			temporal = (coordenada_x + coordenada_y) % 2;
			if(0 == temporal)
			{
				fichas_vacio_UART((*jugador) * 4, VACIO);
			}
			else
			{
				fichas_color((*jugador) * 4, azul);
				fichas_vacio_UART((*jugador) * 4, LLENO);
			}
			/*Opcion para imprimir el color previo*/
			if(ficha.posible_mov)
			{
				fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				fichas_print_opcion((*jugador) * 4);
			}
			if(ninguno != ficha.ficha_name)
			{
				if(0 == *jugador)
				{
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
				}
			}
			if(0 == coordenada_y)
			{
				coordenada_y = 7;
			}
			else
			{
				coordenada_y --;
			}
			g_modo = 4;
		}
		else if(FALSE != *(array_button + DOWN))
		{
			*(array_button + DOWN) = FALSE;

			fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			temporal = (coordenada_x + coordenada_y) % 2;
			if(0 == temporal)
			{
				fichas_vacio_UART((*jugador) * 4, VACIO);
			}
			else
			{
				fichas_color((*jugador) * 4, azul);
				fichas_vacio_UART((*jugador) * 4, LLENO);
			}
			/*Opcion para imprimir el color previo*/
			if(ficha.posible_mov)
			{
				fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				fichas_print_opcion((*jugador) * 4);
			}
			if(ninguno != ficha.ficha_name)
			{
				if(0 == *jugador)
				{
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
				}
			}
			if(7 == coordenada_y)
			{
				coordenada_y = 0;
			}
			else
			{
				coordenada_y ++;
			}
			g_modo = 4;
		}
		else if(FALSE != *(array_button + A))
		{
			*(array_button + A) = FALSE;
			if(ficha.posible_mov)
			{
				if(0 == *jugador)
				{
					fichas_clear_opciones(&((g_array_ajedrez + x_selec + (y_selec * 8))->opciones), (*jugador) * 4, g_array_ajedrez);
					tablero_movimiento(x_selec, y_selec, coordenada_x, coordenada_y);
				}
				else
				{
					fichas_clear_opciones(&((g_array_ajedrez + (7 - x_selec) + ((7 - y_selec) * 8))->opciones), (*jugador) * 4, g_array_ajedrez);
					tablero_movimiento(7 - x_selec, 7 - y_selec, 7 - coordenada_x, 7 - coordenada_y);
				}
				g_modo = 5;
			}
		}
		break;

	case 4:
		if(0 == *jugador)
		{
			ficha = *(g_array_ajedrez + coordenada_x + (coordenada_y * 8));
		}
		else
		{
			ficha = *(g_array_ajedrez + (7 - coordenada_x) + ((7 - coordenada_y) * 8));
		}

		fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
		fichas_color((*jugador) * 4, rojo);
		fichas_vacio_UART((*jugador) * 4, LLENO);

		if(ninguno != ficha.ficha_name)
		{
			if(0 == *jugador)
			{
				ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			}
			else
			{
				ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
			}
		}
		g_modo = 3;
		break;

	case 5:
		(*jugador) = 1 - (*jugador);
		g_modo = 1;

		break;
	}
	return 0;
}

void tablero_movimiento(uint8_t x_old, uint8_t y_old, uint8_t x_new, uint8_t y_new)
{
	struct_ficha_t ficha;
	ficha = *(g_array_ajedrez + x_old + (y_old * 8));
	*(g_array_ajedrez + x_new + (y_new * 8)) = ficha;

	fichas_vacio_print(indefinido, (x_new * 16) + 1, (y_new * 8) + 1);
	ficha.print_ficha(ficha.color, (x_new * 16) + 1, (y_new * 8) + 1);

	fichas_config(&ficha, ninguno, indefinido);
	*(g_array_ajedrez + x_old + (y_old * 8)) = ficha;

	ficha.print_ficha(ficha.color, (x_old * 16) + 1, (y_old * 8) + 1);
}
