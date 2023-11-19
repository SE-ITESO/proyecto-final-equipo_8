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
	verde,
	amarillo
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
	uint8_t number_opciones;
	uint8_t valor_opciones[35];
}struct_opciones_t;

typedef struct
{
	name_ficha_t ficha_name;
	funct_print_ficha print_ficha;
	color_ficha_t color;
	uint8_t posible_mov;
	struct_opciones_t opciones;
}struct_ficha_t;

typedef void(*funct_mov_ficha)(uint8_t x, uint8_t y, struct_ficha_t ajedrez[64]);

void fichas_mover_cursor(UART_channel_t UART_name, uint16_t x, uint8_t y);

void fichas_config(struct_ficha_t* ficha, name_ficha_t name, color_ficha_t color);

void fichas_color(UART_channel_t UART_name, color_ficha_t color);

void fichas_peon_print(color_ficha_t color, uint16_t x, uint8_t y);
void fichas_peon_UART(UART_channel_t UART_name);
void fichas_peon_mov(uint8_t x, uint8_t y, struct_ficha_t ajedrez[64]);

void fichas_torre_print(color_ficha_t color, uint16_t x, uint8_t y);
void fichas_torre_UART(UART_channel_t UART_name);
void fichas_torre_mov(uint8_t x, uint8_t y, struct_ficha_t ajedrez[64]);


void fichas_alfil_print(color_ficha_t color, uint16_t x, uint8_t y);
void fichas_alfil_UART(UART_channel_t UART_name);
void fichas_alfil_mov(uint8_t x, uint8_t y, struct_ficha_t ajedrez[64]);


void fichas_caballo_print(color_ficha_t color, uint16_t x, uint8_t y);
void fichas_caballo_UART(UART_channel_t UART_name);
void fichas_caballo_mov(uint8_t x, uint8_t y, struct_ficha_t ajedrez[64]);


void fichas_reina_print(color_ficha_t color, uint16_t x, uint8_t y);
void fichas_reina_UART(UART_channel_t UART_name);
void fichas_reina_mov(uint8_t x, uint8_t y, struct_ficha_t ajedrez[64]);


void fichas_rey_print(color_ficha_t color, uint16_t x, uint8_t y);
void fichas_rey_UART(UART_channel_t UART_name);
void fichas_rey_mov(uint8_t x, uint8_t y, struct_ficha_t ajedrez[64]);


void fichas_vacio_print(color_ficha_t color, uint16_t x, uint8_t y);
void fichas_vacio_UART(UART_channel_t UART_name, uint8_t color);


void fichas_seleccion_print(UART_channel_t UART_name, color_ficha_t color);

void fichas_print_opcion(uint8_t UART_num);
void fichas_mostrar_opciones(struct_opciones_t* posibilidades, uint8_t jugador, struct_ficha_t ajedrez[64]);

void fichas_clear_opciones(struct_opciones_t* posibilidades, UART_channel_t UART_name, struct_ficha_t ajedrez[64]);

#endif /* FICHAS_H_ */
