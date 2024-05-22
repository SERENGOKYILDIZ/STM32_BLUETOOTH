/*
 * BASIC.cpp
 *
 *  Created on: 5 May 2023
 *      Author: EREN
 */

#include <BASIC.h>
//==============================================================//
uint8_t BASIC_bitRead(uint8_t num, uint8_t adr)
{
	return (num & (1<<adr))>>adr;
}
void BASIC_bitWrite(uint8_t *num, uint8_t adr, uint8_t state)
{
	if(state)*num |= (1<<adr);
	else*num &= ~(1<<adr);
}
void BASIC_bitToggle(uint8_t *num, uint8_t adr)
{
	*num ^= (1 << adr);
}
//==============================================================//
void BASIC_limitation(uint32_t *num, uint32_t min, uint32_t max)
{
	if(*num>max)*num=max;
	if(*num<min)*num=min;
}
void BASIC_limitation_uint8(uint8_t *num, int min, int max)
{
	if(*num==0xff)*num=min;
	if(*num>max)*num=max;
	if(*num<min)*num=min;
}
//==============================================================//
void BASIC_pinHigh(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIOx->BSRR = GPIO_Pin;
}
void BASIC_pinLow(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
}
void BASIC_pinWrite(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t state)
{
	if(state)GPIOx->BSRR = GPIO_Pin;
	else GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
}
void BASIC_pinToggle(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	if(BASIC_pinRead(GPIOx, GPIO_Pin) == 0) GPIOx->BSRR = GPIO_Pin;
	else GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
}
GPIO_PinState BASIC_pinRead(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_PinState bitstatus;
	assert_param(IS_GPIO_PIN(GPIO_Pin));
	if((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
		bitstatus = GPIO_PIN_SET;
	else
		bitstatus = GPIO_PIN_RESET;
	return bitstatus;
}
void BASIC_pinClock(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIOx->BSRR = GPIO_Pin;
	GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
}
//==============================================================//
