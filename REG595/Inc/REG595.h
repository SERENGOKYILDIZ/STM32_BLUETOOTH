/*
 * REG595.h
 *
 *  Created on: May 5, 2023
 *      Author: EREN
 */
#ifndef REG595_H_
#define REG595_H_

#include <stm32f4xx_hal.h>
#include "BASIC.h"

void REG595_Init(GPIO_TypeDef *CLK_p, uint16_t CLK, GPIO_TypeDef *LATCH_p, uint16_t LATCH, GPIO_TypeDef *DATA_p, uint16_t DATA);
uint8_t REG595_bitRead(uint8_t num, uint8_t adr);
void REG595_setData(char var);
char REG595_getData();
void REG595_Write();

#endif /* REG595_H_ */
