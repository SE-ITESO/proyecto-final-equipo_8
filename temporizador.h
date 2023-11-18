/*

 */

#ifndef TEMPORIZADOR_H_
#define TEMPORIZADOR_H_

#include "UART.h"
#include <stdint.h>

#define NUM_TO_ASCII(a) (a + 0x30)

void temporizador_init(uint8_t tiempo_inicial);


#endif /* TEMPORIZADOR_H_ */
