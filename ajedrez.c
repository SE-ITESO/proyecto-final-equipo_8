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

static uint8_t g_log = log_0;

static uint8_t g_turno = jugador_1;

static uint8_t g_reinicio = TRUE;

static uint8_t g_ganador = jugador_1;

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

static uint8_t g_array_repeticion_1[] =
	    // V   E   R          L   O    G
		"-  - --- ----      -    ---- ----- "
		"\e[1B\e[35D"
		"-  - -   -  -      -    -  - -     "
		"\e[1B\e[35D"
		"-  - --- ----      -    -  - -  -- "
		"\e[1B\e[35D"
		"-  - -   - -       -    -  - -   - "
		"\e[1B\e[35D"
		" --  --- -  -      ---- ---- ----- ";

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
		"-   ---- ----      - "
		"\e[1B\e[21D"
		"-   -  - -        -- "
		"\e[1B\e[21D"
		"-   -  - - --      - "
		"\e[1B\e[21D"
		"-   -  - -  -      - "
		"\e[1B\e[21D"
		"--- ---- ----     ---";

static uint8_t g_array_guardado_4[] =
		//L   O   G        2
		"-   ---- ----     ----"
		"\e[1B\e[22D"
		"-   -  - -           -"
		"\e[1B\e[22D"
		"-   -  - - --     ----"
		"\e[1B\e[22D"
		"-   -  - -  -     -   "
		"\e[1B\e[22D"
		"--- ---- ----     ----";

static uint8_t g_array_guardado_5[] =
		//L   O   G        3
		"-   ---- ----     ---"
		"\e[1B\e[21D"
		"-   -  - -          -"
		"\e[1B\e[21D"
		"-   -  - - --     ---"
		"\e[1B\e[21D"
		"-   -  - -  -       -"
		"\e[1B\e[21D"
		"--- ---- ----     ---";

static uint8_t g_array_guardado_6[] =
		//L   O   G        4
		"-   ---- ----     -  -"
		"\e[1B\e[22D"
		"-   -  - -        -  -"
		"\e[1B\e[22D"
		"-   -  - - --     ----"
		"\e[1B\e[22D"
		"-   -  - -  -        -"
		"\e[1B\e[22D"
		"--- ---- ----        -";

static uint8_t g_array_guardado_7[] =
		//L   O   G        5
		"-   ---- ----     ----"
		"\e[1B\e[22D"
		"-   -  - -        -   "
		"\e[1B\e[22D"
		"-   -  - - --     ----"
		"\e[1B\e[22D"
		"-   -  - -  -        -"
		"\e[1B\e[22D"
		"--- ---- ----     ----";

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

static uint8_t g_array_pausa_1[] =
		//  T   A    B   L   A   S
		"----- --- ---- -   --- ----"
		"\e[1B\e[27D"
		"  -   - -  - - -   - - -   "
		"\e[1B\e[27D"
		"  -   ---  --- -   --- ----"
		"\e[1B\e[27D"
		"  -   - -  - - -   - -    -"
		"\e[1B\e[27D"
		"  -   - - ---- --- - - ----";

static uint8_t g_array_pausa_2[] =
		// R    E    T    I    R    A    D   A
		"----- --- ----- --- ----- --- ---- ---"
		"\e[1B\e[38D"
		" -  - -     -    -   -  - - -  - - - -"
		"\e[1B\e[38D"
		" ---- ---   -    -   ---- ---  - - ---"
		"\e[1B\e[38D"
		" - -  -     -    -   - -  - -  - - - -"
		"\e[1B\e[38D"
		" -  - ---   -   ---  -  - - - ---- - -";

static uint8_t g_array_tablas_1[] =
		//¿   T   A    B   L   A   S    ?
		" - ----- --- ---- -   --- ---- --"
		"\e[1B\e[33D"
		"     -   - -  - - -   - - -     -"
		"\e[1B\e[33D"
		"--   -   ---  --- -   --- ---- --"
		"\e[1B\e[33D"
		"-    -   - -  - - -   - -    -   "
		"\e[1B\e[33D"
		"--   -   - - ---- --- - - ---- - ";

