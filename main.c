

/**
 * @file    Proyecto.c
 * @brief   Application entry point.
 */

#include "NVIC.h"
#include "control_nintendo.h"

int main(void)
{
	static uint8_t g_array_buttons_control_1[8] = {0};
	static uint8_t g_array_buttons_control_2[8] = {0};

	control_nintendo_init();

	for(;;)
	{
		control_nintendo_control(CONTROL_1, g_array_buttons_control_1);
		control_nintendo_control(CONTROL_2, g_array_buttons_control_2);
	}

}
