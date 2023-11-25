/*
 * tablero.h
 *
 *  Created on: 11 nov 2023
 *      Author: brand
 */

#ifndef TABLERO_H_
#define TABLERO_H_

#include "UART.h"
#include "fichas.h"
#include "control_nintendo.h"

typedef enum{
	s_none_t,
	s_change_t
}status_player_t;

void tablero_init(void);
void tablero_acomodo_arreglo(void);
void tablero_print_fichas(void);

void tablero_switch_string(uint8_t* array, uint8_t old_character, uint8_t new_character);
void tablero_movimiento(uint8_t x_old, uint8_t y_old, uint8_t x_new, uint8_t y_new);

uint8_t tablero_control(uint8_t* jugador, uint8_t* array_button);

void tablero_print_tablero(void);

#endif /* TABLERO_H_ */
