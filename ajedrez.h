/**
 * @file ajedrez.h
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief 	It controls the operation
 * 			and initialization of the all game
 */

#ifndef AJEDREZ_H_
#define AJEDREZ_H_

#include "tablero.h"
#include "control_nintendo.h"
#include "temporizador.h"
#include "memory.h"

#define TIEMPO_MINUTOS	(15U)
#define TIEMPO_SEGUNDOS	(00U)

#define DIF_SELECTOR	(6U)

#define X_C_SANGRIA		(25U)
#define X_S_SANGRIA		(10U)

typedef void(*ventana_function)(uint8_t* modo);
typedef enum{v_inicio, v_save, v_juego, v_pausa, v_tablas, v_espera, v_derrota, v_leer, v_repeticion} state_ventana_t;
typedef enum{log_0, log_1, log_2, log_3, log_4, log_5} log_t;
typedef enum{jugador_1, jugador_2} jugador_t;

/*!
 * @brief Initialization of the ajedrez game
 */
void ajedrez_init(void);

/*!
 * @brief Performs chess control
 */
void ajedrez_control(void);

/*!
 * @brief Function of window of menu
 *
 * @param uint8_t* modo
 */
void ajedrez_v_menu(uint8_t * modo);

/*!
 * @brief Function of window of save
 *
 * @param uint8_t* modo
 */
void ajedrez_v_save(uint8_t * modo);

/*!
 * @brief Function of window of juego in general
 *
 * @param uint8_t* modo
 */
void ajedrez_v_juego(uint8_t * modo);

/*!
 * @brief Function of window of pausa
 *
 * @param uint8_t* modo
 */
void ajedrez_v_pausa(uint8_t * modo);

/*!
 * @brief Function of window of tablas
 *
 * @param uint8_t* modo
 */
void ajedrez_v_tablas(uint8_t * modo);

/*!
 * @brief Function of window of espera
 *
 * @param uint8_t* modo
 */
void ajedrez_v_espera(uint8_t * modo);

/*!
 * @brief Function of window of derrota
 *
 * @param uint8_t* modo
 */
void ajedrez_v_derrota(uint8_t * modo);

/*!
 * @brief Function of window of leer log
 *
 * @param uint8_t* modo
 */
void ajedrez_v_leer_log(uint8_t * modo);

/*!
 * @brief Function of window of repeticion
 *
 * @param uint8_t* modo
 */
void ajedrez_v_repeticion(uint8_t * modo);

#endif /* AJEDREZ_H_ */
