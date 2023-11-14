/**
 * @file UART.c
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief 	It controls the operation
 * 			and initialization of the UART0
 */

#include "UART.h"

UART_mailbox_t g_UART0_mailbox = {0,0};
UART_mailbox_t g_UART4_mailbox = {0,0};

void UART0_RX_TX_IRQHandler()
{
	(void) UART0->S1;
	g_UART0_mailbox.mailbox = UART0->D;
	g_UART0_mailbox.flag = TRUE;
}

void UART4_RX_TX_IRQHandler()
{
	(void) UART4->S1;
	g_UART4_mailbox.mailbox = UART4->D;
	g_UART4_mailbox.flag = TRUE;
}

uint8_t UART0_get_flag(void)
{
	return g_UART0_mailbox.flag;
}

void UART0_clear_flag(void)
{
	g_UART0_mailbox.flag = FALSE;
}

uint8_t UART0_get_data(void)
{
	return g_UART0_mailbox.mailbox;
}

uint8_t UART4_get_flag(void)
{
	return g_UART4_mailbox.flag;
}

void UART4_clear_flag(void)
{
	g_UART4_mailbox.flag = FALSE;
}

uint8_t UART4_get_data(void)
{
	return g_UART4_mailbox.mailbox;
}

void UART_init(UART_channel_t uartChannel, uint32_t uart_clk, UART_baud_rate_t baud_rate,
		uart_parity_mode_t parity, uart_stop_bit_count_t stop_bit )
{
    uart_config_t config;
	/***************Port configuration******************/
    if(uartChannel==UART_0){
        GPIO_select_alternative_pin (PORT_B_PIN_BASE_ADDR, bit_16, ALT_3);
        GPIO_select_alternative_pin (PORT_B_PIN_BASE_ADDR, bit_17, ALT_3);
    }else{
        GPIO_select_alternative_pin (PORT_C_PIN_BASE_ADDR, bit_14, ALT_3);
        GPIO_select_alternative_pin (PORT_C_PIN_BASE_ADDR, bit_15, ALT_3);
    }

    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = baud_rate;
    config.enableTx     = true;
    config.enableRx     = true;
    config.parityMode	= parity;
    config.stopBitCount = stop_bit;

    switch(uartChannel)
    {
    case UART_0:
    	UART_Init(UART0, &config, uart_clk);
    	break;
    case UART_1:
    	UART_Init(UART1, &config, uart_clk);
    	break;
    case UART_2:
    	UART_Init(UART2, &config, uart_clk);
    	break;
    case UART_3:
    	UART_Init(UART3, &config, uart_clk);
    	break;
    case UART_4:
    	UART_Init(UART4, &config, uart_clk);
    	break;
    default:
    	UART_Init(UART5, &config, uart_clk);
    	break;
    }
}


void UART_interrupt_enable(UART_channel_t uart_channel)
{
	switch (uart_channel)
	{
	case UART_0:
		while (FALSE != (UART0->S1 & UART_S1_RDRF_MASK)) (void) UART0->D;
		UART0->C2 |= (BIT_ON << SHIFT_RECEPTION_ENABLE);
		break;
	case UART_4:
		while (FALSE != (UART4->S1 & UART_S1_RDRF_MASK)) (void) UART4->D;
		UART4->C2 |= (BIT_ON << SHIFT_RECEPTION_ENABLE);
		break;
	default:
		break;
	}
}

void UART_put_char(UART_channel_t uart_channel, uint8_t character)
{
	switch (uart_channel)
	{
	case UART_0:
		while (UART_S1_TC_MASK != ((UART0->S1) & (UART_S1_TC_MASK)));
		UART0->D = character;
		break;
	case UART_4:
		while (UART_S1_TC_MASK != ((UART4->S1) & (UART_S1_TC_MASK)));
		UART4->D = character;
		break;
	default:
		break;
	}
}

void UART_put_string(UART_channel_t uart_channel, uint8_t* string)
{
	int i = 0;
	while(0 != *(string + i)){
		UART_put_char(uart_channel, *(string + i));
		i++;
	}
}


