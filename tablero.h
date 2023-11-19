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

void tablero_init(void);
void tablero_acomodo_arreglo(void);
void tablero_print_fichas(void);

void tablero_switch_string(uint8_t* array, uint8_t old_character, uint8_t new_character);

uint8_t tablero_control(void);

#endif /* TABLERO_H_ */
