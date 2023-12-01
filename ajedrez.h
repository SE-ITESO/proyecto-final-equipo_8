/*
 * ajedrez.h
 *
 *  Created on: 14 nov 2023
 *      Author: brand
 */

#ifndef AJEDREZ_H_
#define AJEDREZ_H_

#include "tablero.h"
#include "control_nintendo.h"
#include "temporizador.h"
#include "memory.h"

typedef void(*ventana_function)(uint8_t* modo);
typedef enum{v_inicio, v_save, v_juego, v_pausa, v_tablas, v_espera, v_derrota, v_leer, v_repeticion} state_ventana_t;
typedef enum{log_0, log_1, log_2, log_3, log_4, log_5} log_t;
typedef enum{jugador_1, jugador_2} jugador_t;

void ajedrez_init(void);
void ajedrez_control(void);

void ajedrez_v_menu(uint8_t * modo);
void ajedrez_v_save(uint8_t * modo);
void ajedrez_v_juego(uint8_t * modo);
void ajedrez_v_pausa(uint8_t * modo);
void ajedrez_v_tablas(uint8_t * modo);
void ajedrez_v_espera(uint8_t * modo);
void ajedrez_v_derrota(uint8_t * modo);
void ajedrez_v_leer_log(uint8_t * modo);
void ajedrez_v_repeticion(uint8_t * modo);

#endif /* AJEDREZ_H_ */
