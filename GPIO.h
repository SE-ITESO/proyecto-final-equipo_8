/**
 * @file GPIO.h
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief 	It controls everything related to the GPIO,
 * 			its configuration, reading and writing bits,
 * 			as well as the interrupts of the peripheral itself.
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "bits.h"

#define SIM_SCGC5        (*((volatile uint32_t *) 0x40048038u))

#define GPIO_A_BASE_ADDR (((volatile uint32_t *) 0x400FF000u))
#define GPIO_B_BASE_ADDR (((volatile uint32_t *) 0x400FF040u))
#define GPIO_C_BASE_ADDR (((volatile uint32_t *) 0x400FF080u))
#define GPIO_D_BASE_ADDR (((volatile uint32_t *) 0x400FF0C0u))
#define GPIO_E_BASE_ADDR (((volatile uint32_t *) 0x400FF100u))

#define PORT_A_PIN_BASE_ADDR (((volatile uint32_t *) 0x40049000u))
#define PORT_B_PIN_BASE_ADDR (((volatile uint32_t *) 0x4004A000u))
#define PORT_C_PIN_BASE_ADDR (((volatile uint32_t *) 0x4004B000u))
#define PORT_D_PIN_BASE_ADDR (((volatile uint32_t *) 0x4004C000u))
#define PORT_E_PIN_BASE_ADDR (((volatile uint32_t *) 0x4004D000u))

#define BASE_SCGC5_PORT  		(9U)

#define SHIFT_MUX 				(8U)
#define SHIFT_DRIVE_STRENGTH 	(6U)
#define SHIFT_OPEN_DRAIN 		(5U)
#define SHIFT_PASIVE_FILTER		(4U)
#define SHIFT_SLEW_RATE 		(2U)
#define SHIFT_PULL_ENABLE 		(1U)
#define SHIFT_PORT_IRQC 		(16U)

#define OFFSET_PORT_INTERRUPT_REGISTER (40U)

#define MASK_INTERRUPT_PORT		(0xffff)

#define GPIO_A ((GPIO_t*) GPIO_A_BASE_ADDR)
#define GPIO_B ((GPIO_t*) GPIO_B_BASE_ADDR)
#define GPIO_C ((GPIO_t*) GPIO_C_BASE_ADDR)
#define GPIO_D ((GPIO_t*) GPIO_D_BASE_ADDR)
#define GPIO_E ((GPIO_t*) GPIO_E_BASE_ADDR)

typedef struct
{
	uint32_t PDOR;
	uint32_t PSOR;
	uint32_t PCOR;
	uint32_t PTOR;
	uint32_t PDIR;
	uint32_t PDDR;
} GPIO_t;

typedef struct
{
	uint32_t flags_port_a;
	uint32_t flags_port_b;
	uint32_t flags_port_c;
	uint32_t flags_port_d;
	uint32_t flags_port_e;
} gpio_interrupt_flags_t;

typedef enum{PORT_A, PORT_B, PORT_C, PORT_D, PORT_E} port_t;
typedef enum{PIN_INPUT, PIN_OUTPUT} function_io_pin_t;
typedef enum{ALT_0, ALT_1, ALT_2, ALT_3, ALT_4, ALT_5, ALT_6, ALT_7} alternative_mux_t;
typedef enum{DRIVE_STRENGTH_LOW, DRIVE_STRENGTH_HIGH} drive_strength_enable_pin_t;
typedef enum{OPEN_DRAIN_DISABLED, OPEN_DRAIN_ENABLED} open_drain_enable_pin_t;
typedef enum{PASIVE_FILTER_DISABLE, PASIVE_FILTER_ENABLE} pasive_filter_enable_pin_t;
typedef enum{SLEW_RATE_FAST, SLEW_RATE_SLOW} slew_rate_enable_pin_t;
typedef enum{PULL_RESISTOR_DISABLED, PULL_RESISTOR_ENABLED} pull_enable_pin_t;
typedef enum{PULLDOWN_RESISTOR, PULLUP_RESISTOR} pull_select_pin_t;
typedef enum{
	INTERRUPT_STATUS_FLAG_DISABLED = 0,
	ISF_FLAG_INTERRUPT_DMA_RISING_EDGE = 1,
	ISF_FLAG_INTERRUPT_DMA_FALLING_EDGE = 2,
	ISF_FLAG_INTERRUPT_DMA_EITHER_EDGE = 3,
	ISF_FLAG_INTERRUPT_LOGIC_0 = 8,
	ISF_FLAG_INTERRUPT_RISING_EDGE = 9,
	ISF_FLAG_INTERRUPT_FALLING_EDGE = 10,
	ISF_FLAG_INTERRUPT_EITHER_EDGE = 11,
	ISF_FLAG_INTERRUPT_LOGIC_1 = 9
}pin_interrupt_t;

typedef struct
{
	alternative_mux_t option_mux;
	drive_strength_enable_pin_t drive_strength;
	open_drain_enable_pin_t open_drain;
	pasive_filter_enable_pin_t pasive_filter;
	slew_rate_enable_pin_t slew_rate;
	pull_enable_pin_t pull_enable;
	pull_select_pin_t pull_select;
} GPIO_pin_config_t;

/*!
 * @brief Clear the interrupt flags of port.
 *
 * @param volatile uint32_t* name of PORT (PORT_A_PIN_BASE_ADDR, PORT_B_PIN_BASE_ADDR, PORT_C_PIN_BASE_ADDR, PORT_D_PIN_BASE_ADDR, PORT_E_PIN_BASE_ADDR)
 * @param uint32_t value
 */
