#include "GY-53.h"
uint8_t Buffer[8];
uint8_t RxBuffer[8];
uint8_t aRxBuffer;
uint8_t Receive_ok = 0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	static uint8_t count = 0;
	RxBuffer[count++] = aRxBuffer;
	if (count == 1)
	{
		if (RxBuffer[0] != 0X5A)
		{
			count = 0;
			HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer, 1); //再开启接收中断
			return;
		}
	}
	if (count == 2)
	{
		if (RxBuffer[1] != 0X5A)
		{
			count = 0;
			HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer, 1); //再开启接收中断
			return;
		}
	}
	if (count > 3)
	{
		if (count != RxBuffer[3] + 5)
		{
			HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer, 1); //再开启接收中断
			return;
		}
		if ((RxBuffer[2] == 0x15) && (Receive_ok == 0))
		{
			Receive_ok = 1;
			count = 0;
			memcpy(Buffer,RxBuffer,8);//拷贝接收到的数据
			memset(RxBuffer, 0x00, sizeof(RxBuffer)); //清空数组
		}
	}
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer, 1); //再开启接收中断
}
int16_t filter(int16_t num)
{
	static int16_t buf[5];
    static uint8_t i;
    uint8_t count;
    int32_t sum = 0;
	buf[i++] = num;
	if (i == 5)
	{
		i = 0;
	}
	for (count = 0;count<5;count++)
	{
		sum +=buf[count]; 
	}
	return (int16_t)(sum/5);
}