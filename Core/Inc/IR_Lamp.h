/*
 * IR_Lamp.h
 *
 *  Created on: 27 мар. 2024 г.
 *      Author: Mi
 */

#ifndef INC_IR_LAMP_H_
#define INC_IR_LAMP_H_

#include "stm32f1xx_hal.h"
#include "main.h"

#define IR_LAMP_ON HAL_GPIO_WritePin(IR_Lamp_GPIO_Port, IR_Lamp_Pin, GPIO_PIN_RESET)
#define IR_LAMP_OFF HAL_GPIO_WritePin(IR_Lamp_GPIO_Port, IR_Lamp_Pin, GPIO_PIN_SET)
#define IR_LAMP_TOGGLE HAL_GPIO_TogglePin(IR_Lamp_GPIO_Port, IR_Lamp_Pin)

void IR_Lamp_AnswerRequest();

#endif /* INC_IR_LAMP_H_ */