void GPIO_port_clear_interrupt_flags (volatile uint32_t * port_address, uint32_t value);

/*!
 * @brief Configurate mode of interrupt of pin.
 *
 * @param volatile uint32_t* name of PORT (PORT_A_PIN_BASE_ADDR, PORT_B_PIN_BASE_ADDR, PORT_C_PIN_BASE_ADDR, PORT_D_PIN_BASE_ADDR, PORT_E_PIN_BASE_ADDR)
 * @param uint8_t number of pin to choose
 * @param pin_interrupt_t option of the mode interruption
 */
void GPIO_set_pin_interrupt_config (volatile uint32_t * port_address, uint8_t number_pin, pin_interrupt_t option);

/*!
 * @brief Clear the status flags of port.
 *
 * @param port_t name of PORT (PORT_A, PORT_B, PORT_C, PORT_D, PORT_E)
 * @param uint32_t mask
 */
void GPIO_clear_irq_status(port_t name_port, uint32_t mask);

/*!
 * @brief Get the status flags of port.
 *
 * @param port_t name of PORT (PORT_A, PORT_B, PORT_C, PORT_D, PORT_E)
 *
 * @retval Returns a uint32_t with the value of the irq status of the port.
 */
uint32_t GPIO_get_irq_status(port_t name_port);


/*!
 * @brief Activate the clock of the port.
 *
 * @param port_t name of port (PORT_A, PORT_B, PORT_C, PORT_D, PORT_E)
 */
void GPIO_activate_clock_port (port_t name_port);

/*!
 * @brief Configurate pin of port.
 *
 * @param volatile uint32_t* name of PORT (PORT_A_PIN_BASE_ADDR, PORT_B_PIN_BASE_ADDR, PORT_C_PIN_BASE_ADDR, PORT_D_PIN_BASE_ADDR, PORT_E_PIN_BASE_ADDR)
 * @param bit_t number of pin
 * @param const GPIO_pin_config_t* struct of configuration of pin
 */
void GPIO_general_configuration_pin (volatile uint32_t* name_port, bit_t number_pin, const GPIO_pin_config_t* pin_config);

/*!
 * @brief Configurate the alternative of pin
 *
 * @param volatile uint32_t* name of PORT (PORT_A_PIN_BASE_ADDR, PORT_B_PIN_BASE_ADDR, PORT_C_PIN_BASE_ADDR, PORT_D_PIN_BASE_ADDR, PORT_E_PIN_BASE_ADDR)
 * @param bit_t number of pin
 * @param alternative_mux_t Alternative of mux
 */
void GPIO_select_alternative_pin (volatile uint32_t* name_port,
		bit_t number_pin, alternative_mux_t option_mux);

/*!
 * @brief Configurate pin of GPIO.
 *
 * @param GPIO* name of GPIO (GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E)
 * @param bit_t number of pin
 * @param const GPIO_pin_config_t* struct of configuration of pin
 */
void GPIO_configure_pin_input_output (GPIO_t* name_port, bit_t number_pin, function_io_pin_t function_of_pin);

/*!
 * @brief Clear output of pin.
 *
 * @param GPIO_t* name of GPIO (GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E)
 * @param bit_t number of pin
 */
void GPIO_clear_output_pin (GPIO_t* name_port, bit_t number_pin);

/*!
 * @brief Set output of pin.
 *
 * @param GPIO_t* name of GPIO (GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E)
 * @param bit_t number of pin
 */
void GPIO_set_output_pin (GPIO_t* name_port, bit_t number_pin);

/*!
 * @brief Toogle output of pin.
 *
 * @param GPIO_t* name of GPIO (GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E)
 * @param bit_t number of pin
 */
void GPIO_toggle_output_pin (GPIO_t* name_port, bit_t number_pin);

/*!
 * @brief Read input of port.
 *
 * @param GPIO_t* name of GPIO (GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E)
 *
 * @retval Returns a uint32_t with the value of the gpio reading.
 *
 */
uint32_t GPIO_read_input_port (GPIO_t* name_port);

/*!
 * @brief Read input of pin.
 *
 * @param GPIO_t* name of GPIO (GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E)
 * @param bit_t number of pin
 *
 * @retval Returns a uint8_t with the value of the pin reading.
 */
uint8_t GPIO_read_input_pin (GPIO_t* name_port, bit_t number_pin);

/*!
 * @brief Set output of port.
 *
 * @param GPIO_t* name of GPIO (GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E)
 * @param uint32_t value
 */
void GPIO_set_output_port (GPIO_t* name_port, uint32_t value);

/*!
 * @brief Clear output of port.
 *
 * @param GPIO_t* name of GPIO (GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E)
 * @param uint32_t value
 */
void GPIO_clear_output_port (GPIO_t* name_port, uint32_t value);

/*!
 * @brief Returns the port's interrupt flags
 *
 * @param volatile uint32_t* name of PORT
 * @retval uint32_t value
 */
uint32_t GPIO_port_get_interrupt_flags(volatile uint32_t* name_port);

/*!
 * @brief Initialization of callbacks
 *
 * @param port_t name of port (PORT_A, PORT_B, PORT_C, PORT_D, PORT_E)
 * @retval  void (*handler)(port_t port_name, uint32_t flags) Pointer of callback
 */
void GPIO_callback_init(port_t port_name, void (*handler)(uint32_t flags));

#endif /* GPIO_H_ */

/*** end of file ***/
