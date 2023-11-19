#include <temporizador.h>
#include "numeros.h"
#include "PIT.h"
#include "NVIC.h"

static uint8_t g_temporizador_posicion[] = {'\e','[','0','0',';','0','0','0','H','\0'};

static uint8_t g_array_color_black[] = "\033[30m";

static uint8_t g_tiempo_restante_minutos[2] = {0, 0};
static uint8_t g_tiempo_restante_segundos[2] = {0, 0};
static uint8_t g_timer_flag = 0;
static uint8_t g_turno = 0;

static uint8_t renglon_index = 0;
static uint8_t fila_index = 0;
static uint8_t temp = 0;


void PIT_set_flag_timer(uint8_t pit)
{
	g_timer_flag++;
}

void temporizador_puntos_print(void)
{
	temporizador_mover_cursor(UART_0, 18, 4);
	UART_put_char(UART_0, 219);
	UART_put_char(UART_0, 219);
	temporizador_mover_cursor(UART_0, 18, 7);
	UART_put_char(UART_0, 219);
	UART_put_char(UART_0, 219);

}

void temporizador_init(uint8_t minuto_inicial, uint8_t segundo_inicial)
{
	g_tiempo_restante_minutos[0] = minuto_inicial;
	g_tiempo_restante_minutos[1] = minuto_inicial;
	g_tiempo_restante_segundos[0] = segundo_inicial;
	g_tiempo_restante_segundos[1] = segundo_inicial;

	PIT_enable();
	PIT_set_time(PIT_CH2, TIEMPO_CH2);
	PIT_enable_channel_interrupt(PIT_CH2);
	PIT_callback_init(channel_2, PIT_set_flag_timer);
	PIT_start_channel(PIT_CH2);

	NVIC_enable_interrupt_and_priotity(PIT_CH2_IRQ, PRIORITY_3);

	UART_put_string(UART_0, g_array_color_black);
	temporizador_puntos_print();
	temporizador_update();


}


void temporizador_update(void)
{
	static uint8_t time_over = 0;
	static uint8_t uart = 0;

	if (FALSE != g_timer_flag)
	{
		g_tiempo_restante_segundos[g_turno]-= g_timer_flag;
		g_timer_flag = 0;

		if (60 < g_tiempo_restante_segundos[g_turno])
		{
			g_tiempo_restante_segundos[g_turno] = 59;
			g_tiempo_restante_minutos[g_turno]--;

			if (0 > g_tiempo_restante_minutos[g_turno])
			{
				time_over = 1;
			}

		}

		uart = (g_turno == 0)? UART_0 : UART_4;
		temporizador_new_time_print(uart);

	}

}

void temporizador_new_time_print(UART_channel_t UART_name)
{
	static uint8_t numero_temporal = 0;
	static uint8_t data = 0;

	data = g_tiempo_restante_minutos[g_turno];

	numero_temporal = (data - (data % 10)) / 10;

	temporizador_numero_print(UART_name, 0, numero_temporal);
	temporizador_numero_print(UART_name, 9, data % 10);

	data = g_tiempo_restante_segundos[g_turno];
	numero_temporal = (data - (data % 10)) / 10;

	temporizador_numero_print(UART_name, 20, numero_temporal);
	temporizador_numero_print(UART_name, 29, data % 10);

}

void temporizador_numero_print(UART_channel_t UART_name, uint8_t posicion, uint8_t numero)
{
	uint8_t *array_num;

	switch (numero)
	{
	case 0:
		array_num = &array_cero[0][0];
	break;
	case 1:
		array_num = &array_uno[0][0];
	break;
	case 2:
		array_num = &array_dos[0][0];
	break;
	case 3:
		array_num = &array_tres[0][0];
	break;
	case 4:
		array_num = &array_cuatro[0][0];
	break;
	case 5:
		array_num = &array_cinco[0][0];
	break;
	case 6:
		array_num = &array_seis[0][0];
	break;
	case 7:
		array_num = &array_siete[0][0];
	break;
	case 8:
		array_num = &array_ocho[0][0];
	break;
	case 9:
		array_num = &array_nueve[0][0];
	break;
	default:
		array_num = &array_cero[0][0];
	break;
	}

	for (renglon_index = 0; renglon_index < 7; renglon_index++)
	{
		temporizador_mover_cursor(UART_name, posicion, renglon_index+2);
		for (fila_index = 0; fila_index < 9; fila_index++)
		{
			temp = *(array_num+(renglon_index*9)+(fila_index));
			temp = (temp == 35)? 219U : temp;
			UART_put_char(UART_name, temp);
		}
	}
}

void temporizador_mover_cursor(UART_channel_t UART_name, uint8_t posicion, uint8_t renglon)
{
	uint8_t recorrimiento_total = 0;

	recorrimiento_total = 207 + posicion;
	g_temporizador_posicion[5] = NUM_TO_ASCII(recorrimiento_total / 100);

	recorrimiento_total = recorrimiento_total % 100;
	g_temporizador_posicion[6] = NUM_TO_ASCII(recorrimiento_total / 10);

	recorrimiento_total = recorrimiento_total % 10;
	g_temporizador_posicion[7] = NUM_TO_ASCII(recorrimiento_total);

	g_temporizador_posicion[2] = NUM_TO_ASCII(0);
	g_temporizador_posicion[3] = NUM_TO_ASCII(renglon);
	UART_put_string(UART_name, g_temporizador_posicion);
}
