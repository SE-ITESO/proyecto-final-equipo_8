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

static uint8_t g_array_cmd[4] = {0x03, 0x00, 0x00, 0x00};

uint8_t g_PIT_memory_flag = 0;

static uint8_t g_movimientos[250] = {0};
static log_struct_t g_current_log;
static uint8_t g_movimientos_index = 5;
static uint8_t *p_aux_ptr;
static uint8_t g_ptr_index = 0;

void PIT_set_flag_memory(uint8_t pit)
{
	g_PIT_memory_flag++;
}


void memory_create_log(uint8_t log_number)
{
	uint32_t address;

	switch (log_number)
	{
	case 1:
		address = 0x040000;
	break;
	case 2:
		address = 0x041000;
	break;
	case 3:
		address = 0x042000;
	break;
	case 4:
		address = 0x043000;
	break;
	case 5:
		address = 0x044000;
	break;

	default:
		address = 0x0;
	break;
	}

	if (0x0 != address)
	{
		log_config(0, &address);
	}

}

void memory_add_movimiento(uint8_t x_old, uint8_t y_old, uint8_t x_new, uint8_t y_new)
{
	uint8_t origen = 0;
	uint8_t destino = 0;

	origen  = (x_old << 4) | (y_old);
	destino = (x_new << 4) | (y_new);

	log_config(1, &origen);
	log_config(1, &destino);
}

void memory_send_log(void)
{
	log_config(2, 0);
}

void memory_read_log(void* data)
{
	log_config(3, data);
}

void log_config(uint8_t operation, void* data)
{

	switch (operation)
	{
	case 0:
		g_current_log.address = *(uint32_t*)data;
		g_current_log.data = g_movimientos;
	break;
	case 1:
		g_current_log.data[g_movimientos_index] = *(uint8_t*)data;
		g_movimientos_index++;
	break;
	case 2:
		g_current_log.data[4] = (g_movimientos_index - 5);
		memory_write_log(&g_current_log);
	break;
	case 3:
		memory_read(&g_current_log);
		p_aux_ptr = data;
		for (g_ptr_index = 0; g_ptr_index < 250; g_ptr_index++)
		{
			*p_aux_ptr = g_current_log.data[g_ptr_index];
			p_aux_ptr++;
		}
	break;
	}
}

void memory_write_log(log_struct_t* log)
{

	uint8_t etapa = 0;

	PIT_set_time(PIT_CH1, TIEMPO_CH1);
	PIT_enable_channel_interrupt(PIT_CH1);
	PIT_callback_init(channel_1, PIT_set_flag_memory);
	PIT_start_channel(PIT_CH1);
	NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ, PRIORITY_3);

	while(etapa < 5)
	{

		if (g_PIT_memory_flag)
		{
			g_PIT_memory_flag = 0;

			switch (etapa)
			{
			case 0:
				memory_write_enable();
			break;
			case 1:
				memory_erase_page(log);
			break;
			case 2:
				memory_write_enable();
			break;
			case 3:
				memory_write_page(log);
			break;
			case 4:
				memory_write_disable();
			break;
			case 5:
			break;

			default:
				memory_write_disable();
			break;
			}

			if (etapa<5)
			{
				etapa++;
			}
		}
	}

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
	masterXfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;

	DSPI_MasterTransferBlocking(SPI0, &masterXfer);
}

void memory_read(log_struct_t* log)
{
	dspi_half_duplex_transfer_t masterXfer;
	uint32_t address = log->address;
	g_array_cmd[0] = 0x03;
	g_array_cmd[1] = ((address) >> SHIFT_PART_1) & MASK_8_BYTES;
	g_array_cmd[2] = ((address) >> SHIFT_PART_2) & MASK_8_BYTES;
	g_array_cmd[3] = ((address) >> SHIFT_PART_3) & MASK_8_BYTES;
	masterXfer.txData = g_array_cmd;
	masterXfer.rxData = log->data;
	masterXfer.txDataSize            = 4u;
	masterXfer.rxDataSize            = 250;
    masterXfer.isTransmitFirst       = true;
    masterXfer.isPcsAssertInTransfer = true;
    masterXfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;

    DSPI_MasterHalfDuplexTransferBlocking(SPI0, &masterXfer);
}
