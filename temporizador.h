/*

 */

#ifndef TEMPORIZADOR_H_
#define TEMPORIZADOR_H_

#include "UART.h"
#include <stdint.h>

#define NUM_TO_ASCII(a) (a + 0x30)

#define TIEMPO_CH2 (10500000U)

void temporizador_init(uint8_t minuto_inicial, uint8_t segundo_inicial);
void temporizador_cero_print(UART_channel_t UART_name, uint8_t posicion);
void temporizador_mover_cursor(UART_channel_t UART_name, uint8_t posicion, uint8_t renglon);
void temporizador_cero_UART(void);
void temporizador_update(void);
void temporizador_new_time_print(void);
void temporizador_numero_print(UART_channel_t UART_name, uint8_t posicion, uint8_t numero);
void temporizador_timer_encabezados_print(void);

#endif /* TEMPORIZADOR_H_ */
