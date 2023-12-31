/**
 * @file tablero.c
 *
 * @Authors Leonardo Arechiga
 * 			Brandon Gutiérrez
 *
 * 	@brief  It controls the operation
 * 			of the board in the game
 *
 */

#include "tablero.h"

static uint8_t g_modo = 1;

static struct_ficha_t g_ficha_generica =
{
		indefinido,
		fichas_vacio_print,
		ninguno,
		FALSE
};

static funct_mov_ficha g_funct_movimiento[] =
{
		fichas_peon_mov,
		fichas_torre_mov,
		fichas_alfil_mov,
		fichas_caballo_mov,
		fichas_reina_mov,
		fichas_rey_mov
};

static uint8_t g_array_clear[] = "\033[2J";

static uint8_t g_array_reina[] =
		// R    E   I    N    A
		"----- --- --- -   - ---"
		"\e[1B\e[23D"
		" -  - -    -  --  - - -"
		"\e[1B\e[23D"
		" ---- ---  -  - - - ---"
		"\e[1B\e[23D"
		" - -  -    -  -  -- - -"
		"\e[1B\e[23D"
		" -  - --- --- -   - - -";

static uint8_t g_array_torre[] =
		// T    O     R     R    E
		"----- ---- ----- ----- ---"
		"\e[1B\e[26D"
		"  -   -  -  -  -  -  - -  "
		"\e[1B\e[26D"
		"  -   -  -  ----  ---- ---"
		"\e[1B\e[26D"
		"  -   -  -  - -   - -  -  "
		"\e[1B\e[26D"
		"  -   ----  -  -  -  - ---";

static uint8_t g_array_alfil[] =
		//A   L   F   I   L
		"--- -   --- --- -  "
		"\e[1B\e[19D"
		"- - -   -    -  -  "
		"\e[1B\e[19D"
		"--- -   ---  -  -  "
		"\e[1B\e[19D"
		"- - -   -    -  -  "
		"\e[1B\e[19D"
		"- - --- -   --- ---";

static uint8_t g_array_caballo[] =
		//c   A    B   A   L   L   O
		"--- --- ---- --- -   -   ----"
		"\e[1B\e[29D"
		"-   - -  - - - - -   -   -  -"
		"\e[1B\e[29D"
		"-   ---  --- --- -   -   -  -"
		"\e[1B\e[29D"
		"-   - -  - - - - -   -   -  -"
		"\e[1B\e[29D"
		"--- - - ---- - - --- --- ----";

static uint8_t g_posicion_reyes[2][2] = {{4, 7},{4, 0}};

static struct_ficha_t g_array_ajedrez[64];

static uint8_t log_number = 0;

static uint8_t g_posible_roque[2][2] = {{TRUE, TRUE}, {TRUE, TRUE}};


void tablero_assign_log_number(uint8_t number)
{
	log_number = number;
}

void tablero_switch_string(uint8_t* array, uint8_t old_character, uint8_t new_character)
{
	int i = 0;
	while(0 != *(array + i)){
		if(old_character == (*(array + i)))
		{
			*(array + i) = new_character;
		}
		i++;
	}
}

void tablero_init(void)
{
	fichas_color(UART_0, azul);
	fichas_color(UART_4, azul);
	tablero_switch_string(g_array_reina, '-', 219);
	tablero_switch_string(g_array_torre, '-', 219);
	tablero_switch_string(g_array_alfil, '-', 219);
	tablero_switch_string(g_array_caballo, '-', 219);
	uint8_t i;
	uint8_t l;
	uint16_t temp_x;
	uint8_t temp_y;
	for(l = 0; l < 8; l++)
	{
		temp_y = (l * 8) + 1;
		for(i = 0; i < 4; i++)
		{
			temp_x = (((l + 1) % 2) * 16) + (i * 32) + 1;
			fichas_vacio_print(ninguno, temp_x, temp_y);
		}
	}

	alarma_init();
	tablero_acomodo_arreglo();
	tablero_print_fichas();

	g_posible_roque[0][0] = TRUE;
	g_posible_roque[0][1] = TRUE;
	g_posible_roque[1][0] = TRUE;
	g_posible_roque[1][1] = TRUE;
}

