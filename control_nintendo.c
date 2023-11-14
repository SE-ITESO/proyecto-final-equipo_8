/**
 * @file control_nintendo.c
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief
 *
 */

#include "control_nintendo.h"

static uint8_t PIT_nintendo_flag = 0;

void PIT_set_flag_nintendo(uint8_t pit)
{
	PIT_nintendo_flag = TRUE;
}

void control_nintendo_init(void)
{
	/*PIT configuration*/
	PIT_enable();
	PIT_set_time(PIT_CH3, TIEMPO_CH3);
	PIT_enable_channel_interrupt(PIT_CH3);
	PIT_callback_init(channel_3, PIT_set_flag_nintendo);
	PIT_start_channel(PIT_CH3);

	NVIC_set_basepri_threshold(0x0);
	NVIC_enable_interrupt_and_priotity(PIT_CH3_IRQ, PRIORITY_3);


	GPIO_activate_clock_port(PORT_D);

	const GPIO_pin_config_t pin_config =
	{
		ALT_1,
		DRIVE_STRENGTH_LOW,
		OPEN_DRAIN_DISABLED,
		PASIVE_FILTER_DISABLE,
		SLEW_RATE_FAST,
		PULL_RESISTOR_DISABLED,
		PULLDOWN_RESISTOR
	};

	GPIO_general_configuration_pin(PORT_D_PIN_BASE_ADDR, bit_1, &pin_config);
	GPIO_configure_pin_input_output(GPIO_D, bit_1, PIN_OUTPUT);

	GPIO_general_configuration_pin(PORT_D_PIN_BASE_ADDR, bit_2, &pin_config);
	GPIO_configure_pin_input_output(GPIO_D, bit_2, PIN_OUTPUT);

	const GPIO_pin_config_t data_config =
	{
		ALT_1,
		DRIVE_STRENGTH_LOW,
		OPEN_DRAIN_DISABLED,
		PASIVE_FILTER_ENABLE,
		SLEW_RATE_FAST,
		PULL_RESISTOR_DISABLED,
		PULLDOWN_RESISTOR
	};

	GPIO_general_configuration_pin(PORT_D_PIN_BASE_ADDR, bit_3, &data_config);
	GPIO_configure_pin_input_output(GPIO_D, bit_3, PIN_INPUT);

}

void control_nintendo_control(uint8_t g_array_buttons[7])
{
	static uint8_t state = 0;

	switch (state)
	{
	case 0:
		GPIO_set_output_port(GPIO_D, BIT_LATCH);
	break;
	case 1:
		GPIO_clear_output_port(GPIO_D, BIT_LATCH);
	break;

	case 2:
		GPIO_set_output_port(GPIO_D, BIT_CLOCK);
	break;
	case 3:
		GPIO_clear_output_port(GPIO_D, BIT_CLOCK);
	break;
	case 4:
		if (FALSE == GPIO_read_input_pin(GPIO_D, BIT_DATA))
			g_array_buttons[0] = TRUE;
	break;

	case 5:
		GPIO_set_output_port(GPIO_D, BIT_CLOCK);
	break;
	case 6:
		GPIO_clear_output_port(GPIO_D, BIT_CLOCK);
	break;
	case 7:
		if (FALSE == GPIO_read_input_pin(GPIO_D, BIT_DATA))
			g_array_buttons[1] = TRUE;
	break;
	case 8:
		GPIO_set_output_port(GPIO_D, BIT_CLOCK);
	break;
	case 9:
		GPIO_clear_output_port(GPIO_D, BIT_CLOCK);
	break;
	case 10:
		if (FALSE == GPIO_read_input_pin(GPIO_D, BIT_DATA))
			g_array_buttons[2] = TRUE;
	break;
	case 11:
		GPIO_set_output_port(GPIO_D, BIT_CLOCK);
	break;
	case 12:
		GPIO_clear_output_port(GPIO_D, BIT_CLOCK);
	break;
	case 13:
		if (FALSE == GPIO_read_input_pin(GPIO_D, BIT_DATA))
			g_array_buttons[3] = TRUE;
	break;
	case 14:
		GPIO_set_output_port(GPIO_D, BIT_CLOCK);
	break;
	case 15:
		GPIO_clear_output_port(GPIO_D, BIT_CLOCK);
	break;
	case 16:
		if (FALSE == GPIO_read_input_pin(GPIO_D, BIT_DATA))
			g_array_buttons[4] = TRUE;
	break;
	case 17:
		GPIO_set_output_port(GPIO_D, BIT_CLOCK);
	break;
	case 18:
		GPIO_clear_output_port(GPIO_D, BIT_CLOCK);
	break;
	case 19:
		if (FALSE == GPIO_read_input_pin(GPIO_D, BIT_DATA))
			g_array_buttons[5] = TRUE;
	break;
	case 20:
		GPIO_set_output_port(GPIO_D, BIT_CLOCK);
	break;
	case 21:
		GPIO_clear_output_port(GPIO_D, BIT_CLOCK);
	break;
	case 22:
		if (FALSE == GPIO_read_input_pin(GPIO_D, BIT_DATA))
			g_array_buttons[6] = TRUE;
	break;
	case 23:
		GPIO_set_output_port(GPIO_D, BIT_CLOCK);
	break;
	case 24:
		GPIO_clear_output_port(GPIO_D, BIT_CLOCK);
	break;
	case 25:
		if (FALSE == GPIO_read_input_pin(GPIO_D, BIT_DATA))
			g_array_buttons[7] = TRUE;
	break;

	}

	if (FALSE != PIT_nintendo_flag)
		{
			state++;
			if (state == 26)
				state = 0;
			PIT_nintendo_flag = 0;
		}

}

