/**
 * @file DAC.c
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief 	This source access to DAC's
 * 			registers and control their parameters
 */

#include "DAC.h"

void DAC_activate_clock (dacn_t name_dac)
{
	SIM_SCGC2 |= (BIT_ON << (name_dac + BASE_SCGC2_DAC));
}				//0000-0011-0000-0000 bits para activar

void DAC_init (DAC_t * p_name_dac, DAC_config_t * p_config)
{
	if (DAC_0_BASE_ADDR == p_name_dac)
	{
		DAC_activate_clock(DAC_0);
	}
	else
	{
		DAC_activate_clock(DAC_1);
	}
	p_name_dac->C0 = (((p_config->voltage_reference) << SHIFT_DAC_VOLTAGE_REFERENCE) +
				      ((p_config->power_control) << SHIFT_DAC_POWER_CONTROL));
}

void DAC_enable (DAC_t * p_name_dac, enable_t option)   //habilita el DAC con enable(1)
{
	if (DISABLED == option)
	{
		p_name_dac->C0 &= ~(BIT_ON<<SHIFT_DAC_ENABLE);  //0000-0000-0000-0000
	}													//1111-1111-0111-1111
	else
	{
		p_name_dac->C0 |= (BIT_ON<<SHIFT_DAC_ENABLE);
	}
}

void DAC_buffer_read_pointer (DAC_t * p_name_dac, uint8_t number_buffer) //donde está el buffer
{
	p_name_dac->C2 &= ((number_buffer<<SHIFT_DAC_BUFFER_READ_POINTER) + (MASK_4_bits));
}

void DAC_buffer_upper_limit (DAC_t * p_name_dac, uint8_t number_buffer)
{
	p_name_dac->C2 &= ((number_buffer) + (MASK_4_bits<<SHIFT_DAC_BUFFER_READ_POINTER));
}

void DAC_write_buffer_value(DAC_t * p_name_dac, uint8_t number_buffer, uint16_t value)
{
	p_name_dac->VALUE[number_buffer].DATH = (value>>8) & (MASK_8_bits);
	p_name_dac->VALUE[number_buffer].DATL = (value) & (MASK_8_bits);
}