void tablero_acomodo_arreglo(void)
{
	uint8_t i;

	fichas_config(&g_ficha_generica, ninguno, indefinido);
	for(i = 0; i < 64; i++)
	{
		g_array_ajedrez[i] = g_ficha_generica;
	}

	/*Posición de negras*/
	fichas_config(&g_ficha_generica, peon, negras);
	for(i = 0; i < 8; i++)
	{
		g_array_ajedrez[i + 8] = g_ficha_generica;
	}
	fichas_config(&g_ficha_generica, reina, negras);
	g_array_ajedrez[3] = g_ficha_generica;

	fichas_config(&g_ficha_generica, alfil, negras);
	g_array_ajedrez[2] = g_ficha_generica;
	g_array_ajedrez[5] = g_ficha_generica;

	fichas_config(&g_ficha_generica, torre, negras);
	g_array_ajedrez[0] = g_ficha_generica;
	g_array_ajedrez[7] = g_ficha_generica;

	fichas_config(&g_ficha_generica, caballo, negras);
	g_array_ajedrez[1] = g_ficha_generica;
	g_array_ajedrez[6] = g_ficha_generica;

	fichas_config(&g_ficha_generica, rey, negras);
	g_array_ajedrez[4] = g_ficha_generica;

	/*Posición de blancas*/
	fichas_config(&g_ficha_generica, peon, blancas);
	for(i = 0; i < 8; i++)
	{
		g_array_ajedrez[i + 48] = g_ficha_generica;
	}

	fichas_config(&g_ficha_generica, reina, blancas);
	g_array_ajedrez[3 + 56] = g_ficha_generica;

	fichas_config(&g_ficha_generica, alfil, blancas);
	g_array_ajedrez[2 + 56] = g_ficha_generica;
	g_array_ajedrez[5 + 56] = g_ficha_generica;

	fichas_config(&g_ficha_generica, torre, blancas);
	g_array_ajedrez[0 + 56] = g_ficha_generica;
	g_array_ajedrez[7 + 56] = g_ficha_generica;

	fichas_config(&g_ficha_generica, caballo, blancas);
	g_array_ajedrez[1 + 56] = g_ficha_generica;
	g_array_ajedrez[6 + 56] = g_ficha_generica;

	fichas_config(&g_ficha_generica, rey, blancas);
	g_array_ajedrez[4 + 56] = g_ficha_generica;
}

void tablero_print_fichas(void)
{
	uint8_t i = 0;
	uint16_t coordenada_x = 0;
	uint8_t coordenada_y = 0;
	/*Impresión de fichas negras*/
	for(i = 0; i < 16; i++)
	{
		coordenada_x = ((i % 8) * 16) + 1;
		coordenada_y = ((i / 8) * 8) + 1;
		g_array_ajedrez[i].print_ficha(g_array_ajedrez[i].color, coordenada_x, coordenada_y);
	}

	/*Impresión de fichas blancas*/
	for(i = 0; i < 16; i++)
	{
		coordenada_x = (((i + 48) % 8) * 16) + 1;
		coordenada_y = (((i + 48) / 8) * 8) + 1;
		g_array_ajedrez[i + 48].print_ficha(g_array_ajedrez[i + 48].color, coordenada_x, coordenada_y);
	}
}

