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

void memory_write_enable(void);
void memory_erase_page(log_struct_t* log);
void memory_write_page(log_struct_t* log);
void memory_write_disable(void);
void memory_erase_page(log_struct_t* log);

void log_config(uint8_t operation, uint32_t data)
{
	static uint8_t movimientos[255] = {0};
	static log_struct_t current_log;
	static uint8_t movimientos_index = 4;

	switch (operation)
	{
	case 0:
		current_log.address = data;
		current_log.data = movimientos;
	break;
	case 1:
		current_log.data[movimientos_index] = data;
		movimientos_index++;
	break;
	case 2:
		memory_write_log(&current_log);
	break;
	}
}


void memory_create_log(uint8_t log_number)
{
	uint32_t address;

	switch (log_number)
	{
	case 0:
		address = 0x040000;
	break;
	case 1:
		address = 0x041000;
	break;
	case 2:
		address = 0x042000;
	break;
	case 3:
		address = 0x043000;
	break;
	case 4:
		address = 0x044000;
	break;
	default:
		address = 0x044000;
	break;
	}

	log_config(0, address);
}

void initial_logs(void)
{
	log_struct_t current_log;
	uint8_t current_data[255];

	for (uint8_t index = 0; index<255; index++)
	{
		current_data[index] = 1;
	}

	current_log.address = 0x40000;
	current_log.data = current_data;

	memory_write_log(&current_log);
	memory_read(&current_log);

	for (uint8_t index = 0; index<255; index++)
	{
		current_data[index] = 2;
	}

	current_log.address = 0x41000;
	current_log.data = current_data;

	memory_write_log(&current_log);
	memory_read(&current_log);

	for (uint8_t index = 0; index<255; index++)
	{
		current_data[index] = 3;
	}

	current_log.address = 0x42000;
	current_log.data = current_data;

	memory_write_log(&current_log);
	memory_read(&current_log);

	for (uint8_t index = 0; index<255; index++)
	{
		current_data[index] = 4;
	}

	current_log.address = 0x43000;
	current_log.data = current_data;

	memory_write_log(&current_log);
	memory_read(&current_log);

	for (uint8_t index = 0; index<255; index++)
	{
		current_data[index] = 4;
	}

	current_log.address = 0x44000;
	current_log.data = current_data;

	memory_write_log(&current_log);
	memory_read(&current_log);
}

void memory_write_log(log_struct_t* log)
{
	/*
	uint8_t tiempo_transcurrido = 0;
	uint8_t etapa = 0;
	while(tiempo_transcurrido < TIEMPO_LIMITE)
	{
		if (g_PIT_memory_flag)
		{
			etapa++;
			g_PIT_memory_flag = 0;

			switch (etapa)
			{
			case 0:
				memory_write_enable();
			break;

			}

		}
	}
	*/
	memory_write_enable();
	memory_erase_page(log);
	memory_write_enable();
	memory_write_page(log);
	memory_write_disable();
}

void memory_write_enable()
{
	uint8_t data = WE_COMMAND;

	dspi_transfer_t masterXfer;
	masterXfer.txData = &data;
	masterXfer.rxData = NULL;
	masterXfer.dataSize = 1;
    masterXfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;

	DSPI_MasterTransferBlocking(SPI0, &masterXfer);
}

void memory_erase_page(log_struct_t* log)
{
	dspi_transfer_t masterXfer;
	uint32_t address = log->address;
	static uint8_t eraser[4] = {0};

	eraser[0] = ERASE_COMMAND;
	eraser[1] = ((address) >> SHIFT_PART_1) & MASK_8_BYTES;
	eraser[2] = ((address) >> SHIFT_PART_2) & MASK_8_BYTES;
	eraser[3] = ((address) >> SHIFT_PART_3) & MASK_8_BYTES;

	masterXfer.txData = eraser;
	masterXfer.rxData = NULL;
	masterXfer.dataSize = 4;
	masterXfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;

	DSPI_MasterTransferBlocking(SPI0, &masterXfer);
}

void memory_write_page(log_struct_t* log)
{
	dspi_transfer_t masterXfer;
	uint32_t address = log->address;

	log->data[0] = WRITE_COMMAND;
	log->data[1] = ((address) >> SHIFT_PART_1) & MASK_8_BYTES;
	log->data[2] = ((address) >> SHIFT_PART_2) & MASK_8_BYTES;
	log->data[3] = ((address) >> SHIFT_PART_3) & MASK_8_BYTES;

	masterXfer.txData = log->data;
	masterXfer.rxData = NULL;
	masterXfer.dataSize = 250;
	masterXfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;

	DSPI_MasterTransferBlocking(SPI0, &masterXfer);
}

void memory_write_disable(void)
{
	dspi_transfer_t masterXfer;
	uint8_t data = WD_COMMAND;

	masterXfer.txData = &data;
	masterXfer.rxData = NULL;
	masterXfer.dataSize = 1;
	masterXfer.configFlags = kDSPI_MasterCtar1 | kDSPI_MasterPcs1 | kDSPI_MasterPcsContinuous;

	DSPI_MasterTransferBlocking(SPI0, &masterXfer);
}

void memory_read(log_struct_t* log)
{
	dspi_half_duplex_transfer_t masterXfer;
	uint32_t address = log->address;
	array_cmd[0] = 0x03;
	array_cmd[1] = ((address) >> SHIFT_PART_1) & MASK_8_BYTES;
	array_cmd[2] = ((address) >> SHIFT_PART_2) & MASK_8_BYTES;
	array_cmd[3] = ((address) >> SHIFT_PART_3) & MASK_8_BYTES;
	masterXfer.txData = array_cmd;
	masterXfer.rxData = log->data;
	masterXfer.txDataSize            = 4u;
	masterXfer.rxDataSize            = 250;
    masterXfer.isTransmitFirst       = true;
    masterXfer.isPcsAssertInTransfer = true;
    masterXfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;

    DSPI_MasterHalfDuplexTransferBlocking(SPI0, &masterXfer);
}
