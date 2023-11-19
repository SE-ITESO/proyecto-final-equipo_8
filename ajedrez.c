/*
 * ajedrez.c
 *
 *  Created on: 14 nov 2023
 *      Author: brand
 */

#include "ajedrez.h"

static uint8_t g_array_init[] = "\033[0;34;46m"
		"\033[2J";

static uint8_t g_array_clear[] = "\033[2J";

static uint8_t g_buttons_control_1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t g_buttons_control_2[8] = {0, 0, 0, 0, 0, 0, 0, 0};

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

static uint8_t g_array_guardado_1[] =
		// G    U   A    R    D    A    R        E    N
		"---- -  - --- ----- ---- --- -----     --- -   -"
		"\e[1B\e[48D"
		"-    -  - - -  -  -  - - - -  -  -     -   --  -"
		"\e[1B\e[48D"
		"- -- -  - ---  ----  - - ---  ----     --- - - -"
		"\e[1B\e[48D"
		"-  - -  - - -  - -   - - - -  - -      -   -  --"
		"\e[1B\e[48D"
		"---- ---- - -  -  - ---- - -  -  -     --- -   -";

static uint8_t g_array_guardado_2[] =
		// N    O        G    U   A    R    D    A    R
		"-   - ----     ---- -  - --- ----- ---- --- -----"
		"\e[1B\e[49D"
		"--  - -  -     -    -  - - -  -  -  - - - -  -  -"
		"\e[1B\e[49D"
		"- - - -  -     - -- -  - ---  ----  - - ---  ----"
		"\e[1B\e[49D"
		"-  -- -  -     -  - -  - - -  - -   - - - -  - - "
		"\e[1B\e[49D"
		"-   - ----     ---- ---- - -  -  - ---- - -  -  -";

static uint8_t g_array_guardado_3[] =
		//L   O   G        1
		"-   --- ----      - "
		"\e[1B\e[20D"
		"-   - - -        -- "
		"\e[1B\e[20D"
		"-   - - - --      - "
		"\e[1B\e[20D"
		"-   - - -  -      - "
		"\e[1B\e[20D"
		"--- --- ----     ---";

static uint8_t g_array_guardado_4[] =
		//L   O   G        2
		"-   --- ----     ----"
		"\e[1B\e[21D"
		"-   - - -           -"
		"\e[1B\e[21D"
		"-   - - - --     ----"
		"\e[1B\e[21D"
		"-   - - -  -     -   "
		"\e[1B\e[21D"
		"--- --- ----     ----";

static uint8_t g_array_guardado_5[] =
		//L   O   G        3
		"-   --- ----     ---"
		"\e[1B\e[20D"
		"-   - - -          -"
		"\e[1B\e[20D"
		"-   - - - --     ---"
		"\e[1B\e[20D"
		"-   - - -  -       -"
		"\e[1B\e[20D"
		"--- --- ----     ---";

static uint8_t g_array_guardado_6[] =
		//L   O   G        4
		"-   --- ----     -  -"
		"\e[1B\e[21D"
		"-   - - -        -  -"
		"\e[1B\e[21D"
		"-   - - - --     ----"
		"\e[1B\e[21D"
		"-   - - -  -        -"
		"\e[1B\e[21D"
		"--- --- ----        -";

static uint8_t g_array_guardado_7[] =
		//L   O   G        5
		"-   --- ----     ----"
		"\e[1B\e[21D"
		"-   - - -        -   "
		"\e[1B\e[21D"
		"-   - - - --     ----"
		"\e[1B\e[21D"
		"-   - - -  -        -"
		"\e[1B\e[21D"
		"--- --- ----     ----";

static uint8_t g_array_regresar[] =
		// R    E   G     R    E   S    A    R
		"----- --- ---- ----- --- ---- --- -----"
		"\e[1B\e[39D"
		" -  - -   -     -  - -   -    - -  -  -"
		"\e[1B\e[39D"
		" ---- --- - --  ---- --- ---- ---  ----"
		"\e[1B\e[39D"
		" - -  -   -  -  - -  -      - - -  - - "
		"\e[1B\e[39D"
		" -  - --- ----  -  - --- ---- - -  -  -";

static ventana_function g_array_ventana_function[] = {ajedrez_v_menu, ajedrez_v_save};

static uint8_t g_ventana = v_inicio;
static uint8_t g_modo = 0;


void ajedrez_init(void)
{
	control_nintendo_init();
	UART_put_string(UART_0, g_array_init);
	UART_put_string(UART_4, g_array_init);

	tablero_switch_string(g_array_menu_1, '-', 219);
	tablero_switch_string(g_array_menu_2, '-', 219);

	tablero_switch_string(g_array_guardado_1, '-', 219);
	tablero_switch_string(g_array_guardado_2, '-', 219);
	tablero_switch_string(g_array_guardado_3, '-', 219);
	tablero_switch_string(g_array_guardado_4, '-', 219);
	tablero_switch_string(g_array_guardado_5, '-', 219);
	tablero_switch_string(g_array_guardado_6, '-', 219);
	tablero_switch_string(g_array_guardado_7, '-', 219);

	tablero_switch_string(g_array_regresar, '-', 219);
}

void ajedrez_control(void)
{
	control_nintendo_control(CONTROL_1, g_buttons_control_1);
	control_nintendo_control(CONTROL_2, g_buttons_control_2);
	g_array_ventana_function[g_ventana](&g_modo);
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
		if((FALSE != g_buttons_control_1[START]) | (FALSE != g_buttons_control_2[START]))
		{
			control_nintendo_clear(g_buttons_control_1);
			control_nintendo_clear(g_buttons_control_2);
			UART_put_string(UART_0, g_array_clear);
			g_ventana = v_save;
			*modo = 0;
		}
		break;
	}
}

void ajedrez_v_save(uint8_t * modo)
{
	switch(*modo)
	{
	case 0:
		fichas_mover_cursor(UART_0, 10, 10);
		UART_put_string(UART_0, g_array_guardado_1);
		fichas_mover_cursor(UART_0, 15, 15);
		UART_put_string(UART_0, g_array_guardado_2);
		fichas_mover_cursor(UART_0, 15, 20);
		UART_put_string(UART_0, g_array_guardado_3);
		fichas_mover_cursor(UART_0, 15, 25);
		UART_put_string(UART_0, g_array_guardado_4);
		fichas_mover_cursor(UART_0, 15, 30);
		UART_put_string(UART_0, g_array_guardado_5);
		fichas_mover_cursor(UART_0, 15, 35);
		UART_put_string(UART_0, g_array_guardado_6);
		fichas_mover_cursor(UART_0, 15, 40);
		UART_put_string(UART_0, g_array_guardado_7);
		*modo = 1;
	case 1:  		//espera a que se seleccione una opción
		break;
	}
}