static uint8_t g_array_si[] =
		// S I
		"---- ---"
		"\e[1B\e[8D"
		"-     - "
		"\e[1B\e[8D"
		"----  - "
		"\e[1B\e[8D"
		"   -  - "
		"\e[1B\e[8D"
		"---- ---";

static uint8_t g_array_no[] =
		// N    O
		"-   - ----"
		"\e[1B\e[10D"
		"--  - -  -"
		"\e[1B\e[10D"
		"- - - -  -"
		"\e[1B\e[10D"
		"-  -- -  -"
		"\e[1B\e[10D"
		"-   - ----";

static uint8_t g_array_perdiste [] =
		//P    E    R     D   I    S    T    E
		"---- --- ----- ---- --- ---- ----- ---"
		"\e[1B\e[38D"
		" - - -    -  -  - -  -  -      -   -  "
		"\e[1B\e[38D"
		" --- ---  ----  - -  -  ----   -   ---"
		"\e[1B\e[38D"
		" -   -    - -   - -  -     -   -   -  "
		"\e[1B\e[38D"
		" -   ---  -  - ---- --- ----   -   ---";

static uint8_t g_array_ganaste [] =
		//G    A    N    A   S     T    E
		"---- --- -   - --- ---- ----- ---"
		"\e[1B\e[33D"
		"-    - - --  - - - -      -   -  "
		"\e[1B\e[33D"
		"- -- --- - - - --- ----   -   ---"
		"\e[1B\e[33D"
		"-  - - - -  -- - -    -   -   -  "
		"\e[1B\e[33D"
		"---- - - -   - - - ----   -   ---";

static uint8_t g_array_espera_1 [] =
		// S    T    A    R     T             M    E    N    U
		"---- ----- --- ----- -----     -   -   - --- -   - -  -"
		"\e[1B\e[55D"
		"-      -   - -  -  -   -        -  -- -- -   --  - -  -"
		"\e[1B\e[55D"
		"----   -   ---  ----   -   ------- - - - --- - - - -  -"
		"\e[1B\e[55D"
		"   -   -   - -  - -    -        -  -   - -   -  -- -  -"
		"\e[1B\e[55D"
		"----   -   - -  -  -   -       -   -   - --- -   - ----";


static ventana_function g_array_ventana_function[] =
		{ajedrez_v_menu, ajedrez_v_save,
		ajedrez_v_juego, ajedrez_v_pausa,
		ajedrez_v_tablas, ajedrez_v_espera,
		ajedrez_v_derrota, ajedrez_v_leer_log,
		ajedrez_v_repeticion};

static uint8_t g_ventana = v_inicio;
static uint8_t g_modo = 0;


void ajedrez_init(void)
{
	control_nintendo_init();
	UART_put_string(UART_0, g_array_init);
	UART_put_string(UART_4, g_array_init);

	tablero_switch_string(g_array_menu_1, '-', 219);
	tablero_switch_string(g_array_menu_2, '-', 219);

	tablero_switch_string(g_array_repeticion_1, '-', 219);

	tablero_switch_string(g_array_guardado_1, '-', 219);
	tablero_switch_string(g_array_guardado_2, '-', 219);
	tablero_switch_string(g_array_guardado_3, '-', 219);
	tablero_switch_string(g_array_guardado_4, '-', 219);
	tablero_switch_string(g_array_guardado_5, '-', 219);
	tablero_switch_string(g_array_guardado_6, '-', 219);
	tablero_switch_string(g_array_guardado_7, '-', 219);

	tablero_switch_string(g_array_pausa_1, '-', 219);
	tablero_switch_string(g_array_pausa_2, '-', 219);

	tablero_switch_string(g_array_tablas_1, '-', 219);
	tablero_switch_string(g_array_si, '-', 219);
	tablero_switch_string(g_array_no, '-', 219);

	tablero_switch_string(g_array_perdiste, '-', 219);
	tablero_switch_string(g_array_ganaste, '-', 219);
	tablero_switch_string(g_array_espera_1, '-', 219);

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
		UART_put_string(UART_0, g_array_clear);
		fichas_mover_cursor(UART_0, 10, 10);
		UART_put_string(UART_0, g_array_menu_1);
		UART_put_string(UART_0, g_array_menu_2);

		UART_put_string(UART_4, g_array_clear);
		fichas_mover_cursor(UART_4, 10, 10);
		UART_put_string(UART_4, g_array_menu_1);
		UART_put_string(UART_4, g_array_menu_2);
		*modo = 1;
	case 1:  		//espera a que se seleccione una opción
		if((FALSE != g_buttons_control_1[START]) | (FALSE != g_buttons_control_2[START]))
		{
			control_nintendo_clear(g_buttons_control_1);
			control_nintendo_clear(g_buttons_control_2);
			g_ventana = v_save;
			*modo = 0;
		}else if((FALSE != g_buttons_control_1[SELECT]) | (FALSE != g_buttons_control_2[SELECT]))
		{
			control_nintendo_clear(g_buttons_control_1);
			control_nintendo_clear(g_buttons_control_2);
			g_ventana = v_leer;
			*modo = 0;
		}
		break;
	}
}

