/**
 * @file control_nintendo.h
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief
 *
 */

#ifndef CONTROL_NINTENDO_H_
#define CONTROL_NINTENDO_H_

#include <stdint.h>
#include "PIT.h"
#include "GPIO.h"
#include "NVIC.h"

#define TIEMPO_CH3		(126U)

#define BIT_DATA		(bit_3)
#define BIT_CLOCK		(BIT_ON << 2)
#define BIT_LATCH		(BIT_ON << 1)

void control_nintendo_init(void);

void control_nintendo_control(uint8_t array_control[7]);


#endif /* CONTROL_NINTENDO_H_ */

/*** end of file ***/
