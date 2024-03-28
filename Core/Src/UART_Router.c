#include "main.h"
#include "ADC_Modules.h"
#include "UART_Router.h"
#include "BMP280.h"
#include "AHT10.h"
#include "FAN.h"
#include "AirPump.h"
#include "IR_Lamp.h"

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
		case ROUTER_CMD_FAN_TOGGLE:
			FAN_TOGGLE;
			FAN_AnswerRequest();
			break;
		case ROUTER_CMD_RKPSS_ADC_VAL:
			sprintf(Router.MainBuff, "RKPSS:%d\n", ADC1_Module.Data[0]);
			break;
		case ROUTER_CMD_WaterLevelSensor_ADC_VAL:
			sprintf(Router.MainBuff, "WaterLevelSensor:%d\n", ADC1_Module.Data[1]);
			break;
		case ROUTER_CMD_AirPump_TOGGLE:
			AIR_PUMP_TOGGLE;
			AirPump_AnswerRequest();
			break;
		case ROUTER_CMD_IR_LAMP_TOGGLE:
			IR_LAMP_TOGGLE;
			IR_Lamp_AnswerRequest();
			break;
	}

	Router_UART_Transmit_DMA((uint8_t*)Router.MainBuff, strlen(Router.MainBuff));
	return;
}
