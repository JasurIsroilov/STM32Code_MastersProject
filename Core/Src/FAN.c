/*
 * FAN.c
 *
 *  Created on: Mar 22, 2024
 *      Author: Mi
 */
#include "stm32f1xx_hal.h"

#include "stdio.h"

#include "main.h"
#include "FAN.h"
#include "UART_Router.h"


void FAN_AnswerRequest()
{
	if(HAL_GPIO_ReadPin(FAN_GPIO_Port, FAN_Pin) == GPIO_PIN_RESET)
		sprintf(Router.MainBuff, "FAN:%s\n", ROUTER_MSG_FAN_ON);
	else
		sprintf(Router.MainBuff, "FAN:%s\n", ROUTER_MSG_FAN_OFF);
	return;
}
