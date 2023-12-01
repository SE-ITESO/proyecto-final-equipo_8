/**
 * @file tablero.h
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief  It controls the operation
 * 			of the board in the game
 *
 */

#ifndef TABLERO_H_
#define TABLERO_H_

#include "UART.h"
#include "fichas.h"
#include "control_nintendo.h"
#include "memory.h"
#include "temporizador.h"
#include "alarma.h"

#define MULT_RENGLON	(8U)

typedef enum{
	s_none_t,
	s_change_t,
	s_jaque_mate
}status_player_t;

/*!
 * @brief Function to initialize the board
 */
void tablero_init(void);

/*!
 * @brief Function to accommodate the array
 */
void tablero_acomodo_arreglo(void);

/*!
 * @brief Function to show the chess pieces in tera term
 */
void tablero_print_fichas(void);

/*!
 * @brief Function to switch a element in a specific array
 *
 * @param uint8_t* array
 * @param uint8_t old_character
 * @param uint8_t new_character
 */
void tablero_switch_string(uint8_t* array, uint8_t old_character, uint8_t new_character);

/*!
 * @brief Function to realize a movement
 *
 * @param uint8_t x_old
 * @param uint8_t y_old
 * @param uint8_t x_new
 * @param uint8_t y_new
 */
void tablero_movimiento(uint8_t x_old, uint8_t y_old, uint8_t x_new, uint8_t y_new);

/*!
 * @brief Function to control the tablero
 *
 * @param uint8_t* jugador
 * @param uint8_t* array_button
 * @param uint8_t* reinicio
 *
 * @retval uint8_t status of the game
 */
uint8_t tablero_control(uint8_t* jugador, uint8_t* array_button, uint8_t* reinicio);

/*!
 * @brief Function to print tablero with chess pieces
 */
void tablero_print_tablero(void);

/*!
 * @brief Function to assign a log number
 *
 * @param uint8_t number
 */
void tablero_assign_log_number(uint8_t number);

/*!
 * @brief Function to init a replay
 *
 * @param uint8_t log_number
 */
void tablero_repeticion_init(uint8_t log_number);

/*!
 * @brief Function to move forward in movements
 */
void tablero_avanza_movimiento(void);

#endif /* TABLERO_H_ */
