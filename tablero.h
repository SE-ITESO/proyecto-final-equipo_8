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

#define NUM_TO_ASCII(a) (a + 0x30)

void tablero_mover_cursor (uint16_t x, uint8_t y);
void tablero_init(void);
void tablero_acomodo_arreglo(void);
void tablero_print_fichas(void);

#endif /* TABLERO_H_ */