void ajedrez_v_save(uint8_t * modo)
{
	static uint8_t coor_y;
	switch(*modo)
	{
	case 0:
		UART_put_string(UART_0, g_array_clear);
		fichas_mover_cursor(UART_0, 10, 10);
		UART_put_string(UART_0, g_array_guardado_1);
		fichas_mover_cursor(UART_0, 25, 16);
		UART_put_string(UART_0, g_array_guardado_2);
		fichas_mover_cursor(UART_0, 25, 22);
		UART_put_string(UART_0, g_array_guardado_3);
		fichas_mover_cursor(UART_0, 25, 28);
		UART_put_string(UART_0, g_array_guardado_4);
		fichas_mover_cursor(UART_0, 25, 34);
		UART_put_string(UART_0, g_array_guardado_5);
		fichas_mover_cursor(UART_0, 25, 40);
		UART_put_string(UART_0, g_array_guardado_6);
		fichas_mover_cursor(UART_0, 25, 46);
		UART_put_string(UART_0, g_array_guardado_7);

		fichas_mover_cursor(UART_0, 25, 52);
		UART_put_string(UART_0, g_array_regresar);

		fichas_mover_cursor(UART_0, 10, 16);
		fichas_seleccion_print(UART_0, rojo);


		UART_put_string(UART_4, g_array_clear);
		fichas_mover_cursor(UART_4, 10, 10);
		UART_put_string(UART_4, g_array_guardado_1);
		fichas_mover_cursor(UART_4, 25, 16);
		UART_put_string(UART_4, g_array_guardado_2);
		fichas_mover_cursor(UART_4, 25, 22);
		UART_put_string(UART_4, g_array_guardado_3);
		fichas_mover_cursor(UART_4, 25, 28);
		UART_put_string(UART_4, g_array_guardado_4);
		fichas_mover_cursor(UART_4, 25, 34);
		UART_put_string(UART_4, g_array_guardado_5);
		fichas_mover_cursor(UART_4, 25, 40);
		UART_put_string(UART_4, g_array_guardado_6);
		fichas_mover_cursor(UART_4, 25, 46);
		UART_put_string(UART_4, g_array_guardado_7);

		fichas_mover_cursor(UART_4, 25, 52);
		UART_put_string(UART_4, g_array_regresar);

		fichas_mover_cursor(UART_4, 10, 16);
		fichas_seleccion_print(UART_4, rojo);
		coor_y = 16;
		*modo = 1;
	case 1:  		//espera a que se seleccione una opción
		if((FALSE != g_buttons_control_1[DOWN]) | (FALSE != g_buttons_control_2[DOWN]))
		{
			fichas_mover_cursor(UART_0, 10, coor_y);
			fichas_seleccion_print(UART_0, cyan);
			fichas_mover_cursor(UART_4, 10, coor_y);
			fichas_seleccion_print(UART_4, cyan);

			if(52 == coor_y)
			{
				coor_y = 16;
			}
			else
			{
				coor_y += 6;
			}

			fichas_mover_cursor(UART_0, 10, coor_y);
			fichas_seleccion_print(UART_0, rojo);

			fichas_mover_cursor(UART_4, 10, coor_y);
			fichas_seleccion_print(UART_4, rojo);

			g_buttons_control_1[DOWN] = FALSE;
			g_buttons_control_2[DOWN] = FALSE;
		}
		else if((FALSE != g_buttons_control_1[UP]) | (FALSE != g_buttons_control_2[UP]))
		{
			fichas_mover_cursor(UART_0, 10, coor_y);
			fichas_seleccion_print(UART_0, cyan);
			fichas_mover_cursor(UART_4, 10, coor_y);
			fichas_seleccion_print(UART_4, cyan);

			if(16 == coor_y)
			{
				coor_y = 52;
			}
			else
			{
				coor_y -= 6;
			}

			fichas_mover_cursor(UART_0, 10, coor_y);
			fichas_seleccion_print(UART_0, rojo);
			fichas_mover_cursor(UART_4, 10, coor_y);
			fichas_seleccion_print(UART_4, rojo);
			g_buttons_control_1[UP] = FALSE;
			g_buttons_control_2[UP] = FALSE;
		}
		else if((FALSE != g_buttons_control_1[A]) | (FALSE != g_buttons_control_2[A]))
		{
			coor_y = (coor_y - 16) / 6;
			if(6 > coor_y)
			{
				g_log = coor_y;
				memory_create_log(coor_y);
				tablero_assign_log_number(coor_y);
				control_nintendo_clear(g_buttons_control_1);
				control_nintendo_clear(g_buttons_control_2);
				*modo = 0;
				g_ventana = v_juego;
			}
			else
			{
				control_nintendo_clear(g_buttons_control_1);
				control_nintendo_clear(g_buttons_control_2);
				fichas_color(UART_0, azul);
				fichas_color(UART_4, azul);
				*modo = 0;
				g_ventana = v_inicio;
			}
		}
		break;
	}
}

