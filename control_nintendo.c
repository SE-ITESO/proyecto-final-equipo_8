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

	/*PIT configuration*/
	PIT_enable();
	PIT_set_time(PIT_CH3, TIEMPO_CH3);
	PIT_enable_channel_interrupt(PIT_CH3);
	PIT_callback_init(channel_3, PIT_set_flag_nintendo);
	PIT_start_channel(PIT_CH3);

	NVIC_set_basepri_threshold(0x0);
	NVIC_enable_interrupt_and_priotity(PIT_CH3_IRQ, PRIORITY_3);

}

void control_nintendo_control(uint8_t array_buttons[7])
{
	static uint8_t state = 0;
	static uint16_t counter_to_latch = 0;
	static uint8_t control_index = 0;

	if(FALSE != PIT_nintendo_flag)
	{

		PIT_nintendo_flag = 0;

		switch (state)
		{
		case 0:
			counter_to_latch++;

			if (1500 < counter_to_latch)	//12u * 1500 = 18milis
			{
				counter_to_latch=0;
				state = 1;
			}

		break;
		case 1:
			GPIO_set_output_port(GPIO_D, BIT_LATCH);
			state = 2;
		break;
		case 2:
			GPIO_clear_output_port(GPIO_D, BIT_LATCH);
			state = 3;
		break;
		case 3:
			GPIO_set_output_port(GPIO_D, BIT_CLOCK);
			state = 4;
		break;
		case 4:
			GPIO_clear_output_port(GPIO_D, BIT_CLOCK);
			state = 5;
		break;
		case 5:

			if (FALSE == GPIO_read_input_pin(GPIO_D, BIT_DATA))
			{
				array_buttons[control_index] = TRUE;
			}

			if (7 <= control_index)
			{
				state = 0;
				control_index = 0;
			}else{
				state = 3;
				control_index++;
			}

		break;
		default:
			state = 0;
		break;

		}
	}

}

