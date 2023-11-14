

/**
 * @file    Proyecto.c
 * @brief   Application entry point.
 */

#include "NVIC.h"
#include "control_nintendo.h"

int main(void)
{
	static uint8_t g_array_buttons[8] = {0};

	control_nintendo_init();

	for(;;)
	{
		control_nintendo_control(g_array_buttons);
	}

}
