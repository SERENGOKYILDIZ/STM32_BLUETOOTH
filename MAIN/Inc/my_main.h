#ifndef __MY_MAIN_H_
#define __MY_MAIN_H_

#include <stm32f4xx_hal.h>

////////--> MY EXTERNS <--////////
extern UART_HandleTypeDef huart6;
extern ADC_HandleTypeDef hadc1;
////////////////////////////////////

////////--> MY VARIABLES <--////////
#define REG_CLK_Pin GPIO_PIN_0
#define REG_LATCH_Pin GPIO_PIN_1
#define REG_DATA_Pin GPIO_PIN_2
#define REG_Port GPIOB

#define MY_USART huart6
#define MY_ADC hadc1
////////////////////////////////////

////////--> MY FUNCTIONS <--////////
void Read_Level();
void Update_REG595(uint8_t data);
void Get_Bluetooth();
void MAIN();
void Blink();
////////////////////////////////////

#endif /* __MY_MAIN_H_ */
