/*
 * Bluetooth.h
 *
 *  Created on: 5 April 2024
 *      Author: Eren
 */
#include "Bluetooth.h"
#define BUFFER_SIZE 8

UART_HandleTypeDef* USARTX;

char rx_buff[BUFFER_SIZE];
char tx_buff[50];

int count = 0;

void Bluetooth_Init(UART_HandleTypeDef* usartx)
{
	USARTX = usartx;
	__HAL_UART_ENABLE_IT(USARTX, UART_IT_RXNE);
}
void Bluetooth_Write_String(char *data)
{
	char trash_data = 0xff;
	HAL_UART_Transmit(USARTX, (uint8_t*)trash_data, 1, 100);

	//Real Data
	HAL_UART_Transmit(USARTX, (uint8_t*)tx_buff, sprintf(tx_buff, data), 100);
}
void Bluetooth_Write(char *data)
{
	char trash_data = 0xff;
	HAL_UART_Transmit(USARTX, (uint8_t*)trash_data, 1, 100);

	//Real Data
	HAL_UART_Transmit(USARTX, (uint8_t*)data, sizeof(data), 100);
}
void Bluetooth_Read()
{
	HAL_UART_Receive_IT(USARTX, (uint8_t *)rx_buff, sizeof(rx_buff));
	count++;
}
int Bluetooth_Check_Data(char *data)
{
	if (rx_buff[0] == 0) return 0;
	int i = 0;
	for(i=0;i<strlen(data);i++)
	{
		if(data[i] != rx_buff[i])
		{
			return 0;
		}
	}
	for(i=0;i<strlen(data);i++)
	{
		rx_buff[i]=0;
	}
	return 1;
}