void ajedrez_v_juego(uint8_t * modo)
{
	uint8_t status;
	static uint8_t* pointer_button;
	static uint8_t time_over;

	switch(*modo)
	{
	case 0:
		UART_put_string(UART_0, g_array_clear);
		UART_put_string(UART_4, g_array_clear);
		tablero_init();
		temporizador_init(1, 0);
		g_turno   = jugador_1;
		*modo = 1;
	case 1:
		if(jugador_1 == g_turno)
		{
			pointer_button = g_buttons_control_1;
		}
		else
		{
			pointer_button = g_buttons_control_2;
		}
		status = tablero_control(&g_turno, pointer_button, &g_reinicio);

		time_over = temporizador_update(g_turno);
		if (1 == time_over)
		{
			g_ventana = v_derrota;
			*modo = 0;
			g_ganador = jugador_2 - g_turno;
		}

		if(s_change_t == status)
		{
			if(jugador_1 == g_turno)
			{
				control_nintendo_clear(g_buttons_control_1);
			}
			else
			{
				control_nintendo_clear(g_buttons_control_2);
			}
		}
		else if(s_jaque_mate == status)
		{
			g_ventana = v_derrota;
			*modo = 0;
			control_nintendo_clear(g_buttons_control_1);
			control_nintendo_clear(g_buttons_control_2);
			g_ganador = jugador_2 - g_turno;
		}
		else
		{
			if((jugador_1 == g_turno) & (TRUE == g_buttons_control_1[B]))
			{
				*modo = 0;
				g_ventana = v_pausa;
				control_nintendo_clear(g_buttons_control_1);
			}
			else if((jugador_2 == g_turno) & (TRUE == g_buttons_control_2[B]))
			{
				*modo = 0;
				g_ventana = v_pausa;
				control_nintendo_clear(g_buttons_control_2);
			}
		}
		break;
	}
}

