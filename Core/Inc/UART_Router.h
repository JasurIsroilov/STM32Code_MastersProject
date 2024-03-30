#ifndef INC_UART_ROUTER_H_
#define INC_UART_ROUTER_H_

#include "stm32f1xx_hal.h"

#include "string.h"

#define ROUTER_RX_BUFF_SIZE 50
#define ROUTER_MAIN_BUFF_SIZE 100

#define ROUTER_CMD_GET_DEVICE_ID '0'
#define ROUTER_CMD_GET_TEMPERATURE 't'
#define ROUTER_CMD_GET_PRESSURE 'p'
#define ROUTER_CMD_GET_HUMIDITY 'h'
#define ROUTER_CMD_FAN_TOGGLE 'f'
#define ROUTER_CMD_AirPump_TOGGLE 'a'
#define ROUTER_CMD_RKPSS_ADC_VAL 's'
#define ROUTER_CMD_WaterLevelSensor_ADC_VAL 'l'
#define ROUTER_CMD_IR_LAMP_TOGGLE 'i'
#define ROUTER_CMD_STEPPER_MOTOR_ROTATE 'm'

#define ROUTER_MSG_SOUND_DETECTED "SOUND\n"
#define ROUTER_MSG_MOTOR_LEFT_BORDER "LEFT_BORDER\n"
#define ROUTER_MSG_MOTOR_RIGHT_BORDER "RIGHT_BORDER\n"
#define ROUTER_MSG_FAN_ON "ON"
#define ROUTER_MSG_FAN_OFF "OFF"
#define ROUTER_MSG_AirPump_ON "ON"
#define ROUTER_MSG_AirPump_OFF "OFF"
#define ROUTER_MSG_IR_LAMP_ON "ON"
#define ROUTER_MSG_IR_LAMP_OFF "OFF"
#define ROUTER_MSG_STEPPER_MOTOR_CW "STEPPER:CLOCKWISE\n"
#define ROUTER_MSG_STEPPER_MOTOR_CCW "STEPPER:COUNTERCLOCKWISE\n"

typedef struct {
	uint8_t RxBuff[ROUTER_RX_BUFF_SIZE];
	char MainBuff[ROUTER_MAIN_BUFF_SIZE];
} Router_T;

Router_T Router;

void Router_CommandHandler();
void Router_UART_Transmit_DMA(const uint8_t *pData, uint16_t Size);

#endif /* INC_UART_ROUTER_H_ */
