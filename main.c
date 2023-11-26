
/**
 * @file    Proyecto.c
 * @brief   Application entry point.
 */

/*
 * Notas:
 * El 219 Es un "█"
 * El 32 Es un " "
 * http://graphcomp.com/info/specs/ansi_col.html
 *
 * */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "clock.h"

#include "ajedrez.h"
#include "NVIC.h"

#include "SPI.h"
#include "memory.h"

int main(void) {

	uint8_t data[255] = {0};

	clock_init();
	SPI_config();

	memory_create_log(1);

	for(uint8_t index = 0; index <125; index++)
	{
		memory_add_movimiento(index);
	}

	memory_send_log();
	memory_read_log(&data);

	return 0;
}
