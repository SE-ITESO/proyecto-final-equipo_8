/**
 * @file alarma.c
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief 	Controls the alarm mode,
 * 			as well as monitoring to know if the alarm is enabled,
 * 			as well as activated.
 */

#include "alarma.h"

const uint16_t sin_array[ELEMENTOS_ARRAY]={
							2047,2459,2854,3216,
							3530,3784,3966,4070,
							4091,4028,3884,3665,
							3380,3040,2660,2254,
							1839,1434,1053,713,
							428, 209, 65,  2,
							23,  127, 310, 563,
							878, 1240,1635,2047};

static uint16_t g_alarma_flag = 0;

void set_alarma_flag(uint8_t pit)
{
	g_alarma_flag ++;
}

void alarma_init(void)
{

	/*PIT configuration*/
	PIT_enable();
	PIT_set_time(PIT_CH0, TIEMPO_CH0);
	PIT_start_channel(PIT_CH0);
	PIT_enable_channel_interrupt(PIT_CH0);
	//PIT_start_channel(PIT_CH0);
	PIT_callback_init(channel_0, set_alarma_flag);

	/*NVIC configuration*/
	NVIC_set_basepri_threshold(0x0);
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_3);

	/*DAC configuration*/
	DAC_config_t config_dac_0 =
	{
		DACREF_2,
		HIGH_POWER
	};

	DAC_activate_clock(DAC_0);
	DAC_init(DAC_0_BASE_ADDR, &config_dac_0);
	DAC_enable(DAC_0_BASE_ADDR, ENABLED);
	DAC_buffer_read_pointer(DAC_0_BASE_ADDR, BUFFER_0);

}


void alarma_sonido()
{
	static uint8_t i = 0;
	static uint16_t value_DAC = 0;
	static uint8_t seno_activo = 0;
	static uint32_t conteo = 0;

	if (g_alarma_flag)					//hubo bandera, actualiza valor del DAC
	{
		i = i + g_alarma_flag;
		i = i % ELEMENTOS_ARRAY;
		value_DAC = sin_array[i];
		conteo++;
		g_alarma_flag = 0;
	}

	if(conteo == LIMITE)
	{
		seno_activo = ~seno_activo;
		conteo = 0;
	}

	if (seno_activo)			//segundo non?
	{
		value_DAC  = value_DAC;
	}
	else									//DAC en cero, detiene el pit
	{
 		value_DAC = 0;
	}

	DAC_write_buffer_value(DAC_0_BASE_ADDR, BUFFER_0, value_DAC);
}

