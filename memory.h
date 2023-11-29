/**
 * @file memory.h
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief 	This receives information between
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
#define TIEMPO_CH1		(100000000U)

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

void memory_add_movimiento(uint8_t x_old, uint8_t y_old, uint8_t x_new, uint8_t y_new);

void memory_send_log(void);

void memory_read_log(void* data);


#endif /* MEMORY_H_ */
