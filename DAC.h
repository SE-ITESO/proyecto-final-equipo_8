/**
 * @file DAC.h
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief 	Access to DAC's
 * 			registers and control their parameters
 */

#ifndef DAC_H_
#define DAC_H_

#include <stdint.h>
#include "bits.h"

#define SIM_SCGC2       (*((volatile uint32_t *) 0x4004802Cu))

#define BASE_SCGC2_DAC  (12U)

#define DAC_0_BASE_ADDR (((DAC_t *) 0x400CC000u))
#define DAC_1_BASE_ADDR (((DAC_t *) 0x400CD000u))

#define MASK_8_bits		(0xFF)
#define MASK_4_bits		(0xF)

#define SHIFT_DAC_VOLTAGE_REFERENCE 	(6U)
#define SHIFT_DAC_POWER_CONTROL			(3U)
#define SHIFT_DAC_ENABLE				(7U)
#define SHIFT_DAC_BUFFER_READ_POINTER	(4U)

typedef struct {
	struct {
		uint8_t DATL;
		uint8_t DATH;
	} VALUE [16];
	uint8_t SR;
	uint8_t C0;
	uint8_t C1;
	uint8_t C2;
} volatile DAC_t;

typedef enum{DAC_0, DAC_1} dacn_t;
typedef enum{DACREF_1, DACREF_2} dac_reference_t;
typedef enum{HIGH_POWER, LOW_POWER} dac_power_control_t;

typedef struct
{
	dac_reference_t voltage_reference;
	dac_power_control_t power_control;
} DAC_config_t;

/*!
 * @brief Activate the clock of the DAC.
 *
 * @param dac_t name of DAC (DAC_0, DAC_1)
 */
void DAC_activate_clock (dacn_t name_dac);

/*!
 * @brief Init the DAC.
 *
 * @param DAC_t * of DAC
 * @param DAC_config_t* configuration of DAC
 */
void DAC_init (DAC_t * p_name_dac, DAC_config_t* config);

/*!
 * @brief Enables or disables the DAC
 *
 * @param DAC_t * of DAC
 * @param enable_t option enable of DAC
 */
void DAC_enable (DAC_t * p_name_dac ,enable_t option);

/*!
 * @brief Define read DAC buffer
 *
 * @param DAC_t * of DAC
 * @param uint8_t number of buffer
 */
void DAC_buffer_read_pointer (DAC_t * p_name_dac, uint8_t number_buffer);

/*!
 * @brief Define upper DAC buffer
 *
 * @param DAC_t * of DAC
 * @param uint8_t number of buffer
 */
void DAC_buffer_upper_limit (DAC_t* p_name_dac, uint8_t number_buffer);

/*!
 * @brief Write in the buffer selected.
 *
 * @param DAC_t * of DAC
 * @param uint8_t number of buffer
 */
void DAC_write_buffer_value(DAC_t * p_name_dac, uint8_t number_buffer, uint16_t value);

#endif /* DAC_H_ */

/*** end of file ***/