void ajedrez_v_pausa(uint8_t * modo)
{
	static uint8_t* pointer_button;
	static uint8_t coor_y;
	uint8_t temp;

	switch(*modo)
	{
	case 0:
		UART_put_string((g_turno * 4), g_array_clear);
		fichas_color((g_turno * 4), negras);
		fichas_mover_cursor((g_turno * 4), 25, 10);
		UART_put_string((g_turno * 4), g_array_regresar);
		fichas_mover_cursor((g_turno * 4), 25, 16);
		UART_put_string((g_turno * 4), g_array_pausa_1);
		fichas_mover_cursor((g_turno * 4), 25, 22);
		UART_put_string((g_turno * 4), g_array_pausa_2);
		fichas_mover_cursor((g_turno * 4), 10, 10);
		fichas_seleccion_print((g_turno * 4), rojo);
		if(jugador_1 == g_turno)
		{
			pointer_button = g_buttons_control_1;
		}
		else
		{
			pointer_button = g_buttons_control_2;
		}
		*modo = 1;
		coor_y = 10;
		break;
	case 1:
		if(FALSE != *(pointer_button + DOWN))
		{
			fichas_mover_cursor((g_turno * 4), 10, coor_y);
			fichas_seleccion_print((g_turno * 4), cyan);
			if(22 == coor_y)
			{
				coor_y = 10;
			}
			else
			{
				coor_y += 6;
			}
			fichas_mover_cursor((g_turno * 4), 10, coor_y);
			fichas_seleccion_print((g_turno * 4), rojo);

			*(pointer_button + DOWN) = FALSE;
		}

		else if(FALSE != *(pointer_button + UP))
		{
			fichas_mover_cursor((g_turno * 4), 10, coor_y);
			fichas_seleccion_print((g_turno * 4), cyan);
			if(10 == coor_y)
			{
				coor_y = 22;
			}
			else
			{
				coor_y -= 6;
			}
			fichas_mover_cursor((g_turno * 4), 10, coor_y);
			fichas_seleccion_print((g_turno * 4), rojo);

			*(pointer_button + UP) = FALSE;
		}

		else if(FALSE != *(pointer_button + A))
		{
			temp = (coor_y - 10) / 6;
			if(0 == temp)
			{
				*modo = 2;
			}
			else if(1 == temp)
			{
				g_ventana = v_tablas;
				*modo = 0;
				control_nintendo_clear(g_buttons_control_1);
				control_nintendo_clear(g_buttons_control_2);
			}
			else if(2 == temp)
			{
				g_ventana = v_derrota;
				*modo = 0;
				control_nintendo_clear(g_buttons_control_1);
				control_nintendo_clear(g_buttons_control_2);
				g_ganador = jugador_2 - g_turno;
			}
		}
		break;
	case 2:
		control_nintendo_clear(g_buttons_control_1);
		control_nintendo_clear(g_buttons_control_2);
		tablero_print_tablero();
		*modo = 1;
		g_ventana = v_juego;
		break;
	}
}

void ajedrez_v_tablas(uint8_t * modo)
{
	static uint8_t coor_y;
	uint8_t UART_num = UART_4 - (g_turno * 4);
	static uint8_t* pointer_button;
	uint8_t temp;

	switch(*modo)
	{
	case 0:
		UART_put_string(UART_0, g_array_clear);
		UART_put_string(UART_4, g_array_clear);

		fichas_color(UART_num, negras);
		fichas_mover_cursor(UART_num, 10, 10);
		UART_put_string(UART_num, g_array_tablas_1);
		fichas_mover_cursor(UART_num, 25, 16);
		UART_put_string(UART_num, g_array_si);
		fichas_mover_cursor(UART_num, 25, 22);
		UART_put_string(UART_num, g_array_no);
		fichas_mover_cursor(UART_num, 10, 16);
		fichas_seleccion_print(UART_num, rojo);
		if(jugador_1 == g_turno)
		{
			pointer_button = g_buttons_control_2;
		}
		else
		{
			pointer_button = g_buttons_control_1;
		}
		*modo = 1;
		coor_y = 16;

	case 1:
		if(FALSE != *(pointer_button + DOWN))
		{
			fichas_mover_cursor(UART_num, 10, coor_y);
			fichas_seleccion_print(UART_num, cyan);

			coor_y = (22 - coor_y) + 16;

			fichas_mover_cursor(UART_num, 10, coor_y);
			fichas_seleccion_print(UART_num, rojo);

			*(pointer_button + DOWN) = FALSE;
		}

		else if(FALSE != *(pointer_button + UP))
		{
			fichas_mover_cursor(UART_num, 10, coor_y);
			fichas_seleccion_print(UART_num, cyan);

			coor_y = (22 - coor_y) + 16;

			fichas_mover_cursor(UART_num, 10, coor_y);
			fichas_seleccion_print(UART_num, rojo);

			*(pointer_button + UP) = FALSE;
		}
		else if(FALSE != *(pointer_button + A))
		{
			temp = (coor_y - 16) / 6;
			if(0 == temp)
			{
				UART_put_string(UART_0, g_array_clear);
				fichas_color(UART_0, negras);
				fichas_mover_cursor(UART_0, 25, 10);
				UART_put_string(UART_0, g_array_pausa_1);

				UART_put_string(UART_4, g_array_clear);
				fichas_color(UART_4, negras);
				fichas_mover_cursor(UART_4, 25, 10);
				UART_put_string(UART_4, g_array_pausa_1);
				*modo = 0;
				g_ventana = v_espera;
			}
			else
			{
				control_nintendo_clear(g_buttons_control_1);
				control_nintendo_clear(g_buttons_control_2);
				tablero_print_tablero();
				*modo = 1;
				g_ventana = v_juego;
			}
		}
		break;
	}
}

