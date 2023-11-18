/*
 * ajedrez.h
 *
 *  Created on: 14 nov 2023
 *      Author: brand
 */

#ifndef AJEDREZ_H_
#define AJEDREZ_H_

#include "tablero.h"

typedef void(*ventana_function)(uint8_t* modo);
typedef enum{v_inicio} state_ventana_t;

void ajedrez_init(void);

void ajedrez_v_menu(uint8_t * modo);
void ajedrez_control(void);


#endif /* AJEDREZ_H_ */