uint8_t tablero_control(uint8_t* jugador, uint8_t* array_button, uint8_t* reinicio)
{
	static uint8_t coordenada_x = 0;
	static uint8_t coordenada_y = 7;
	static struct_ficha_t ficha;
	static struct_ficha_t ficha_seleccionada;
	static struct_ficha_t ficha_temporal;
	struct_ficha_jaque_t ficha_jaque;
	static uint8_t x_selec = 0;
	static uint8_t y_selec = 0;
	uint8_t temporal;
	uint8_t status = s_none_t;
	static uint8_t y_aux;
	static uint8_t s_jaque;

	if(TRUE == *reinicio)
	{
		coordenada_x = 0;
		coordenada_y = 7;
		*reinicio = FALSE;
		g_modo = 1;
		s_jaque = libre;
	}

	s_jaque = fichas_jaque_sencillo(*jugador, g_posicion_reyes[*jugador][0] , g_posicion_reyes[*jugador][1], g_array_ajedrez);

	if(jaque == s_jaque)
	{
		alarma_sonido();
		s_jaque = fichas_jaque_mate(*jugador, g_posicion_reyes[*jugador][0] , g_posicion_reyes[*jugador][1], g_array_ajedrez);
		if(jaque_mate == s_jaque)
		{
			fichas_ficha_jaque(&ficha_jaque, g_posicion_reyes[*jugador][0], g_posicion_reyes[*jugador][1], g_array_ajedrez);
			s_jaque =  fichas_salvar_jaque(&ficha_jaque, g_posicion_reyes[*jugador][0], g_posicion_reyes[*jugador][1], g_array_ajedrez);
			if(jaque_mate == s_jaque)
			{
				g_modo = 6;
			}
		}
	}

	switch(g_modo)
	{
	case 0:
		if(FALSE != *(array_button + RIGHT))
		{
			*(array_button + RIGHT) = FALSE;

			fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			temporal = (coordenada_x + coordenada_y) % 2;
			if(0 == temporal)
			{
				fichas_vacio_UART((*jugador) * 4, VACIO);
			}
			else
			{
				fichas_color((*jugador) * 4, azul);
				fichas_vacio_UART((*jugador) * 4, LLENO);
			}
			if(ninguno != ficha.ficha_name)
			{
				if(0 == *jugador)
				{
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
				}
			}
			if(7 == coordenada_x)
			{
				coordenada_x = 0;
			}
			else
			{
				coordenada_x ++;
			}
			g_modo = 1;
		}
		else if(FALSE != *(array_button + LEFT))
		{
			*(array_button + LEFT) = FALSE;

			fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			temporal = (coordenada_x + coordenada_y) % 2;
			if(0 == temporal)
			{
				fichas_vacio_UART((*jugador) * 4, VACIO);
			}
			else
			{
				fichas_color((*jugador) * 4, azul);
				fichas_vacio_UART((*jugador) * 4, LLENO);
			}
			if(ninguno != ficha.ficha_name)
			{
				if(0 == *jugador)
				{
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
				}
			}
			if(0 == coordenada_x)
			{
				coordenada_x = 7;
			}
			else
			{
				coordenada_x --;
			}
			g_modo = 1;
		}
		else if(FALSE != *(array_button + UP))
		{
			*(array_button + UP) = FALSE;

			fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			temporal = (coordenada_x + coordenada_y) % 2;
			if(0 == temporal)
			{
				fichas_vacio_UART((*jugador) * 4, VACIO);
			}
			else
			{
				fichas_color((*jugador) * 4, azul);
				fichas_vacio_UART((*jugador) * 4, LLENO);
			}
			if(ninguno != ficha.ficha_name)
			{
				if(0 == *jugador)
				{
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
				}
			}
			if(0 == coordenada_y)
			{
				coordenada_y = 7;
			}
			else
			{
				coordenada_y --;
			}
			g_modo = 1;
		}
		else if(FALSE != *(array_button + DOWN))
		{
			*(array_button + DOWN) = FALSE;

			fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			temporal = (coordenada_x + coordenada_y) % 2;
			if(0 == temporal)
			{
				fichas_vacio_UART((*jugador) * 4, VACIO);
			}
			else
			{
				fichas_color((*jugador) * 4, azul);
				fichas_vacio_UART((*jugador) * 4, LLENO);
			}
			if(ninguno != ficha.ficha_name)
			{
				if(0 == *jugador)
				{
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
				}
			}
			if(7 == coordenada_y)
			{
				coordenada_y = 0;
			}
			else
			{
				coordenada_y ++;
			}
			g_modo = 1;
		}
		else if(FALSE != *(array_button + A))
		{
			*(array_button + A) = FALSE;

			if(0 == *jugador)
			{
				if(blancas == ficha.color)
				{
					fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
					fichas_vacio_print(indefinido, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
					g_modo = 2;
				}
			}
			else
			{
				if(negras == ficha.color)
				{
					fichas_mover_cursor((*jugador) * 4, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
					fichas_vacio_print(indefinido, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
					g_modo = 2;
				}
			}
		}
		break;

	case 1:
		if(0 == *jugador)
		{
			ficha = *(g_array_ajedrez + coordenada_x + (coordenada_y * MULT_RENGLON));
		}
		else
		{
			ficha = *(g_array_ajedrez + (7 - coordenada_x) + ((7 - coordenada_y) * MULT_RENGLON));
		}
		fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
		fichas_color((*jugador) * 4, verde);
		fichas_vacio_UART((*jugador) * 4, LLENO);
		if(ninguno != ficha.ficha_name)
		{
			if(0 == *jugador)
			{
				ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			}
			else
			{
				ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
			}
		}
		g_modo = 0;
		break;

	case 2:
		if(0 == *jugador)
		{
			g_funct_movimiento[ficha.ficha_name - 1](coordenada_x, coordenada_y, g_array_ajedrez);
			if(rey == ficha.ficha_name)
			{
				if((TRUE == g_posible_roque[*jugador][roque_corto]) & (7 == (coordenada_y)))
				{
					fichas_roque(coordenada_x, coordenada_y, g_array_ajedrez, roque_corto);
				}
				if((TRUE == g_posible_roque[*jugador][roque_largo]) & (7 == (coordenada_y)))
				{
					fichas_roque(coordenada_x, coordenada_y, g_array_ajedrez, roque_largo);
				}
			}
		}
		else
		{
			g_funct_movimiento[ficha.ficha_name - 1](7 - coordenada_x, 7 - coordenada_y, g_array_ajedrez);
			if(rey == ficha.ficha_name)
			{
				if((TRUE == g_posible_roque[*jugador][roque_corto]) & (0 == (7 - coordenada_y)))
				{
					fichas_roque(7 - coordenada_x, 7 - coordenada_y, g_array_ajedrez, roque_corto);
				}
				if((TRUE == g_posible_roque[*jugador][roque_largo]) & (0 == (7 - coordenada_y)))
				{
					fichas_roque(7 - coordenada_x, 7 - coordenada_y, g_array_ajedrez, roque_largo);
				}
			}
		}

		if(0 == *jugador)
		{
			ficha = *(g_array_ajedrez + coordenada_x + (coordenada_y * MULT_RENGLON));
			ficha_seleccionada = *(g_array_ajedrez + coordenada_x + (coordenada_y * MULT_RENGLON));
		}
		else
		{
			ficha = *(g_array_ajedrez + (7 - coordenada_x) + ((7 - coordenada_y) * MULT_RENGLON));
			ficha_seleccionada = *(g_array_ajedrez + (7 - coordenada_x) + ((7 - coordenada_y) * MULT_RENGLON));
		}

		x_selec = coordenada_x;
		y_selec = coordenada_y;
		fichas_mostrar_opciones(&(ficha_seleccionada.opciones), *jugador, g_array_ajedrez);
		if(0 != ficha_seleccionada.opciones.number_opciones)
		{
			fichas_color((*jugador) * 4, rojo);
			g_modo = 3;
		}
		else
		{
			g_modo = 1;
		}
		break;

	case 3:
		if(FALSE != *(array_button + RIGHT))
		{
			*(array_button + RIGHT) = FALSE;

			fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			temporal = (coordenada_x + coordenada_y) % 2;
			if(0 == temporal)
			{
				fichas_vacio_UART((*jugador) * 4, VACIO);
			}
			else
			{
				fichas_color((*jugador) * 4, azul);
				fichas_vacio_UART((*jugador) * 4, LLENO);
			}
			/*Opcion para imprimir el color previo*/
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(ficha.posible_mov)
			{
				fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				fichas_print_opcion((*jugador) * 4);
			}
			if(ninguno != ficha.ficha_name)
			{
				if(0 == *jugador)
				{
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
				}
			}
			if(7 == coordenada_x)
			{
				coordenada_x = 0;
			}
			else
			{
				coordenada_x ++;
			}
			g_modo = 4;
		}
		else if(FALSE != *(array_button + LEFT))
		{
			*(array_button + LEFT) = FALSE;

			fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			temporal = (coordenada_x + coordenada_y) % 2;
			if(0 == temporal)
			{
				fichas_vacio_UART((*jugador) * 4, VACIO);
			}
			else
			{
				fichas_color((*jugador) * 4, azul);
				fichas_vacio_UART((*jugador) * 4, LLENO);
			}
			/*Opcion para imprimir el color previo*/
			if(ficha.posible_mov)
			{
				fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				fichas_print_opcion((*jugador) * 4);
			}
			if(ninguno != ficha.ficha_name)
			{
				if(0 == *jugador)
				{
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
				}
			}
			if(0 == coordenada_x)
			{
				coordenada_x = 7;
			}
			else
			{
				coordenada_x --;
			}
			g_modo = 4;
		}
		else if(FALSE != *(array_button + UP))
		{
			*(array_button + UP) = FALSE;

			fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			temporal = (coordenada_x + coordenada_y) % 2;
			if(0 == temporal)
			{
				fichas_vacio_UART((*jugador) * 4, VACIO);
			}
			else
			{
				fichas_color((*jugador) * 4, azul);
				fichas_vacio_UART((*jugador) * 4, LLENO);
			}
			/*Opcion para imprimir el color previo*/
			if(ficha.posible_mov)
			{
				fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				fichas_print_opcion((*jugador) * 4);
			}
			if(ninguno != ficha.ficha_name)
			{
				if(0 == *jugador)
				{
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
				}
			}
			if(0 == coordenada_y)
			{
				coordenada_y = 7;
			}
			else
			{
				coordenada_y --;
			}
			g_modo = 4;
		}
		else if(FALSE != *(array_button + DOWN))
		{
			*(array_button + DOWN) = FALSE;

			fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			temporal = (coordenada_x + coordenada_y) % 2;
			if(0 == temporal)
			{
				fichas_vacio_UART((*jugador) * 4, VACIO);
			}
			else
			{
				fichas_color((*jugador) * 4, azul);
				fichas_vacio_UART((*jugador) * 4, LLENO);
			}
			/*Opcion para imprimir el color previo*/
			if(ficha.posible_mov)
			{
				fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				fichas_print_opcion((*jugador) * 4);
			}
			if(ninguno != ficha.ficha_name)
			{
				if(0 == *jugador)
				{
					ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
				}
			}
			if(7 == coordenada_y)
			{
				coordenada_y = 0;
			}
			else
			{
				coordenada_y ++;
			}
			g_modo = 4;
		}
		else if(FALSE != *(array_button + A))
		{
			*(array_button + A) = FALSE;

			if(ficha.posible_mov)
			{
				if(0 == *jugador)
				{
					fichas_clear_opciones(&((g_array_ajedrez + x_selec + (y_selec * MULT_RENGLON))->opciones), (*jugador) * 4, g_array_ajedrez);
					ficha_temporal =  *(g_array_ajedrez + coordenada_x + (coordenada_y * MULT_RENGLON));
					tablero_movimiento(x_selec, y_selec, coordenada_x, coordenada_y);
				}
				else
				{
					fichas_clear_opciones(&((g_array_ajedrez + (7 - x_selec) + ((7 - y_selec) * MULT_RENGLON))->opciones), (*jugador) * 4, g_array_ajedrez);
					ficha_temporal =  *(g_array_ajedrez + (7 - coordenada_x) + ((7 - coordenada_y) * MULT_RENGLON));
					tablero_movimiento(7 - x_selec, 7 - y_selec, 7 - coordenada_x, 7 - coordenada_y);
				}

				if(rey == ficha_seleccionada.ficha_name)
				{
					if(0 == *jugador)
					{
						g_posicion_reyes[*jugador][0] = coordenada_x;
						g_posicion_reyes[*jugador][1] = coordenada_y;
						if((2 == coordenada_x) & (TRUE == g_posible_roque[*jugador][roque_corto]))
						{
							tablero_movimiento(0, 7, 3, 7);
						}
						else if((6 == coordenada_x) & (TRUE == g_posible_roque[*jugador][roque_largo]))
						{
							tablero_movimiento(7, 7, 5, 7);
						}
					}
					else
					{
						g_posicion_reyes[*jugador][0] = 7 - coordenada_x;
						g_posicion_reyes[*jugador][1] = 7 - coordenada_y;
						if((2 == coordenada_x) & (TRUE == g_posible_roque[*jugador][roque_corto]))
						{
							tablero_movimiento(0, 0, 3, 0);
						}
						else if((6 == coordenada_x) & (TRUE == g_posible_roque[*jugador][roque_largo]))
						{
							tablero_movimiento(7, 0, 5, 0);
						}
					}
				}
				g_modo = 5;
			}

			s_jaque = fichas_jaque_sencillo(*jugador, g_posicion_reyes[*jugador][0] , g_posicion_reyes[*jugador][1], g_array_ajedrez);

			if(jaque == s_jaque)
			{
				if(0 == *jugador)
				{
					tablero_movimiento(coordenada_x, coordenada_y, x_selec, y_selec);
					g_array_ajedrez[coordenada_x + (8 * coordenada_y)] = ficha_temporal;
					ficha_temporal.print_ficha(ficha_temporal.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
				}
				else
				{
					tablero_movimiento(7 - coordenada_x, 7 - coordenada_y, 7 - x_selec, 7 - y_selec);
					g_array_ajedrez[(7 - coordenada_x) + (8 * (7 - coordenada_y))] = ficha_temporal;
					ficha_temporal.print_ficha(ficha_temporal.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);

				}

				if(rey == ficha_seleccionada.ficha_name)
				{
					if(0 == *jugador)
					{
						g_posicion_reyes[*jugador][0] = x_selec;
						g_posicion_reyes[*jugador][1] = y_selec;
					}
					else
					{
						g_posicion_reyes[*jugador][0] = 7 - x_selec;
						g_posicion_reyes[*jugador][1] = 7 - y_selec;
					}

				}
				g_modo = 1;
			}

			if((rey == ficha_seleccionada.ficha_name) & (5 == g_modo))
			{
				g_posible_roque[*jugador][roque_corto] = FALSE;
				g_posible_roque[*jugador][roque_largo] = FALSE;
			}

			if(0 == *jugador)
			{
				if((torre == ficha_seleccionada.ficha_name) & (5 == g_modo) & (0 == x_selec))
				{
					g_posible_roque[*jugador][roque_largo] = FALSE;
				}
				else if((torre == ficha_seleccionada.ficha_name) & (5 == g_modo) & (7 == x_selec))
				{
					g_posible_roque[*jugador][roque_corto] = FALSE;
				}
				else if((peon == ficha_seleccionada.ficha_name) & (0 == coordenada_y))
				{
					g_modo = 7;
				}
			}
			else
			{
				if((torre == ficha_seleccionada.ficha_name) & (5 == g_modo) & (0 == (7 - x_selec)))
				{
					g_posible_roque[*jugador][roque_largo] = FALSE;
				}
				else if((torre == ficha_seleccionada.ficha_name) & (5 == g_modo) & (7 == (7 - x_selec)))
				{
					g_posible_roque[*jugador][roque_corto] = FALSE;
				}
				else if((peon == ficha_seleccionada.ficha_name) & (7 == 7 - coordenada_y))
				{
					g_modo = 7;
				}
			}
		}
		break;

	case 4:
		if(0 == *jugador)
		{
			ficha = *(g_array_ajedrez + coordenada_x + (coordenada_y * MULT_RENGLON));
		}
		else
		{
			ficha = *(g_array_ajedrez + (7 - coordenada_x) + ((7 - coordenada_y) * MULT_RENGLON));
		}

		fichas_mover_cursor((*jugador) * 4, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
		fichas_color((*jugador) * 4, rojo);
		fichas_vacio_UART((*jugador) * 4, LLENO);

		if(ninguno != ficha.ficha_name)
		{
			if(0 == *jugador)
			{
				ficha.print_ficha(ficha.color, (coordenada_x * 16) + 1, (coordenada_y * 8) + 1);
			}
			else
			{
				ficha.print_ficha(ficha.color, ((7 - coordenada_x) * 16) + 1, ((7 - coordenada_y) * 8) + 1);
			}
		}
		g_modo = 3;
		break;

	case 5:
		(*jugador) = 1 - (*jugador);

		g_modo = 1;
		status = s_change_t;
		break;

	case 6:
		status = s_jaque_mate;
		break;
	case 7:
		y_aux = 10;
		UART_put_string((*jugador) * 4, g_array_clear);
		fichas_color((*jugador) * 4, azul);
		fichas_mover_cursor((*jugador) * 4, 25, 10);
		UART_put_string((*jugador) * 4, g_array_reina);
		fichas_mover_cursor((*jugador) * 4, 25, 16);
		UART_put_string((*jugador) * 4, g_array_torre);
		fichas_mover_cursor((*jugador) * 4, 25, 22);
		UART_put_string((*jugador) * 4, g_array_alfil);
		fichas_mover_cursor((*jugador) * 4, 25, 28);
		UART_put_string((*jugador) * 4, g_array_caballo);
		fichas_mover_cursor((*jugador) * 4, 10, y_aux);
		fichas_seleccion_print((*jugador) * 4, rojo);
		g_modo = 8;
	case 8:
		if(FALSE != *(array_button + DOWN))
		{
			fichas_mover_cursor((*jugador) * 4, 10, y_aux);
			fichas_seleccion_print((*jugador) * 4, cyan);
			if(28 == y_aux)
			{
				y_aux = 10;
			}
			else
			{
				y_aux += 6;
			}
			fichas_mover_cursor((*jugador) * 4, 10, y_aux);
			fichas_seleccion_print((*jugador) * 4, rojo);

			*(array_button + DOWN) = FALSE;
		}

		else if(FALSE != *(array_button + UP))
		{
			fichas_mover_cursor((*jugador) * 4, 10, y_aux);
			fichas_seleccion_print((*jugador) * 4, cyan);
			if(10 == y_aux)
			{
				y_aux = 28;
			}
			else
			{
				y_aux -= 6;
			}
			fichas_mover_cursor((*jugador) * 4, 10, y_aux);
			fichas_seleccion_print((*jugador) * 4, rojo);

			*(array_button + UP) = FALSE;
		}

		else if(FALSE != *(array_button + A))
		{
			*(array_button + A) = FALSE;
			y_aux = (y_aux - 10) / 6;
			temporal = ficha_seleccionada.color;

			switch(y_aux)
			{
			case 0:
				fichas_config(&g_ficha_generica, reina, temporal);
				break;
			case 1:
				fichas_config(&g_ficha_generica, torre, temporal);
				break;
			case 2:
				fichas_config(&g_ficha_generica, alfil, temporal);
				break;
			case 3:
				fichas_config(&g_ficha_generica, caballo, temporal);
				break;
			default:
				break;
			}
			if(0 == *jugador)
			{
				g_array_ajedrez[(coordenada_x) + (8 * (coordenada_y))] = g_ficha_generica;
			}
			else
			{
				g_array_ajedrez[(7 - coordenada_x) + (8 * (7 - coordenada_y))] = g_ficha_generica;
			}
			g_modo = 5;
			tablero_print_tablero();
			fichas_color(UART_4, negras);
			fichas_color(UART_0, negras);
			temporizador_timer_encabezados_print();
		}
		break;
	}

	return status;
}

void tablero_movimiento(uint8_t x_old, uint8_t y_old, uint8_t x_new, uint8_t y_new)
{
	struct_ficha_t ficha;

	if (0 != log_number)
	{
		memory_add_movimiento(x_old, y_old, x_new, y_new);
	}

	ficha = *(g_array_ajedrez + x_old + (y_old * MULT_RENGLON));
	*(g_array_ajedrez + x_new + (y_new * MULT_RENGLON)) = ficha;

	fichas_vacio_print(indefinido, (x_new * 16) + 1, (y_new * 8) + 1);
	ficha.print_ficha(ficha.color, (x_new * 16) + 1, (y_new * 8) + 1);

	fichas_config(&ficha, ninguno, indefinido);
	*(g_array_ajedrez + x_old + (y_old * MULT_RENGLON)) = ficha;

	ficha.print_ficha(ficha.color, (x_old * 16) + 1, (y_old * 8) + 1);
}

void tablero_print_tablero(void)
{
	uint8_t x;
	uint8_t y;
	struct_ficha_t ficha;
	for(y = 0; y < 8; y++)
	{
		for(x = 0; x < 8; x++)
		{
			fichas_vacio_print(indefinido, (x * 16) + 1, (y * 8) + 1);
			ficha = *(g_array_ajedrez + x + (y * 8));
			if(ninguno != ficha.ficha_name)
			{
				ficha.print_ficha(ficha.color, (x * 16) + 1, (y * 8) + 1);
			}
		}
	}
}

static uint8_t data_for_log[255] = {0};
static uint8_t size_of_log = 0;
static uint8_t movimientos_log_index = 0;

void tablero_repeticion_init(uint8_t log_number_here)
{
	uint8_t data_correcta = 0;
	uint8_t errores = 0;
	memory_create_log(log_number_here);
	while((0 == data_correcta) && (errores < 10))
	{
		memory_read_log(data_for_log);
		size_of_log = data_for_log[0];
		if(data_for_log[size_of_log + 1] == 0)
		{
			data_correcta = 1;
		}else{
			errores++;
		}
	}
	movimientos_log_index = 1;
}

void tablero_avanza_movimiento()
{
	uint8_t x_origen_a = 0;
	uint8_t y_origen_a = 0;
	uint8_t x_destino_a = 0;
	uint8_t y_destino_a = 0;

	if(movimientos_log_index < size_of_log)
	{
		x_origen_a = (data_for_log[movimientos_log_index] >> 4) & 0x0F;
		y_origen_a = (data_for_log[movimientos_log_index]) & (0x0F);
		x_destino_a = (data_for_log[movimientos_log_index + 1] >> 4) & 0x0F;
		y_destino_a = (data_for_log[movimientos_log_index + 1]) & (0x0F);
		tablero_movimiento(x_origen_a, y_origen_a, x_destino_a, y_destino_a);
		movimientos_log_index += 2;
	}

}

void tablero_retrocede_movimiento()
{
	uint8_t x_origen_r = 0;
	uint8_t y_origen_r = 0;
	uint8_t x_destino_r = 0;
	uint8_t y_destino_r = 0;

	if(movimientos_log_index > 1)
	{
		movimientos_log_index-=2;
		x_destino_r = (data_for_log[movimientos_log_index] >> 4) & 0x0F;
		y_destino_r = (data_for_log[movimientos_log_index]) & (0x0F);
		x_origen_r = (data_for_log[movimientos_log_index + 1] >> 4) & 0x0F;
		y_origen_r = (data_for_log[movimientos_log_index + 1]) & (0x0F);
		tablero_movimiento(x_origen_r, y_origen_r, x_destino_r, y_destino_r);
	}
}


