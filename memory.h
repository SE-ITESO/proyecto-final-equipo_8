/**
 * @file memory.h
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief 	This receives and transmit information between
 * 			the K64 and the memory via SPI.
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include "stdint.h"
#include "SPI.h"
#include "fsl_dspi.h"
#include "PIT.h"
#include "NVIC.h"

#define SHIFT_PART_1	(16U)
#define SHIFT_PART_2	(8U)
#define SHIFT_PART_3	(0U)

#define MASK_8_BYTES	(0xFF)

#define SIZE_TX			(4U)
#define SIZE_RX			(1U)

#define ERASE_COMMAND	(0x20)
#define WE_COMMAND		(0x06)
#define WD_COMMAND		(0x04)
#define WRITE_COMMAND	(0x02)

#define TIEMPO_LIMITE	(20000000U)
#define TIEMPO_CH1		(20000000U)

#define ADD_LOG_1	(0x040000U)
#define ADD_LOG_2	(0x041000U)
#define ADD_LOG_3	(0x042000U)
#define ADD_LOG_4	(0x043000U)
#define ADD_LOG_5	(0x044000U)

typedef struct{
	uint32_t address;
	uint8_t* data;
}log_struct_t;

/*!
 * @brief It used to read the memory, only byte by byte
 *
 * @param sound_t* sound_n Pointer to struct of sound
 */
void memory_create_log(uint8_t log_number);

/*!
 * @brief It used to save a move in game
 *
 * @param uint8_t x_old
 * @param uint8_t y_old
 * @param uint8_t x_new
 * @param uint8_t y_new
 */
void memory_add_movimiento(uint8_t x_old, uint8_t y_old, uint8_t x_new, uint8_t y_new);

/*!
 * @brief Function for send the information to memory
 */
void memory_send_log(void);

/*!
 * @brief Function for read the information to memory
 *
 * @param void* data
 */
void memory_read_log(void* data);

/*!
 * @brief Function for enable the write
 */
void memory_write_enable(void);

/*!
 * @brief Function for erase the page
 *
 * @param log_struct_t* log
 */
void memory_erase_page(log_struct_t* log);

/*!
 * @brief Function for write page
 *
 * @param log_struct_t* log
 */
void memory_write_page(log_struct_t* log);

/*!
 * @brief Function for disable the page
 */
void memory_write_disable(void);

/*!
 * @brief Function for configuration the log
 *
 * @param log_struct_t* log
 */
void log_config(uint8_t operation, void* data);

/*!
 * @brief Function for write the log
 *
 * @param log_struct_t* log
 */
void memory_write_log(log_struct_t* log);

/*!
 * @brief Function for read the log
 *
 * @param log_struct_t* log
 */
void memory_read(log_struct_t* log);

#endif /* MEMORY_H_ */
