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

typedef enum {
	k_sound,
	s_sound,
	b_sound,
	h_sound,
	g_sound,
	r_sound,
	t_sound,
	c_sound,
	w_sound
}sound_name_t;

typedef struct {
	uint32_t address;
	uint16_t size;
	uint8_t* array;
	uint8_t character;
}sound_t;

/*!
 * @brief It used to read the memory, only byte by byte
 *
 * @param sound_t* sound_n Pointer to struct of sound
 */
void memory_read(sound_t* sound_n);

#endif /* MEMORY_H_ */
