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

typedef void(*funct_print_ficha)(void);

typedef enum{
	indefinido,
	blancas,
	negras,
	azul,
	cyan
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

typedef struct
{
	name_ficha_t ficha_name;
	funct_print_ficha print_ficha;
	color_ficha_t color;
	uint8_t offset[2];
}struct_ficha_t;

void fichas_config(struct_ficha_t* ficha, name_ficha_t name, color_ficha_t color);

void fichas_color(color_ficha_t color);

void fichas_peon_print(void);
void fichas_torre_print(void);
void fichas_alfil_print(void);
void fichas_caballo_print(void);
void fichas_reina_print(void);
void fichas_rey_print(void);

void fichas_vacio_print(void);

#endif /* FICHAS_H_ */
