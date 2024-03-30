#include "AHT10.h"
#include "UART_Router.h"

//------------------------------------------------------------
extern I2C_HandleTypeDef hi2c1;

extern UART_HandleTypeDef huart2;

//------------------------------------------------------------
uint8_t AHT10_TmpHum_Cmd[3] = {0xAC, 0x33, 0x00};
//------------------------------------------------------------

void AHT10_Init()
{
	AHT10_DataStruct.ADC_Raw = 0;
	AHT10_DataStruct.Humidity = 0.00;
	AHT10_DataStruct.Temperature = 0.00;
	AHT10_DataStruct.TriggerTimeCounter = 0;
	AHT10_DataStruct.ReadDataTimerCounter = 0;
	AHT10_TriggerMeasurements();
}

void _AHT10_Error()
{
	sprintf(Router.MainBuff, "AHT10 error resetting...\n");
	HAL_UART_Transmit_IT(&huart2, (uint8_t*)Router.MainBuff, strlen(Router.MainBuff));
}

void _AHT10_Reset()
{
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Master_Transmit_IT(&hi2c1, AHT10_ADDRESS, (uint8_t *) AHT10_RESET_VALUE, 1);
	if(status != HAL_OK) _AHT10_Error();
}

void AHT10_TriggerMeasurements()
{
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Master_Transmit_IT(&hi2c1, AHT10_ADDRESS, (uint8_t *) AHT10_TmpHum_Cmd, 3);

	if(status != HAL_OK) _AHT10_Error();
}

void _AHT10_ReadRaw()
{
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Master_Receive_IT(&hi2c1, AHT10_ADDRESS, (uint8_t *) AHT10_DataStruct.RX_Data, 6);

	if(status != HAL_OK) _AHT10_Error();
}

void _AHT10_RawToHoomanVals()
{
	AHT10_DataStruct.ADC_Raw = (((uint32_t)AHT10_DataStruct.RX_Data[3] & 15) << 16) |
			((uint32_t)AHT10_DataStruct.RX_Data[4] << 8) | AHT10_DataStruct.RX_Data[5];
	AHT10_DataStruct.Temperature = (float)(AHT10_DataStruct.ADC_Raw * 200.00 / 1048576.00) - 50.00;

	AHT10_DataStruct.ADC_Raw = ((uint32_t)AHT10_DataStruct.RX_Data[1] << 12) |
			((uint32_t)AHT10_DataStruct.RX_Data[2] << 4) | (AHT10_DataStruct.RX_Data[3] >> 4);
	AHT10_DataStruct.Humidity = (float)(AHT10_DataStruct.ADC_Raw*100.00/1048576.00);
}

void AHT10_Measure()
{
	  _AHT10_ReadRaw();
	  if(~AHT10_DataStruct.RX_Data[0] & 0x80) _AHT10_RawToHoomanVals();
}
