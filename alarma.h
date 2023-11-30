/**
 * @file alarma.h
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief 	Controls the alarm mode,
 * 			as well as monitoring to know if the alarm is enabled,
 * 			as well as activated.
 */

#ifndef ALARMA_H_
#define ALARMA_H_

#include "bits.h"
#include "DAC.h"
#include "PIT.h"
#include "NVIC.h"

#define BUFFER_0 	   	(0U)
#define TIEMPO_CH0 		(1563U)
#define ALARMA_SECOND  	(100U)
#define LIMITE_HORAS   	(23U)
#define LIMITE_MINUTOS	(59U)
#define ELEMENTOS_ARRAY	(32U)

#define ALAR_BIT_PTB_10		(BIT_ON << 10)
#define ALAR_BIT_PTB_3  	(BIT_ON << 3)
#define ALAR_BIT_PTA_4  	(BIT_ON << 4)
#define ALAR_BIT_PTB_2  	(BIT_ON << 2)

#define LIMITE 				(31990U)

/*!
 * @brief Initialization of Alarma
 *
 * @param void (*handler)(uint8_t pit), Pointer of callback
 */
void alarma_init(void);

/*!
 * @brief Hours in alarm mode
 *
 * @retval uint8_t Number of hours in alarm mode
 */
uint8_t alarma_get_hour(void);

/*!
 * @brief Minutes in alarm mode
 *
 * @retval uint8_t Number of minutes in alarm mode
 */
uint8_t alarma_get_minute(void);

/*!
 * @brief Seconds in alarm mode
 *
 * @retval uint8_t Number of seconds in alarm mode
 */
uint8_t alarma_get_second(void);

/*!
 * @brief Controls the function of the bocine
 *
 * @param uint8_t l_alarma_flag. Flags for alarm interruption.
 * @param void (*handler)(uint8_t pit) Function pointer for clearing the flags.
 */
void alarma_sonido(void);

/*!
 * @brief Controls the function of alarm mode
 *
 */
void alarma_control(void);

/*!
 * @brief Monitors the alarm, for example if enabled or activated.
 *
 * @param uint8_t l_modo_display. Current mode of the displays.
 * @param uint8_t l_alarma_flag. Flags for alarm interruption.
 * @param void (*handler)(uint8_t pit) Function pointer for clearing the flags.
 */
void alarma_monitoreo(
		uint8_t l_modo_display,
		uint8_t l_alarma_flag,
		void (*handler)(uint8_t pit));

#endif /* ALARMA_H_ */

/*** end of file ***/
