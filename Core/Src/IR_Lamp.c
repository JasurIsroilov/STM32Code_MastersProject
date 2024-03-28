/*
 * IR_Lamp.c
 *
 *  Created on: 27 мар. 2024 г.
 *      Author: Mi
 */

#include "stm32f1xx_hal.h"

#include "stdio.h"

#include "main.h"
#include "FAN.h"
#include "UART_Router.h"


void IR_Lamp_AnswerRequest()
{
	if(HAL_GPIO_ReadPin(IR_Lamp_GPIO_Port, IR_Lamp_Pin) == GPIO_PIN_RESET)
		sprintf(Router.MainBuff, "LAMP:%s\n", ROUTER_MSG_IR_LAMP_ON);
	else
		sprintf(Router.MainBuff, "LAMP:%s\n", ROUTER_MSG_IR_LAMP_OFF);
	return;
}
