/**
 * @file memory.c
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief 	This receives information between
 * 			the K64 and the memory via SPI.
 */

#include "memory.h"

static uint8_t array_cmd[4] = {0x03, 0x00, 0x00, 0x00};

void memory_read(sound_t* sound_n)
{
	dspi_half_duplex_transfer_t masterXfer;
	uint32_t address = sound_n->address;
	//We need divided the address [23:0] in 3 bytes, also we need send the command 0x03-Read data
	array_cmd[1] = ((address) >> SHIFT_PART_1) & MASK_8_BYTES;
	array_cmd[2] = ((address) >> SHIFT_PART_2) & MASK_8_BYTES;
	array_cmd[3] = ((address) >> SHIFT_PART_3) & MASK_8_BYTES;
	masterXfer.txData = array_cmd;
	masterXfer.rxData = sound_n->array;
	masterXfer.txDataSize            = SIZE_TX;
	masterXfer.rxDataSize            = sound_n->size;
    masterXfer.isTransmitFirst       = true;
    masterXfer.isPcsAssertInTransfer = true;
    masterXfer.configFlags = kDSPI_MasterCtar1 | kDSPI_MasterPcs1 | kDSPI_MasterPcsContinuous;

    DSPI_MasterHalfDuplexTransferBlocking(SPI0, &masterXfer);
}
