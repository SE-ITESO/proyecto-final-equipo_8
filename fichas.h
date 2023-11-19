/*
 * fichas.h
 *
 *  Created on: 11 nov 2023
 *      Author: brand
 */

#ifndef FICHAS_H_
#define FICHAS_H_

#include "UART.h"

#define LLENO		(219U)
#define UP_LLENO	(223U)
#define DOWN_LLENO	(220U)
#define VACIO 		(32U)

#define NUM_TO_ASCII(a) (a + 0x30)

typedef enum{
	indefinido,
	blancas,
	negras,
	azul,
	cyan,
	rojo,
	verde
}color_ficha_t;

typedef enum{
	ninguno,
	peon,
	torre,
	alfil,
	caballo,
	reina,
	rey
}name_ficha_t;

typedef enum{
	offset_x,
	offset_y
}offset_t;

typedef void(*funct_print_ficha)(color_ficha_t color, uint16_t x, uint8_t y);

typedef struct
{
	name_ficha_t ficha_name;
	funct_print_ficha print_ficha;
	color_ficha_t color;
}struct_ficha_t;

void fichas_mover_cursor(UART_channel_t UART_name, uint16_t x, uint8_t y);

void fichas_config(struct_ficha_t* ficha, name_ficha_t name, color_ficha_t color);

void fichas_color(UART_channel_t UART_name, color_ficha_t color);

void fichas_peon_print(color_ficha_t color, uint16_t x, uint8_t y);
void fichas_peon_UART(UART_channel_t UART_name);

void fichas_torre_print(color_ficha_t color, uint16_t x, uint8_t y);
void fichas_torre_UART(UART_channel_t UART_name);

void fichas_alfil_print(color_ficha_t color, uint16_t x, uint8_t y);
void fichas_alfil_UART(UART_channel_t UART_name);

void fichas_caballo_print(color_ficha_t color, uint16_t x, uint8_t y);
void fichas_caballo_UART(UART_channel_t UART_name);

void fichas_reina_print(color_ficha_t color, uint16_t x, uint8_t y);
void fichas_reina_UART(UART_channel_t UART_name);

void fichas_rey_print(color_ficha_t color, uint16_t x, uint8_t y);
void fichas_rey_UART(UART_channel_t UART_name);

void fichas_vacio_print(color_ficha_t color, uint16_t x, uint8_t y);
void fichas_vacio_UART(UART_channel_t UART_name, uint8_t color);

void fichas_seleccion_print(UART_channel_t UART_name, color_ficha_t color);

#endif /* FICHAS_H_ */
