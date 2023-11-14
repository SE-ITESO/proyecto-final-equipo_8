/**
 * @file GPIO.c
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief 	It controls everything related to the GPIO,
 * 			its configuration, reading and writing bits,
 * 			as well as the interrupts of the peripheral itself.
 */

#include "GPIO.h"

volatile static gpio_interrupt_flags_t g_intr_status_flag = {0};

static void (*PORTA_callback)(uint32_t flags) = 0;
static void (*PORTB_callback)(uint32_t flags) = 0;
static void (*PORTC_callback)(uint32_t flags) = 0;
static void (*PORTD_callback)(uint32_t flags) = 0;
static void (*PORTE_callback)(uint32_t flags) = 0;

void GPIO_callback_init(port_t port_name, void (*handler)(uint32_t flags))
{
	switch (port_name)
	{
	case 0:
		PORTA_callback = handler;
	break;
	case 1:
		PORTB_callback = handler;
	break;
	case 2:
		PORTC_callback = handler;
	break;
	case 3:
		PORTD_callback = handler;
	break;
	default:
		PORTE_callback = handler;
	break;
	}
}

void PORTA_IRQHandler(void)
{
	g_intr_status_flag.flags_port_a = GPIO_port_get_interrupt_flags(PORT_A_PIN_BASE_ADDR);
	GPIO_port_clear_interrupt_flags(PORT_A_PIN_BASE_ADDR, MASK_INTERRUPT_PORT);
}

void PORTB_IRQHandler(void)
{
	g_intr_status_flag.flags_port_b = GPIO_port_get_interrupt_flags(PORT_B_PIN_BASE_ADDR);
	GPIO_port_clear_interrupt_flags(PORT_B_PIN_BASE_ADDR, MASK_INTERRUPT_PORT);
}

void PORTC_IRQHandler(void)
{
	uint32_t irq_status = 0;
	irq_status = GPIO_port_get_interrupt_flags(PORT_C_PIN_BASE_ADDR);

 	if(PORTC_callback)
	{
 		PORTC_callback(irq_status);
	}

 	GPIO_port_clear_interrupt_flags(PORT_C_PIN_BASE_ADDR, MASK_INTERRUPT_PORT);
}


void PORTD_IRQHandler(void)
{
	uint32_t irq_status = 0;
	irq_status = GPIO_port_get_interrupt_flags(PORT_D_PIN_BASE_ADDR);

 	if(PORTD_callback)
	{
 		PORTD_callback(irq_status);
	}

 	GPIO_port_clear_interrupt_flags(PORT_D_PIN_BASE_ADDR, MASK_INTERRUPT_PORT);
}

void GPIO_set_pin_interrupt_config (volatile uint32_t * port_address, uint8_t number_pin, pin_interrupt_t option)
{
	volatile uint32_t* portx_pcrn;
	portx_pcrn = port_address;
	portx_pcrn = portx_pcrn + number_pin;
	*(portx_pcrn) |= (option<<SHIFT_PORT_IRQC);
}

uint32_t GPIO_port_get_interrupt_flags (volatile uint32_t * port_address)
{
	volatile uint32_t* portx_pcrn;
	portx_pcrn = port_address;
	portx_pcrn = portx_pcrn + OFFSET_PORT_INTERRUPT_REGISTER;
	return *(portx_pcrn);
}

void GPIO_port_clear_interrupt_flags (volatile uint32_t * port_address, uint32_t value)
{
	volatile uint32_t* portx_pcrn;
	portx_pcrn = port_address;
	portx_pcrn = portx_pcrn + OFFSET_PORT_INTERRUPT_REGISTER;
	*(portx_pcrn) = value;
}

void GPIO_clear_irq_status(port_t name_port, uint32_t mask)
{
	if(PORT_A == name_port)
	{
		g_intr_status_flag.flags_port_a &= ~(mask);
	}
	else if(PORT_B == name_port)
	{
		g_intr_status_flag.flags_port_b &= ~(mask);
	}
	else if(PORT_C == name_port)
	{
		g_intr_status_flag.flags_port_c &= ~(mask);
	}
	else if(PORT_D == name_port)
	{
		g_intr_status_flag.flags_port_d &= ~(mask);
	}
	else
	{
		g_intr_status_flag.flags_port_e &= ~(mask);
	}
}

uint32_t GPIO_get_irq_status(port_t name_port)
{
	uint32_t status = 0;

	if(PORT_A == name_port)
	{
		status = g_intr_status_flag.flags_port_a;
	}
	else if(PORT_B == name_port)
	{
		status = g_intr_status_flag.flags_port_b;
	}
	else if(PORT_C == name_port)
	{
		status = g_intr_status_flag.flags_port_c;
	}
	else if(PORT_D == name_port)
	{
		status = g_intr_status_flag.flags_port_d;
	}
	else
	{
		status = g_intr_status_flag.flags_port_e;
	}
	return(status);
}

