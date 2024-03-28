/*
 * AirPump.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Mi
 */

#include "stm32f1xx_hal.h"

#include "stdio.h"

#include "main.h"
#include "AirPump.h"
#include "UART_Router.h"

void AirPump_AnswerRequest()
{
	if(HAL_GPIO_ReadPin(AirPump_GPIO_Port, AirPump_Pin) == GPIO_PIN_RESET)
		sprintf(Router.MainBuff, "AirPump:%s\n", ROUTER_MSG_AirPump_ON);
	else
		sprintf(Router.MainBuff, "AirPump:%s\n", ROUTER_MSG_AirPump_OFF);
	return;
}
