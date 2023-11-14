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

#endif /* TABLERO_H_ */
