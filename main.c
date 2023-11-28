#include "ajedrez.h"
#include "NVIC.h"
#include "clock.h"

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
	return 0;
}

/*

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

	memory_create_log(0);
	memory_read_log(data);

	for(uint8_t index = 0; index <255; index++)
	{
		memory_add_movimiento(33);
	}

	memory_send_log();
	memory_read_log(data);

	return 0;
}
 */
