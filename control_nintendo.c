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

static uint8_t PIT_nintendo_flag[2] = {0,0};

void PIT_set_flag_nintendo(uint8_t pit)
{
	PIT_nintendo_flag[0] = TRUE;
	PIT_nintendo_flag[1] = TRUE;
}

void control_nintendo_init(void)
{

	GPIO_activate_clock_port(PORT_C);

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

	/*control 1*/
	GPIO_general_configuration_pin(PORT_C_PIN_BASE_ADDR, bit_5, &pin_config);
	GPIO_configure_pin_input_output(GPIO_C, bit_5, PIN_OUTPUT);

	GPIO_general_configuration_pin(PORT_C_PIN_BASE_ADDR, bit_7, &pin_config);
	GPIO_configure_pin_input_output(GPIO_C, bit_7, PIN_OUTPUT);

	/*control 2*/
	GPIO_general_configuration_pin(PORT_C_PIN_BASE_ADDR, bit_9, &pin_config);
	GPIO_configure_pin_input_output(GPIO_C, bit_9, PIN_OUTPUT);

	GPIO_general_configuration_pin(PORT_C_PIN_BASE_ADDR, bit_8, &pin_config);
	GPIO_configure_pin_input_output(GPIO_C, bit_8, PIN_OUTPUT);

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

	/*control 1*/
	GPIO_general_configuration_pin(PORT_C_PIN_BASE_ADDR, bit_0, &data_config);
	GPIO_configure_pin_input_output(GPIO_C, bit_0, PIN_INPUT);

	/*control 2*/
	GPIO_general_configuration_pin(PORT_C_PIN_BASE_ADDR, bit_1, &data_config);
	GPIO_configure_pin_input_output(GPIO_C, bit_1, PIN_INPUT);

	/*PIT configuration*/
	PIT_enable();
	PIT_set_time(PIT_CH3, TIEMPO_CH3);
	PIT_enable_channel_interrupt(PIT_CH3);
	PIT_callback_init(channel_3, PIT_set_flag_nintendo);
	PIT_start_channel(PIT_CH3);

	NVIC_set_basepri_threshold(0x0);
	NVIC_enable_interrupt_and_priotity(PIT_CH3_IRQ, PRIORITY_3);

}

void control_nintendo_control(control_num_t control, uint8_t array_buttons[7])
{
	static uint8_t state[2] = {0,0};
	static uint16_t counter_to_latch[2] = {0,0};
	static uint8_t control_index[2] = {0,0};

	uint32_t data = 0;
	uint32_t clock = 0;
	uint32_t latch = 0;

	if (control == CONTROL_1)
	{
		data = BIT_DATA_C1;
		clock = BIT_CLOCK_C1;
		latch = BIT_LATCH_C1;
	}else{
		data = BIT_DATA_C2;
		clock = BIT_CLOCK_C2;
		latch = BIT_LATCH_C2;
	}

	if(FALSE != PIT_nintendo_flag[control])
	{

		PIT_nintendo_flag[control] = 0;

		switch (state[control])
		{
		case 0:
			counter_to_latch[control]++;

			if (150 < counter_to_latch[control])	//12u * 1500 = 18milis
			{
				counter_to_latch[control]=0;
				state[control] = 1;
			}

		break;
		case 1:
			GPIO_set_output_port(GPIO_C, latch);
			state[control] = 2;
		break;
		case 2:
			GPIO_clear_output_port(GPIO_C, latch);
			state[control] = 3;
		break;

		case 3:

			if (FALSE == GPIO_read_input_pin(GPIO_C, data))
			{
				array_buttons[control_index[control]] = TRUE;
			}

			if (6 < control_index[control])
			{
				state[control] = 0;
				control_index[control] = 0;
			}else{
				state[control] = 4;
				control_index[control]++;
			}

		break;

		case 4:
			GPIO_set_output_port(GPIO_C, clock);
			state[control] = 5;
		break;
		case 5:
			GPIO_clear_output_port(GPIO_C, clock);
			state[control] = 3;
		break;

		default:
			state[control] = 0;
		break;

		}
	}

}
