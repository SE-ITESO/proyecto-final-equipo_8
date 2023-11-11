

/**
 * @file    Proyecto.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"

#include "UART.h"
#include "NVIC.h"

int main(void) {

	CLOCK_SetSimSafeDivs();
	UART_init (UART_0,  21000000, BD_115200, kUART_ParityDisabled, kUART_OneStopBit);
	UART_interrupt_enable(UART_0);

	NVIC_enable_interrupt_and_priotity(UART0_IRQ, PRIORITY_10);

	UART_put_string(UART_0, "Hola");
    while(1) {
    }
}
