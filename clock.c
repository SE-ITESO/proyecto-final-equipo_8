/**
 * @file clock.c
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * @brief 	Process to put the clock at 100M Hz.
 *
 */

#include "clock.h"
void clock_init(void)
{
	mcg_pll_config_t 	 pll0Config =
	{
			.enableMode = MCG_PLL_DISABLE, /* MCGPLLCLK disabled */
			.prdiv      = DIVIDED_15,            /* PLL Reference divider: divided by 15 */
			.vdiv       = MULTIPLIED_30,            /* VCO divider: multiplied by 30 */
	};


	const osc_config_t osc_config = {
			.freq        = OSC_FREQ,    /* Oscillator frequency: 50000000Hz */
			.capLoad     = (OSC_CAP0P),  /* Oscillator capacity load: 0pF */
			.workMode    = kOSC_ModeExt, /* Use external clock */
			.oscerConfig = {
					.enableMode =
							kOSC_ErClkEnable, /* Enable external reference clock, disable external reference clock in STOP mode */
			}};


	CLOCK_SetSimSafeDivs();

	CLOCK_InitOsc0(&osc_config);

	CLOCK_SetXtal0Freq(osc_config.freq);

	CLOCK_SetFbiMode(kMCG_Dmx32Default, kMCG_DrsLow, NULL);
	CLOCK_SetFbeMode(0, kMCG_Dmx32Default, kMCG_DrsLow, NULL);
	CLOCK_SetPbeMode(kMCG_PllClkSelPll0, &pll0Config);
	CLOCK_SetPeeMode();
}
