
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

#include "fichas.h"
#include "tablero.h"
#include "NVIC.h"

static uint8_t g_mover_arriba[] = "\033[10A";

int main(void) {


	CLOCK_SetSimSafeDivs();
	UART_init (UART_0,  21000000, BD_115200, kUART_ParityDisabled, kUART_OneStopBit);
	UART_interrupt_enable(UART_0);

	NVIC_enable_interrupt_and_priotity(UART0_IRQ, PRIORITY_10);

	tablero_init();

	UART_put_string(UART_0, "\033[30;30H");
	UART_put_string(UART_0, g_mover_arriba);

	int i = 0;
/*
	for(i = 0; i < 3; i++)
	{
		UART_put_char(UART_0, 32);
	}
*/

	//fichas_peon_print();
	//fichas_torre_print();
	//fichas_alfil_print();
	//fichas_caballo_print();
	//fichas_reina_print();
	//fichas_rey_print();

	//UART_put_string(UART_0, "Hola puto");
    while(1) {
    }
}
