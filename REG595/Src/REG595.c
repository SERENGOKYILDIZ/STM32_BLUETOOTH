/*
 * REG595.c
 *
 *  Created on: May 5, 2023
 *      Author: EREN
 */

#include "REG595.h"

GPIO_TypeDef *PORT_CLK;
GPIO_TypeDef *PORT_LATCH;
GPIO_TypeDef *PORT_DATA;

uint16_t PIN_CLK;
uint16_t PIN_LATCH;
uint16_t PIN_DATA;

char myData;

void REG595_Init(GPIO_TypeDef *CLK_p, uint16_t CLK, GPIO_TypeDef *LATCH_p, uint16_t LATCH, GPIO_TypeDef *DATA_p, uint16_t DATA)
{
	PORT_CLK = CLK_p;
	PORT_LATCH = LATCH_p;
	PORT_DATA = DATA_p;

	PIN_CLK = CLK;
	PIN_LATCH = LATCH;
	PIN_DATA = DATA;
}
uint8_t REG595_bitRead(uint8_t num, uint8_t adr)
{
	return (num & (1<<adr))>>adr;
}
char REG595_getData()
{
	return myData;
}
void REG595_setData(char var)
{
	myData=var;
}
void REG595_Write()
{
	BASIC_pinLow(PORT_LATCH, PIN_LATCH);
	for(int i=7;i>=0;i--)
	{
		BASIC_pinWrite(PORT_DATA, PIN_DATA, REG595_bitRead(myData, i));
		BASIC_pinClock(PORT_CLK, PIN_CLK);
	}
	BASIC_pinHigh(PORT_LATCH, PIN_LATCH);
}

