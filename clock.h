/**
 * @file clock.h
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * @brief 	Definitions for the clock module.
 *
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <stdio.h>
#include "MK64F12.h"
#include "fsl_clock.h"

#define MCG_PLL_DISABLE (0U)                     /*!< MCGPLLCLK disabled */
#define OSC_CAP0P 		(0U)                     /*!< Oscillator 0pF capacitor load */
#define DIVIDED_15		(0xeU)
#define MULTIPLIED_30	(0x6U)
#define OSC_FREQ		(50000000U)

/*!
 * @brief Initialization of clock to 100MHz
 */
void clock_init(void);

#endif /* CLOCK_H_ */
