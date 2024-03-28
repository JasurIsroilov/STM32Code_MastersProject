/*
 * AirPump.h
 *
 *  Created on: Mar 24, 2024
 *      Author: Mi
 */

#ifndef INC_AIRPUMP_H_
#define INC_AIRPUMP_H_

#include "stm32f1xx_hal.h"
#include "main.h"

#define AIR_PUMP_ON HAL_GPIO_WritePin(AirPump_GPIO_Port, AirPump_Pin, GPIO_PIN_RESET)
#define AIR_PUMP_OFF HAL_GPIO_WritePin(AirPump_GPIO_Port, AirPump_Pin, GPIO_PIN_SET)
#define AIR_PUMP_TOGGLE HAL_GPIO_TogglePin(AirPump_GPIO_Port, AirPump_Pin)

void AirPump_AnswerRequest();

#endif /* INC_AIRPUMP_H_ */
