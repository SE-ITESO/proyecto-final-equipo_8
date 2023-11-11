/*
 * fichas.h
 *
 *  Created on: 11 nov 2023
 *      Author: brand
 */

#ifndef FICHAS_H_
#define FICHAS_H_

#include "UART.h"

#define LLENO	(219U)
#define VACIO 	(32U)

void fichas_peon_print(void);
void fichas_torre_print(void);
void fichas_alfil_print(void);
void fichas_caballo_print(void);

#endif /* FICHAS_H_ */
