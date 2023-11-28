
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
#include "clock.h"
#include "SPI.h"

int main(void)
{
	clock_init();
	CLOCK_SetSimSafeDivs();
	UART_init (UART_0,  100000000, BD_115200, kUART_ParityDisabled, kUART_OneStopBit);
	UART_init (UART_4,  50000000, BD_115200, kUART_ParityDisabled, kUART_OneStopBit);
	UART_interrupt_enable(UART_0);
	UART_interrupt_enable(UART_4);
	SPI_config();

	NVIC_enable_interrupt_and_priotity(UART0_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(UART4_IRQ, PRIORITY_10);

	ajedrez_init();

    while(1)
    {
    	ajedrez_control();
    }
}
