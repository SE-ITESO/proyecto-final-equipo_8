#include <temporizador.h>

static uint8_t tiempo_restante[2] = {0, 0};

void temporizador_init(uint8 tiempo_inicial)
{
	tiempo_restante[0] = tiempo_inicial;
	tiempo_restante[1] = tiempo_inicial;
}

void temporizador_cero_print(uint16_t posicion)
{
	temporizador_mover_cursor(UART_0, posicion);
	temporizador_cero_UART(UART_0);
}

void temporizador_mover_cursor(UART_channel_t UART_name, uint8_t posicion)
{
	uint8_t recorrimiento_total = 0;

	recorrimiento_total = 176 + (posicion * 16);
	g_temporizador_posicion[5] = NUM_TO_ASCII(recorrimiento_total / 100);

	recorrimiento_total = recorrimiento_total % 100;
	g_temporizador_posicion[6] = NUM_TO_ASCII(recorrimiento_total / 10);

	recorrimiento_total = recorrimiento_total % 10;
	g_temporizador_posicion[7] = NUM_TO_ASCII(recorrimiento_total);

	g_temporizador_posicion[2] = NUM_TO_ASCII(0);
	g_temporizador_posicion[3] = NUM_TO_ASCII(1);
	UART_put_string(UART_name, g_posicion);
}

void temporizador_cero_UART(UART_0)
{
	uint8_t i = 0;

	/*Nivel 1*/
	UART_put_char(UART_name, DOWN_LLENO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, DOWN_LLENO);
	g_salto[6] = '4';
	UART_put_string(UART_name, g_salto);

	/*Nivel 2*/
	UART_put_char(UART_name, UP_LLENO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, LLENO);
	UART_put_char(UART_name, UP_LLENO);
	g_salto[6] = '4';
	UART_put_string(UART_name, g_salto);

	/*Nivel 3*/
	for(i = 0; i < 4; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '5';
	UART_put_string(UART_name, g_salto);

	/*Nivel 4*/
	for(i = 0; i < 6; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '7';
	UART_put_string(UART_name, g_salto);

	/*Nivel 5*/
	for(i = 0; i < 8; i++)
	{
		UART_put_char(UART_name, LLENO);
	}
	g_salto[6] = '8';
	UART_put_string(UART_name, g_salto);
}