void ajedrez_v_derrota(uint8_t * modo)
{
	uint8_t ganador = g_ganador * 4;
	uint8_t perdedor = UART_4 - ganador;

	switch(*modo)
	{
	case 0:
		UART_put_string(ganador, g_array_clear);
		fichas_color(ganador, negras);
		fichas_mover_cursor(ganador, 25, 10);
		UART_put_string(ganador, g_array_ganaste);

		UART_put_string(perdedor, g_array_clear);
		fichas_color(perdedor, negras);
		fichas_mover_cursor(perdedor, 25, 10);
		UART_put_string(perdedor, g_array_perdiste);

		if (0 != g_log)
		{
			memory_send_log();
		}

		control_nintendo_clear(g_buttons_control_1);
		control_nintendo_clear(g_buttons_control_2);

		*modo = 0;
		g_ventana = v_espera;
		break;
	}
}

void ajedrez_v_espera(uint8_t * modo)
{

	switch(*modo)
	{
	case 0:
		fichas_color(UART_0, negras);
		fichas_mover_cursor(UART_0, 40, 30);
		UART_put_string(UART_0, g_array_espera_1);

		fichas_color(UART_4, negras);
		fichas_mover_cursor(UART_4, 40, 30);
		UART_put_string(UART_4, g_array_espera_1);

		*modo = 1;
	case 1:
		if(FALSE != (g_buttons_control_1[START] | g_buttons_control_2[START]))
		{
			control_nintendo_clear(g_buttons_control_1);
			control_nintendo_clear(g_buttons_control_2);
			fichas_color(UART_0, azul);
			fichas_color(UART_4, azul);
			*modo = 0;
			g_ventana = v_inicio;
			g_reinicio = TRUE;
		}
		break;
	}
}

