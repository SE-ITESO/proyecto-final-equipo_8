#include <temporizador.h>

static uint8_t tiempo_restante[2] = {0, 0};
static uint8_t g_temporizador_posicion[] = {'\e','[','0','0',';','0','0','0','H','\0'};

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
	UART_put_string(UART_name, g_temporizador_posicion);
}

void temporizador_cero_UART()
{
	/*Nivel 1*/
	UART_put_string(UART_0, "xdxdxdxd");

}


void temporizador_cero_print(uint16_t posicion)
{
	temporizador_mover_cursor(UART_0, posicion);
	temporizador_cero_UART(UART_0);
}

void temporizador_init(uint8_t tiempo_inicial)
{
	tiempo_restante[0] = tiempo_inicial;
	tiempo_restante[1] = tiempo_inicial;

	temporizador_cero_print(0);
}
