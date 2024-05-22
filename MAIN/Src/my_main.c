#include "my_main.h"
#include "Bluetooth.h"
#include "BASIC.h"
#include "REG595.h"

uint8_t REGISTER;
uint16_t level_value[3];
int level_count;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &MY_USART)
	{
		Get_Bluetooth();
		Bluetooth_Read();
	}
}
void Read_Level()
{
	HAL_ADC_Start(&MY_ADC);
	if(HAL_ADC_PollForConversion(&MY_ADC, 1000) == HAL_OK)
	{
		level_value[level_count] = HAL_ADC_GetValue(&MY_ADC);
		level_count++;
		if(level_count==3)
			level_count=0;
	}
	HAL_ADC_Stop(&MY_ADC);

	/*
	 * TO DO : The level_value of the value will be checked.
	 * */
	/*
	value-=12;
	value/=10;
	value/=1.9;
	if(value > 100)
		value = 100;
	*/
}
void Update_REG595(uint8_t data)
{
	REG595_setData(data);
	REG595_Write();
}
void Get_Bluetooth()
{
	if(Bluetooth_Check_Data("led1 onn"))
	{
		REGISTER &= ~(1 << 0);
	}
	else if(Bluetooth_Check_Data("led1 off"))
	{
		REGISTER |= (1 << 0);
	}
	else if(Bluetooth_Check_Data("led2 onn"))
	{
		REGISTER &= ~(1 << 1);
	}
	else if(Bluetooth_Check_Data("led2 off"))
	{
		REGISTER |= (1 << 1);
	}
	else if(Bluetooth_Check_Data("led3 onn"))
	{
		REGISTER &= ~(1 << 2);
	}
	else if(Bluetooth_Check_Data("led3 off"))
	{
		REGISTER |= (1 << 2);
	}
	else if(Bluetooth_Check_Data("led4 onn"))
	{
		REGISTER &= ~(1 << 3);
	}
	else if(Bluetooth_Check_Data("led4 off"))
	{
		REGISTER |= (1 << 3);
	}
	else if(Bluetooth_Check_Data("data led"))
	{
		char datam[3];
		datam[0] = 'W';
		datam[1] = 0xff - REGISTER;
		datam[2] = 0x0f;           			//->The level sensor value will come here
		Bluetooth_Write(datam);
	}
	Update_REG595(REGISTER);
}
void MAIN()
{
	////////--> 74HC595 CODE <--////////
	REG595_Init(REG_Port, REG_CLK_Pin, REG_Port, REG_LATCH_Pin, REG_Port, REG_DATA_Pin);
	REGISTER = 0xff;
	Update_REG595(REGISTER);
	////////--> BLUETOOTH CODE <--////////
	Bluetooth_Init(&MY_USART);
	int is_ready = 0;
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == 0)
		is_ready = 1;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	Bluetooth_Read();
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == 1 && is_ready == 1)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		}
		Read_Level();
		HAL_Delay(100);
	}
}

void Blink()
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_Delay(100);
}

