/**
 * @file PIT.c
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief	Controls the PIT, its configuration,
 * 			as well as interrupts
 */

#include "PIT.h"

static void (*PIT_channel_0_callback)(uint8_t pit) = 0;
static void (*PIT_channel_1_callback)(uint8_t pit) = 0;
static void (*PIT_channel_2_callback)(uint8_t pit) = 0;
static void (*PIT_channel_3_callback)(uint8_t pit) = 0;

static void PIT_sim_init(void)
{
	SIM_SCGC6 |=  (BIT_ON << SHIFT_CLOCK_PIT);
}

void PIT_enable(void)
{
	PIT_sim_init();
	(*PIT_mcr) &= ~(PIT_ENABLE_MASK);
}

void PIT_Disable(void)
{

	(*PIT_mcr) |= (PIT_ENABLE_MASK);
}

void PIT_set_time(PIT_CH_t * p_channel, uint32_t time)
{
	p_channel->LDVAL = time;
}

void PIT_start_channel(PIT_CH_t * p_channel)
{
	p_channel->TCTRL |= PIT_START_CHANNEL_MASK;
}

void PIT_disable_channel(PIT_CH_t * p_channel)
{
	p_channel->TCTRL &= ~(PIT_START_CHANNEL_MASK);
}

uint32_t PIT_status_channel(PIT_CH_t * p_channel)
{
	uint32_t status = p_channel->TCTRL & (PIT_START_CHANNEL_MASK);
	return status;
}

void PIT_enable_channel_interrupt(PIT_CH_t * p_channel)
{
	p_channel->TCTRL |= PIT_ENABLE_INTERRUPT_MASK;
	p_channel->TFLG |= BIT_ON;
}

void PIT_callback_init(channel_t channel, void (*handler)(uint8_t pit))
{
	switch (channel)
	{
	case 0:
		PIT_channel_0_callback = handler;
	break;
	case 1:
		PIT_channel_1_callback = handler;
	break;
	case 2:
		PIT_channel_2_callback = handler;
	break;
	case 3:
		PIT_channel_3_callback = handler;
	break;
	}
}

static uint8_t PIT_get_flag(PIT_CH_t * p_channel)
{
	uint8_t PIT_interrupt_flag = p_channel->TFLG;
	return PIT_interrupt_flag;
}

static void PIT_channel_ClearInterruptFlags(PIT_CH_t * p_channel)
{
	p_channel->TFLG = TRUE;
}

void PIT0_IRQHandler(void)
{
	uint8_t irq_status = 0;
	irq_status = PIT_get_flag(PIT_CH0);

 	if(PIT_channel_0_callback)
	{
		PIT_channel_0_callback(irq_status);
	}

	PIT_channel_ClearInterruptFlags(PIT_CH0);
}

void PIT1_IRQHandler(void)
{
	uint8_t irq_status = 0;
	irq_status = PIT_get_flag(PIT_CH1);

 	if(PIT_channel_1_callback)
	{
		PIT_channel_1_callback(irq_status);
	}

	PIT_channel_ClearInterruptFlags(PIT_CH1);
}

void PIT2_IRQHandler(void)
{
	uint8_t irq_status = 0;
	irq_status = PIT_get_flag(PIT_CH2);

 	if(PIT_channel_2_callback)
	{
		PIT_channel_2_callback(irq_status);
	}

	PIT_channel_ClearInterruptFlags(PIT_CH0);
}

void PIT3_IRQHandler(void)
{
	uint8_t irq_status = 0;
	irq_status = PIT_get_flag(PIT_CH3);

 	if(PIT_channel_3_callback)
	{
		PIT_channel_3_callback(irq_status);
	}

	PIT_channel_ClearInterruptFlags(PIT_CH3);
}

