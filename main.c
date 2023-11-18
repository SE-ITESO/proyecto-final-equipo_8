
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

#include "ajedrez.h"
#include "NVIC.h"

int main(void) {
	CLOCK_SetSimSafeDivs();
	UART_init (UART_0,  21000000, BD_115200, kUART_ParityDisabled, kUART_OneStopBit);
	UART_init (UART_4,  10500000, BD_115200, kUART_ParityDisabled, kUART_OneStopBit);
	UART_interrupt_enable(UART_0);
	UART_interrupt_enable(UART_4);

	NVIC_enable_interrupt_and_priotity(UART0_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(UART4_IRQ, PRIORITY_10);

	ajedrez_init();
	//tablero_init();

	//fichas_peon_print();
	//fichas_torre_print();
	//fichas_alfil_print();
	//fichas_caballo_print();
	//fichas_reina_print();
	//fichas_rey_print();

    while(1)
    {
    	ajedrez_control();
    }
}
