
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
#include "memory.h"

#include "ajedrez.h"
#include "NVIC.h"


int main(void)
{
	SPI_config();

	uint8_t data_cero[255] = {0};
	log_struct_t log_cero;
	log_cero.address = 0x41000;
	log_cero.data = data_cero;
	memory_read(&log_cero);

	return 0;
}
