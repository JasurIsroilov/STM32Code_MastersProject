#include "main.h"
#include "BMP280.h"

//------------------------------------------------------------
extern I2C_HandleTypeDef hi2c2;

extern UART_HandleTypeDef huart2;

extern char str1[100];
BMP280_CalibrationData _CalibrationData;
int32_t temper_int;
//------------------------------------------------------------

void _BMP280_Error(void)
{
	sprintf(str1, "BMP280 error\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 0x1000);
}

//------------------------------------------------------------
uint8_t _BMP280_I2Cx_WriteData(uint16_t addr, uint8_t reg, uint8_t value)
{
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Write(&hi2c2, addr, (uint16_t)reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 0x10000);
	if(status != HAL_OK) _BMP280_Error();
	return value;
}

uint8_t _BMP280_I2Cx_ReadData(uint16_t addr, uint8_t reg)
{
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t value = 0;
	status = HAL_I2C_Mem_Read(&hi2c2, addr, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 0x10000);
	if(status != HAL_OK) _BMP280_Error();
	return value;
}

void _BMP280_I2Cx_ReadData16(uint16_t addr, uint8_t reg, uint16_t *value)
{
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Read(&hi2c2, addr, reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)value, 2, 0x10000);
	if(status != HAL_OK) _BMP280_Error();
}

void _BMP280_I2Cx_ReadData24(uint16_t addr, uint8_t reg, uint32_t *value)
{
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Read(&hi2c2, addr, reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)value, 3, 0x10000);
	if(status != HAL_OK) _BMP280_Error();
}

void _BMP280_WriteReg(uint8_t reg, uint8_t value)
{
	_BMP280_I2Cx_WriteData(BMP280_ADDRESS, reg, value);
}

//------------------------------------------------------------

uint8_t _BMP280_ReadReg(uint8_t reg)
{
	uint8_t res = _BMP280_I2Cx_ReadData(BMP280_ADDRESS, reg);
	return res;
}

uint8_t _BMP280_ReadStatus(void)
{
	uint8_t res = _BMP280_ReadReg(BMP280_REGISTER_STATUS) & 0x09;
	return res;
}

//------------------------------------------------------------

void _BMP280_ReadReg_U16(uint8_t reg, uint16_t *value)
{
	_BMP280_I2Cx_ReadData16(BMP280_ADDRESS, reg, value);
}

void _BMP280_ReadReg_S16(uint8_t reg, int16_t *value)
{
	_BMP280_I2Cx_ReadData16(BMP280_ADDRESS, reg, (uint16_t*) value);
}

void _BMP280_ReadReg_U24(uint8_t reg, uint32_t *value)
{
	_BMP280_I2Cx_ReadData24(BMP280_ADDRESS, reg, value);
	*(uint32_t *) value &= 0x00FFFFFF;
}

void _BMP280_ReadReg_BE_U24(uint8_t reg, uint32_t *value)
{
  _BMP280_I2Cx_ReadData24(BMP280_ADDRESS, reg, value);
  *(uint32_t *) value = be24toword(*(uint32_t *) value) & 0x00FFFFFF;
}

//------------------------------------------------------------

void _BMP280_ReadCoefficients(void)
{
  _BMP280_ReadReg_U16(BMP280_REGISTER_DIG_P1, &_CalibrationData.dig_P1);

  _BMP280_ReadReg_S16(BMP280_REGISTER_DIG_P2, &_CalibrationData.dig_P2);

  _BMP280_ReadReg_S16(BMP280_REGISTER_DIG_P3, &_CalibrationData.dig_P3);

  _BMP280_ReadReg_S16(BMP280_REGISTER_DIG_P4, &_CalibrationData.dig_P4);

  _BMP280_ReadReg_S16(BMP280_REGISTER_DIG_P5, &_CalibrationData.dig_P5);

  _BMP280_ReadReg_S16(BMP280_REGISTER_DIG_P6, &_CalibrationData.dig_P6);

  _BMP280_ReadReg_S16(BMP280_REGISTER_DIG_P7, &_CalibrationData.dig_P7);

  _BMP280_ReadReg_S16(BMP280_REGISTER_DIG_P8, &_CalibrationData.dig_P8);

  _BMP280_ReadReg_S16(BMP280_REGISTER_DIG_P9, &_CalibrationData.dig_P9);
}

//------------------------------------------------------------

void _BMP280_SetStandby(uint8_t tsb) {
	uint8_t reg;
	reg = _BMP280_ReadReg(BMP280_REG_CONFIG) & ~BMP280_STBY_MSK;
	reg |= tsb & BMP280_STBY_MSK;
	_BMP280_WriteReg(BMP280_REG_CONFIG, reg);
}

//------------------------------------------------------------

