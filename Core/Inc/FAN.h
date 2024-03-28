/*
 * FAN.h
 *
 *  Created on: Mar 22, 2024
 *      Author: Mi
 */

#ifndef INC_FAN_H_
#define INC_FAN_H_

#include "stm32f1xx_hal.h"
#include "main.h"

#define FAN_ON HAL_GPIO_WritePin(FAN_GPIO_Port, FAN_Pin, GPIO_PIN_RESET)
#define FAN_OFF HAL_GPIO_WritePin(FAN_GPIO_Port, FAN_Pin, GPIO_PIN_SET)
#define FAN_TOGGLE HAL_GPIO_TogglePin(FAN_GPIO_Port, FAN_Pin)

void FAN_AnswerRequest();

#endif /* INC_FAN_H_ */
