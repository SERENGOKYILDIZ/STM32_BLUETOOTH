/*
 * Bluetooth.h
 *
 *  Created on: 5 April 2024
 *      Author: Eren
 */
#ifndef __BLUETOOTH_H_
#define __BLUETOOTH_H_

#include <stm32f4xx_hal.h>

void Bluetooth_Init(UART_HandleTypeDef* usartx);
void Bluetooth_Write_String(char *data);
void Bluetooth_Write(char *data);
void Bluetooth_Read();
int Bluetooth_Check_Data(char *data);

#endif /* __BLUETOOTH_H_ */