void _BMP280_SetFilter(uint8_t filter) {
	uint8_t reg;
	reg = _BMP280_ReadReg(BMP280_REG_CONFIG) & ~BMP280_FILTER_MSK;
	reg |= filter & BMP280_FILTER_MSK;
	_BMP280_WriteReg(BMP280_REG_CONFIG, reg);
}

//------------------------------------------------------------

void _BMP280_SetOversamplingPressure(uint8_t osrs)
{
	uint8_t reg;
	reg = _BMP280_ReadReg(BMP280_REG_CTRL_MEAS) & ~BMP280_OSRS_P_MSK;
	reg |= osrs & BMP280_OSRS_P_MSK;
	_BMP280_WriteReg(BMP280_REG_CTRL_MEAS, reg);
}

//------------------------------------------------------------

void _BMP280_SetMode(uint8_t mode)
{
  uint8_t reg;
  reg = _BMP280_ReadReg(BMP280_REG_CTRL_MEAS) & ~BMP280_MODE_MSK;
  reg |= mode & BMP280_MODE_MSK;
  _BMP280_WriteReg(BMP280_REG_CTRL_MEAS, reg);
}

//------------------------------------------------------------

float BMP280_ReadPressure(void)
{
  float press_float = 0.0f;
  uint32_t press_raw, pres_int;
  int64_t val1, val2, p;

  _BMP280_ReadReg_BE_U24(BMP280_REGISTER_PRESSUREDATA, &press_raw);
  press_raw >>= 4;
  val1 = ((int64_t) temper_int) - 128000;
  val2 = val1 * val1 * (int64_t)_CalibrationData.dig_P6;
  val2 = val2 + ((val1 * (int64_t)_CalibrationData.dig_P5) << 17);
  val2 = val2 + ((int64_t)_CalibrationData.dig_P4 << 35);
  val1 = ((val1 * val1 * (int64_t)_CalibrationData.dig_P3) >> 8) + ((val1 * (int64_t)_CalibrationData.dig_P2) << 12);
  val1 = (((((int64_t)1) << 47) + val1)) * ((int64_t)_CalibrationData.dig_P1) >> 33;
  if (val1 == 0)
  {
    return 0; // avoid exception caused by division by zero
  }
  p = 1048576 - press_raw;
  p = (((p << 31) - val2) * 3125) / val1;
  val1 = (((int64_t)_CalibrationData.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
  val2 = (((int64_t)_CalibrationData.dig_P8) * p) >> 19;
  p = ((p + val1 + val2) >> 8) + ((int64_t)_CalibrationData.dig_P7 << 4);
  pres_int = ((p >> 8) * 1000) + (((p & 0xff) * 390625) / 100000);
  press_float = pres_int / 100.0f;
  return press_float;
}

//------------------------------------------------------------

void BMP280_Init(void)
{
	uint32_t value32 = 0;

	LED_ON;
	sprintf(str1, "BMP280 Initializing...\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 0x1000);

	uint8_t value = _BMP280_ReadReg(BMP280_REG_ID);
	sprintf(str1, "BMP280_CHIP_ID: 0x%02X\n", value);
	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 0x1000);

	if(value != BMP280_CHIP_ID)
	{
		_BMP280_Error();
		return;
	}

	sprintf(str1, "BMP280 resetting the software...\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 0x1000);
	_BMP280_WriteReg(BMP280_SOFTRESET_REG, BMP280_SOFTRESET_VALUE);
	while(_BMP280_ReadStatus() & BMP280_STATUS_IM_UPTODATE);

	sprintf(str1, "BMP280 reading calibration data...\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 0x1000);
	_BMP280_ReadCoefficients();

	sprintf(str1, "BMP280 setting standby time 1sec...\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 0x1000);
	_BMP280_SetStandby(BMP280_STBY_1000);

	sprintf(str1, "BMP280 setting IIR filter...\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 0x1000);
	_BMP280_SetFilter(BMP280_FILTER_4);

	sprintf(str1, "BMP280 setting oversampling times for P...\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 0x1000);
	_BMP280_SetOversamplingPressure(BMP280_OSRS_P_x2);

	sprintf(str1, "BMP280 checking oversampling install...\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 0x1000);
	value32 = _BMP280_ReadReg(BMP280_REG_CTRL_MEAS);
	sprintf(str1, "Measurements status: %04X\n", value32);
	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 0x1000);

	sprintf(str1, "Pressure: %s\n", (value32 & BMP280_OSRS_P_MSK) ? "ON" : "OFF");
	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 0x1000);

	sprintf(str1, "BMP280 setting normal mode...\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 0x1000);
	_BMP280_SetMode(BMP280_MODE_NORMAL);

	sprintf(str1, "BMP280 Initialization completed\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), 0x1000);
}

//------------------------------------------------------------
