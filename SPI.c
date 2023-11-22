
#include "SPI.h"
#include "fsl_dspi.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"
#include "clock_config.h"

void SPI_config(void)
{
	uint32_t srcClock_Hz;
	
	CLOCK_SetSimSafeDivs();

	dspi_master_config_t masterConfig;

	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortC);
	PORT_SetPinMux(PORTD, PIN0_IDX, kPORT_MuxAlt2);
	PORT_SetPinMux(PORTD, PIN1_IDX, kPORT_MuxAlt2);
	PORT_SetPinMux(PORTD, PIN2_IDX, kPORT_MuxAlt2);
	PORT_SetPinMux(PORTD, PIN3_IDX, kPORT_MuxAlt2);
	PORT_SetPinMux(PORTC, PIN3_IDX, kPORT_MuxAlt2);
	/*-------------------------------------------Ctar0--------------------------------------------------*/
	masterConfig.whichCtar 									= kDSPI_Ctar0; //Una área para configurar
	masterConfig.ctarConfig.baudRate 						= TRANSFER_BAUDRATE;
	masterConfig.ctarConfig.bitsPerFrame 					= 8U;
	masterConfig.ctarConfig.cpol 							= kDSPI_ClockPolarityActiveHigh;
	masterConfig.ctarConfig.cpha 							= kDSPI_ClockPhaseFirstEdge;
	masterConfig.ctarConfig.direction 						= kDSPI_MsbFirst; //Modo de transmisión
	masterConfig.ctarConfig.pcsToSckDelayInNanoSec 			= 1000000000U / TRANSFER_BAUDRATE;
	masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec 		= 1000000000U / TRANSFER_BAUDRATE;
	masterConfig.ctarConfig.betweenTransferDelayInNanoSec 	= 1000000000U / TRANSFER_BAUDRATE;

	masterConfig.whichPcs 			= kDSPI_Pcs0;
	masterConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;

	masterConfig.enableContinuousSCK 		= false; //Para que siempre este el reloj dandolo todo
	masterConfig.enableRxFifoOverWrite 		= false; //No usamos fifo de contención de datos
	masterConfig.enableModifiedTimingFormat = false; //
	masterConfig.samplePoint 				= kDSPI_SckToSin0Clock; //Donde tomar la muestra, es la sincronia

	srcClock_Hz = CLOCK_GetFreq(DSPI0_CLK_SRC); //Configuración
	DSPI_MasterInit(SPI0, &masterConfig, srcClock_Hz);
	/*----------------------------------------Ctar1-------------------------------------*/
	masterConfig.whichCtar 									= kDSPI_Ctar1; //Una área para configurar
	masterConfig.ctarConfig.baudRate 						= TRANSFER_BAUDRATE_MEM;
	masterConfig.ctarConfig.bitsPerFrame 					= 8U;
	masterConfig.ctarConfig.cpol 							= kDSPI_ClockPolarityActiveLow;
	masterConfig.ctarConfig.cpha 							= kDSPI_ClockPhaseSecondEdge;
	masterConfig.ctarConfig.direction 						= kDSPI_MsbFirst; //Modo de transmisión
	masterConfig.ctarConfig.pcsToSckDelayInNanoSec 			= 0U;
	masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec 		= 0U;
	masterConfig.ctarConfig.betweenTransferDelayInNanoSec 	= 0U;

	masterConfig.whichPcs 			= kDSPI_Pcs1;
	masterConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;

	masterConfig.enableContinuousSCK 		= false; //Para que siempre este el reloj dandolo todo
	masterConfig.enableRxFifoOverWrite 		= false; //No usamos fifo de contención de datos
	masterConfig.enableModifiedTimingFormat = false; //
	masterConfig.samplePoint 				= kDSPI_SckToSin0Clock; //Donde tomar la muestra, es la sincronia

	DSPI_MasterInit(SPI0, &masterConfig, srcClock_Hz);


}