void ajedrez_v_leer_log(uint8_t * modo)
{
	static uint8_t coor_y;

	switch(*modo)
	{
	case 0:
		UART_put_string(UART_0, g_array_clear);
		fichas_mover_cursor(UART_0, 10, 10);
		UART_put_string(UART_0, g_array_repeticion_1);
		fichas_mover_cursor(UART_0, 25, 16);
		UART_put_string(UART_0, g_array_guardado_3);
		fichas_mover_cursor(UART_0, 25, 22);
		UART_put_string(UART_0, g_array_guardado_4);
		fichas_mover_cursor(UART_0, 25, 28);
		UART_put_string(UART_0, g_array_guardado_5);
		fichas_mover_cursor(UART_0, 25, 34);
		UART_put_string(UART_0, g_array_guardado_6);
		fichas_mover_cursor(UART_0, 25, 40);
		UART_put_string(UART_0, g_array_guardado_7);

		fichas_mover_cursor(UART_0, 25, 46);
		UART_put_string(UART_0, g_array_regresar);

		fichas_mover_cursor(UART_0, 10, 16);
		fichas_seleccion_print(UART_0, rojo);


		UART_put_string(UART_4, g_array_clear);
		fichas_mover_cursor(UART_4, 10, 10);
		UART_put_string(UART_4, g_array_repeticion_1);
		fichas_mover_cursor(UART_4, 25, 16);
		UART_put_string(UART_4, g_array_guardado_3);
		fichas_mover_cursor(UART_4, 25, 22);
		UART_put_string(UART_4, g_array_guardado_4);
		fichas_mover_cursor(UART_4, 25, 28);
		UART_put_string(UART_4, g_array_guardado_5);
		fichas_mover_cursor(UART_4, 25, 34);
		UART_put_string(UART_4, g_array_guardado_6);
		fichas_mover_cursor(UART_4, 25, 40);
		UART_put_string(UART_4, g_array_guardado_7);

		fichas_mover_cursor(UART_4, 25, 46);
		UART_put_string(UART_4, g_array_regresar);

		fichas_mover_cursor(UART_4, 10, 16);
		fichas_seleccion_print(UART_4, rojo);

		coor_y = 16;
		*modo = 1;
	case 1:  		//espera a que se seleccione una opción
		if((FALSE != g_buttons_control_1[DOWN]) | (FALSE != g_buttons_control_2[DOWN]))
		{
			fichas_mover_cursor(UART_0, 10, coor_y);
			fichas_seleccion_print(UART_0, cyan);
			fichas_mover_cursor(UART_4, 10, coor_y);
			fichas_seleccion_print(UART_4, cyan);

			if(46 == coor_y)
			{
				coor_y = 16;
			}
			else
			{
				coor_y += 6;
			}

			fichas_mover_cursor(UART_0, 10, coor_y);
			fichas_seleccion_print(UART_0, rojo);

			fichas_mover_cursor(UART_4, 10, coor_y);
			fichas_seleccion_print(UART_4, rojo);

			g_buttons_control_1[DOWN] = FALSE;
			g_buttons_control_2[DOWN] = FALSE;
		}
		else if((FALSE != g_buttons_control_1[UP]) | (FALSE != g_buttons_control_2[UP]))
		{
			fichas_mover_cursor(UART_0, 10, coor_y);
			fichas_seleccion_print(UART_0, cyan);
			fichas_mover_cursor(UART_4, 10, coor_y);
			fichas_seleccion_print(UART_4, cyan);

			if(16 == coor_y)
			{
				coor_y = 46;
			}
			else
			{
				coor_y -= 6;
			}

			fichas_mover_cursor(UART_0, 10, coor_y);
			fichas_seleccion_print(UART_0, rojo);
			fichas_mover_cursor(UART_4, 10, coor_y);
			fichas_seleccion_print(UART_4, rojo);
			g_buttons_control_1[UP] = FALSE;
			g_buttons_control_2[UP] = FALSE;
		}
		else if((FALSE != g_buttons_control_1[A]) | (FALSE != g_buttons_control_2[A]))
		{
			coor_y = (coor_y - 16) / 5;
			if(5 > coor_y)
			{
				g_log = coor_y;
				tablero_assign_log_number(coor_y);
				control_nintendo_clear(g_buttons_control_1);
				control_nintendo_clear(g_buttons_control_2);
				*modo = 0;
				g_ventana = v_repeticion;
			}
			else
			{
				control_nintendo_clear(g_buttons_control_1);
				control_nintendo_clear(g_buttons_control_2);
				fichas_color(UART_0, azul);
				fichas_color(UART_4, azul);
				*modo = 0;
				g_ventana = v_inicio;
			}
		}
		break;
	}
}

void ajedrez_v_repeticion(uint8_t * modo)
{

	switch(*modo)
	{
	case 0:
		UART_put_string(UART_0, g_array_clear);
		UART_put_string(UART_4, g_array_clear);
		tablero_repeticion_init(g_log+1);
		tablero_init();
		*modo = 1;
	case 1:
		if ((FALSE != g_buttons_control_1[A]) | (FALSE != g_buttons_control_2[A]))
		{
			control_nintendo_clear(g_buttons_control_1);
			control_nintendo_clear(g_buttons_control_2);
			tablero_avanza_movimiento();
		}else if ((FALSE != g_buttons_control_1[B]) | (FALSE != g_buttons_control_2[B]))
		{
			control_nintendo_clear(g_buttons_control_1);
			control_nintendo_clear(g_buttons_control_2);
			tablero_retrocede_movimiento();
		}else if ((FALSE != g_buttons_control_1[SELECT]) | (FALSE != g_buttons_control_2[SELECT]))
		{
			control_nintendo_clear(g_buttons_control_1);
			control_nintendo_clear(g_buttons_control_2);
			g_ventana = v_leer;
			*modo = 0;
			fichas_color(UART_0, azul);
			fichas_color(UART_4, azul);
		}
		break;

	}
}