void GPIO_activate_clock_port (port_t name_port)
{
	SIM_SCGC5 |= (BIT_ON << (name_port + BASE_SCGC5_PORT));
}

void GPIO_general_configuration_pin (volatile uint32_t* name_port,
		bit_t number_pin, const GPIO_pin_config_t* pin_config)
{
	if(PORT_A_PIN_BASE_ADDR == name_port){
		GPIO_activate_clock_port(PORT_A);
	}
	else if(PORT_B_PIN_BASE_ADDR == name_port){
		GPIO_activate_clock_port(PORT_B);
	}
	else if(PORT_C_PIN_BASE_ADDR == name_port){
		GPIO_activate_clock_port(PORT_C);
	}
	else if(PORT_D_PIN_BASE_ADDR == name_port){
		GPIO_activate_clock_port(PORT_D);
	}
	else{
		GPIO_activate_clock_port(PORT_E);
	}
	volatile uint32_t* portx_pcrn;
	portx_pcrn = name_port;
	portx_pcrn = portx_pcrn + number_pin;
	*(portx_pcrn) = ((pin_config->option_mux) << SHIFT_MUX) +
			((pin_config->drive_strength) << SHIFT_DRIVE_STRENGTH) +
			((pin_config->open_drain) << SHIFT_OPEN_DRAIN) +
			((pin_config->pasive_filter) << SHIFT_PASIVE_FILTER) +
			((pin_config->slew_rate) << SHIFT_SLEW_RATE) +
			((pin_config->pull_enable) << SHIFT_PULL_ENABLE) +
			pin_config->pull_select;
}

void GPIO_select_alternative_pin (volatile uint32_t* name_port,
		bit_t number_pin, alternative_mux_t option_mux)
{
	if(PORT_A_PIN_BASE_ADDR == name_port){
		GPIO_activate_clock_port(PORT_A);
	}
	else if(PORT_B_PIN_BASE_ADDR == name_port){
		GPIO_activate_clock_port(PORT_B);
	}
	else if(PORT_C_PIN_BASE_ADDR == name_port){
		GPIO_activate_clock_port(PORT_C);
	}
	else if(PORT_D_PIN_BASE_ADDR == name_port){
		GPIO_activate_clock_port(PORT_D);
	}
	else{
		GPIO_activate_clock_port(PORT_E);
	}
	volatile uint32_t* portx_pcrn;
	portx_pcrn = name_port;
	portx_pcrn = portx_pcrn + number_pin;
	*(portx_pcrn) &= ~(7 << SHIFT_MUX);
	*(portx_pcrn) |= (option_mux << SHIFT_MUX);
}

void GPIO_configure_pin_input_output (GPIO_t* name_port, bit_t number_pin,
		function_io_pin_t function_of_pin)
{
	GPIO_t* gpio_aux;
	gpio_aux = name_port;
	if(PIN_OUTPUT == function_of_pin)
	{
		gpio_aux->PDDR |= (BIT_ON<<number_pin);
	}
	else
	{
		gpio_aux->PDDR &= ~(BIT_ON<<number_pin);
	}
}

void GPIO_clear_output_pin (GPIO_t* name_port, bit_t number_pin)
{
	GPIO_t* gpio_aux;
	gpio_aux = name_port;
	gpio_aux->PCOR = (BIT_ON << number_pin);
}
/////////////////////////////////////////////////////////////////////////////////
void GPIO_clear_output_port (GPIO_t* name_port, uint32_t value)
{
	GPIO_t* gpio_aux;
	gpio_aux = name_port;
	gpio_aux->PCOR = value;
}

void GPIO_set_output_pin (GPIO_t* name_port, bit_t number_pin)
{
	GPIO_t* gpio_aux;
	gpio_aux = name_port;
	gpio_aux->PSOR = (BIT_ON << number_pin);
}
////////////////////////////////////////////////////////////////////////////////
void GPIO_set_output_port (GPIO_t* name_port, uint32_t value)
{
	GPIO_t* gpio_aux;
	gpio_aux = name_port;
	gpio_aux->PSOR = value;
}

void GPIO_toggle_output_port (GPIO_t* name_port, bit_t number_pin)
{
	GPIO_t* gpio_aux;
	gpio_aux = name_port;
	gpio_aux->PTOR = (BIT_ON << number_pin);
}


uint32_t GPIO_read_input_port (GPIO_t* name_port)
{
	GPIO_t* gpio_aux;
	gpio_aux = name_port;
	return gpio_aux->PDIR;
}

uint8_t GPIO_read_input_pin (GPIO_t* name_port, bit_t number_pin)
{
	uint32_t read_port;
	read_port = GPIO_read_input_port(name_port);
	read_port = (read_port >> number_pin) & (BIT_ON);
	return (uint8_t) read_port;
}
