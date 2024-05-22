/*
 * BASIC.h
 *
 *  Created on: 5 May 2023
 *      Author: Eren
 */
#ifndef BASIC_H_
#define BASIC_H_

#include <stm32f4xx_hal.h>

uint8_t BASIC_bitRead(uint8_t num, uint8_t adr);
void BASIC_bitWrite(uint8_t *num, uint8_t adr, uint8_t state);
void BASIC_bitToggle(uint8_t *num, uint8_t adr);

void BASIC_limitation(uint32_t *num, uint32_t min, uint32_t max);
void BASIC_limitation_uint8(uint8_t *num, int min, int max);

void BASIC_pinHigh(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void BASIC_pinLow(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void BASIC_pinWrite(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t state);
void BASIC_pinToggle(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
GPIO_PinState BASIC_pinRead(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void BASIC_pinClock(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif /* BASIC_H_ */
