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

#define TIEMPO_LIMITE	(50U)

typedef struct{
	uint32_t address;
	uint8_t* data;
}log_struct_t;

/*!
 * @brief It used to read the memory, only byte by byte
 *
 * @param sound_t* sound_n Pointer to struct of sound
 */
void memory_read(log_struct_t* log);
void memory_write_log(log_struct_t* log);
void initial_logs(void);

#endif /* MEMORY_H_ */
