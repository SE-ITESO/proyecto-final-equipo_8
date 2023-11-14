/**
	\file
	\brief
		This is the header file for the UART device driver.
		It contains the macros and function definition.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	27/07/2015
	\todo
		To implement all needed functions
 */
#ifndef UART_H_
#define UART_H_

#include "stdint.h"
#include "fsl_uart.h"
#include "MK64F12.h"
#include "bits.h"
#include "GPIO.h"

#define SHIFT_RECEPTION_ENABLE (5U)

/**
 * \brief A mail box type definition for serial port
 */
typedef struct{
	uint8_t flag; /** Flag to indicate that there is new data*/
	uint8_t mailbox; /** it contains the received data*/
} UART_mailbox_t;

/*!
 	 \brief	 It gets the flag reception of the UART0
 	 \return uint8_t TRUE or FALSE
 */
uint8_t UART0_get_flag(void);

/*!
 	 \brief	 It gets the data of the UART0
 	 \return uint8_t data of UART0
 */
uint8_t UART0_get_data(void);

/*!
 	 \brief	 Clear the flag reception of the UART0
 */
void UART0_clear_flag(void);


uint8_t UART4_get_flag(void);
void UART4_clear_flag(void);
uint8_t UART4_get_data(void);

/**
 * \brief This enum define the UART port to be used.
 */
typedef enum {UART_0,UART_1,UART_2,UART_3,UART_4,UART_5} UART_channel_t;

/**
 * \brief It defines some common transmission baud rates
 */
typedef enum {BD_4800=4800,BD_9600=9600,BD_5600=5600, BD_115200=115200}UART_baud_rate_t;

//
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It configures the UART to be used
 	 \param[in]  uartChannel indicates which UART will be used.
 	 \param[in]  systemClk indicates the MCU frequency.
 	 \param[in]  baudRate sets the baud rate to transmit.
 	 \return void
 */
void UART_init(UART_channel_t uartChannel, uint32_t uart_clk, UART_baud_rate_t baud_rate,
		uart_parity_mode_t parity, uart_stop_bit_count_t stop_bit );

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 enables the RX UART interrupt). This function should include the next sentence:
 	 while (!(UART0_S1 & UART_S1_RDRF_MASK)). It is to guaranty that the incoming data is complete
 	 when reception register is read. For more details see chapter 52 in the kinetis reference manual.
 	 \param[in]  uartChannel indicates the UART channel.
 	 \return void
 */
void UART_interrupt_enable(UART_channel_t uart_channel);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It sends one character through the serial port. This function should include the next sentence:
 	 while(!(UART0->S1 & UART_S1_TC_MASK)). It is to guaranty that before to try to transmit a byte, the previous
 	 one was transmitted. In other word, to avoid to transmit data while the UART is busy transmitting information.
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  character to be transmitted.
 	 \return void
 */

void UART_put_char (UART_channel_t uart_channel, uint8_t character);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It sends a string character through the serial port.
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  string pointer to the string to be transmitted.
 	 \return void
 */
void UART_put_string(UART_channel_t uart_channel, uint8_t* string);

#endif /* UART_H_ */

