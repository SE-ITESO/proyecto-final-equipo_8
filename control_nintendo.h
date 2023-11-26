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

#define TIEMPO_CH3		(50000U)

#define BIT_DATA_C1			(bit_0)
#define BIT_CLOCK_C1		(BIT_ON << 5)
#define BIT_LATCH_C1		(BIT_ON << 7)

#define BIT_DATA_C2			(bit_1)
#define BIT_CLOCK_C2		(BIT_ON << 9)
#define BIT_LATCH_C2		(BIT_ON << 8)

typedef enum{
	CONTROL_1,
	CONTROL_2
}control_num_t;

typedef enum{
	A,
	B,
	SELECT,
	START,
	UP,
	DOWN,
	LEFT,
	RIGHT
}control_button_t;

void control_nintendo_init(void);

void control_nintendo_clear(uint8_t array_buttons[8]);

void control_nintendo_control(control_num_t control, uint8_t array_control[8]);


#endif /* CONTROL_NINTENDO_H_ */

/*** end of file ***/
