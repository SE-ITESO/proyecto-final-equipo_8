/**
 * @file PIT.h
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief	Controls the PIT, its configuration,
 * 			as well as interrupts
 */

#ifndef PIT_H_
#define PIT_H_

#include <stdint.h>
#include "bits.h"

#define PIT_mcr					(((volatile uint32_t *) 0x40037000u))
#define PIT_channel_0_base		(((volatile uint32_t *) 0x40037100u))
#define PIT_channel_1_base		(((volatile uint32_t *) 0x40037110u))
#define PIT_channel_2_base		(((volatile uint32_t *) 0x40037120u))
#define PIT_channel_3_base		(((volatile uint32_t *) 0x40037130u))

#define SIM_SCGC6				(*((volatile uint32_t *) 0x4004803Cu))

#define SHIFT_CLOCK_PIT 		(23U)
#define PIT_CH0					((PIT_CH_t*) PIT_channel_0_base)
#define PIT_CH1 				((PIT_CH_t*) PIT_channel_1_base)
#define PIT_CH2 				((PIT_CH_t*) PIT_channel_2_base)
#define PIT_CH3 				((PIT_CH_t*) PIT_channel_3_base)

#define PIT_ENABLE_MASK 			(2U)
#define PIT_START_CHANNEL_MASK 		(1U)
#define PIT_ENABLE_INTERRUPT_MASK 	(2U)

#define ARRAY_PITCH1_CALLBACK 		(0U)
#define ARRAY_PITCH2_CALLBACK 		(1U)
#define PITCH3_CALLBACK 			(2U)

typedef enum{
	channel_0,
	channel_1,
	channel_2,
	channel_3
}channel_t;

typedef struct
{
	uint32_t LDVAL;
	uint32_t CVAL;
	uint32_t TCTRL;
	uint32_t TFLG;
} PIT_CH_t;

/*!
 * @brief Enable the PIT.
 */
void PIT_enable(void);

/*!
 * @brief Configure the value of the counter of channel
 *
 * @param PIT_CH_t * of Channel
 * @param uint32_t Time value
 */
void PIT_set_time(PIT_CH_t * p_channel, uint32_t time);

/*!
 * @brief Start count of the channel
 *
 * @param PIT_CH_t * of Channel
 */
void PIT_start_channel(PIT_CH_t * p_channel);

/*!
 * @brief Disable the channel
 *
 * @param PIT_CH_t * of Channel
 */
void PIT_disable_channel(PIT_CH_t * p_channel);

uint32_t PIT_status_channel(PIT_CH_t * p_channel);

/*!
 * @brief Enable the interrupt of Channel
 *
 * @param PIT_CH_t * of Channel
 */
void PIT_enable_channel_interrupt(PIT_CH_t * p_channel);

/*!
 * @brief Callback initialization
 *
 * @param channel_t name of channel (channel_0, channel_1, channel_2, channel_3)
 * @param pointer of function
 */
void PIT_callback_init(channel_t channel, void (*handler)(uint8_t pit));

#endif /* PIT_H_ */
