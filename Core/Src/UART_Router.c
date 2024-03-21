#include "main.h"
#include "UART_Router.h"
#include "BMP280.h"
#include "AHT10.h"

extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_tx;

void Router_UART_Transmit_DMA(const uint8_t *pData, uint16_t Size)
{
	HAL_UART_Transmit_DMA(&huart2, pData, Size);
	return;
}

void Router_CommandHandler()
{
	switch((char)Router.RxBuff[0])
	{
		case ROUTER_CMD_GET_PRESSURE:
			sprintf(Router.MainBuff, "PRESSURE:%d\n", (int)(BMP280_ReadPressure()*0.0075));
			break;
		case ROUTER_CMD_GET_HUMIDITY:
			sprintf(Router.MainBuff, "HUMIDITY:%0.1f\n", AHT10_DataStruct.Humidity);
			break;
		case ROUTER_CMD_GET_TEMPERATURE:
			sprintf(Router.MainBuff, "TEMPERATURE:%0.1f\n", AHT10_DataStruct.Temperature);
			break;
		case ROUTER_CMD_GET_DEVICE_ID:
			sprintf(Router.MainBuff, "DEVICE_ID:%s\n", DEVICE_ID);
			break;
	}

	Router_UART_Transmit_DMA((uint8_t*)Router.MainBuff, strlen(Router.MainBuff));
	return;
}
