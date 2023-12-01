/**
 * @file temporizador.h
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief  It controls the operation
 * 			of temporizador
 *
 */

#ifndef TEMPORIZADOR_H_
#define TEMPORIZADOR_H_

#include "UART.h"
#include <stdint.h>
#include "PIT.h"
#include "NVIC.h"

#define NUM_TO_ASCII(a) (a + 0x30)

#define TIEMPO_CH2 (50000000U)

/*!
 * @brief Function of initialization of temporizador
 *
 * @param uint8_t minuto_inicial
 * @param uint8_t segundo_inicial
 */
void temporizador_init(uint8_t minuto_inicial, uint8_t segundo_inicial);

/*!
 * @brief Function of move the cursor
 *
 * @param UART_channel_t UART_name
 * @param uint8_t posicion
 * @param uint8_t renglon
 */
void temporizador_mover_cursor(UART_channel_t UART_name, uint8_t posicion, uint8_t renglon);

/*!
 * @brief Function of update the time a specific player
 *
 * @param uint8_t turno
 */
uint8_t temporizador_update(uint8_t turno);

/*!
 * @brief Function of show the new time a specific player
 */
void temporizador_new_time_print(void);

/*!
 * @brief Function of print a number
 *
 * @param UART_channel_t UART_name
 * @param uint8_t posicion
 * @param uint8_t numero
 */
void temporizador_numero_print(UART_channel_t UART_name, uint8_t posicion, uint8_t numero);

/*!
 * @brief Function of print a headers
 */
void temporizador_timer_encabezados_print(void);

#endif /* TEMPORIZADOR_H_ */
