/*
 * ajedrez.c
 *
 *  Created on: 14 nov 2023
 *      Author: brand
 */

#include "ajedrez.h"

static uint8_t g_array_init[] = "\033[0;34;46m"
		"\033[2J";

static uint8_t g_array_menu_1[] =
		 //S    T    A	  R	    T	   ->	 I   N    I   C   I   A    R         J   U    E   G     O
		"---- ----- --- ----- -----     -   --- -   - --- --- --- --- -----      --- -  - --- ---- ----"
		"\e[1B\e[94D"
		"-      -   - -  -  -   -        -   -  --  -  -  -    -  - -  -  -       -  -  - -   -    -  -"
		"\e[1B\e[94D"
		"----   -   ---  ----   -   -------  -  - - -  -  -    -  ---  ----       -  -  - --- - -- -  -"
		"\e[1B\e[94D"
		"   -   -   - -  - -    -        -   -  -  --  -  -    -  - -  - -      - -  -  - -   -  - -  -"
		"\e[1B\e[94D"
		"----   -   - -  -  -   -       -   --- -   - --- --- --- - -  -  -     ---  ---- --- ---- ----"
		"\e[5B\e[94D";

static uint8_t g_array_menu_2[] =
		//S    E   L   E   C    T      ->     J   U    E   G     O    S        P    R    E    V    I   O    S
		"---- --- -   --- --- -----     -    --- -  - --- ---- ---- ----     ---- ----- --- -   - --- ---- ----"
		"\e[1B\e[102D"
		"-    -   -   -   -     -        -    -  -  - -   -    -  - -         - -  -  - -   -   -  -  -  - -   "
		"\e[1B\e[102D"
		"---- --- -   --- -     -   -------   -  -  - --- - -- -  - ----      ---  ---- --- -   -  -  -  - ----"
		"\e[1B\e[102D"
		"   - -   -   -   -     -        -  - -  -  - -   -  - -  -    -      -    - -  -    - -   -  -  -    -"
		"\e[1B\e[102D"
		"---- --- --- --- ---   -       -   ---  ---- --- ---- ---- ----      -    -  - ---   -   --- ---- ----";

static ventana_function g_array_ventana_function[] = {ajedrez_v_menu};

static uint8_t g_ventana = v_inicio;
static uint8_t g_modo = 0;


void ajedrez_init(void)
{
	UART_put_string(UART_0, g_array_init);
	UART_put_string(UART_4, g_array_init);

	tablero_switch_string(g_array_menu_1, '-', 219);
	tablero_switch_string(g_array_menu_2, '-', 219);
}

void ajedrez_v_menu(uint8_t * modo)
{
	switch(*modo)
	{
	case 0:
		fichas_mover_cursor(UART_0, 10, 10);
		UART_put_string(UART_0, g_array_menu_1);
		UART_put_string(UART_0, g_array_menu_2);
		*modo = 1;
	case 1:  		//espera a que se seleccione una opción
		break;
	}
}

void ajedrez_control(void)
{
	g_array_ventana_function[g_ventana](&g_modo);
}
