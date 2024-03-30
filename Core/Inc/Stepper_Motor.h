/*
 * Stepper_Motor.h
 *
 *  Created on: 29 мар. 2024 г.
 *      Author: Mi
 */

#ifndef INC_STEPPER_MOTOR_H_
#define INC_STEPPER_MOTOR_H_

#include "stm32f1xx_hal.h"
#include "main.h"

#define STEPPER_MOTOR_TIMER_CLK 64000000 // 64Mhz -> APB1
#define STEPPER_MOTOR_HS_ROTOR_NSTEPS 4096 // half-steps mode. 4096 steps of a rotor for one full rotation

#define STEPPER_MOTOR_1_A_H HAL_GPIO_WritePin(Stepper_A_GPIO_Port, Stepper_A_Pin, GPIO_PIN_SET)
#define STEPPER_MOTOR_1_A_L HAL_GPIO_WritePin(Stepper_A_GPIO_Port, Stepper_A_Pin, GPIO_PIN_RESET)

#define STEPPER_MOTOR_1_B_H HAL_GPIO_WritePin(Stepper_B_GPIO_Port, Stepper_B_Pin, GPIO_PIN_SET)
#define STEPPER_MOTOR_1_B_L HAL_GPIO_WritePin(Stepper_B_GPIO_Port, Stepper_B_Pin, GPIO_PIN_RESET)

#define STEPPER_MOTOR_1_C_H HAL_GPIO_WritePin(Stepper_C_GPIO_Port, Stepper_C_Pin, GPIO_PIN_SET)
#define STEPPER_MOTOR_1_C_L HAL_GPIO_WritePin(Stepper_C_GPIO_Port, Stepper_C_Pin, GPIO_PIN_RESET)

#define STEPPER_MOTOR_1_D_H HAL_GPIO_WritePin(Stepper_D_GPIO_Port, Stepper_D_Pin, GPIO_PIN_SET)
#define STEPPER_MOTOR_1_D_L HAL_GPIO_WritePin(Stepper_D_GPIO_Port, Stepper_D_Pin, GPIO_PIN_RESET)

/*
 *	That'll be more precise way, if the struct contains GpioPorts and GpioPins.
 */

typedef struct
{
	uint8_t ntact; // Number of tact
	uint8_t rpm; // Rotates per minute
} StepperMotor_T;

StepperMotor_T StepperMotor_1;

void StepperMotor_Init(StepperMotor_T *stepper);
void StepperMotor_HalfStep_RotateCounterClockWise(StepperMotor_T *stepper);
void StepperMotor_HalfStep_RotateClockWise(StepperMotor_T *stepper);
void StepperMotor_SetSpeed(StepperMotor_T *stepper, TIM_HandleTypeDef *htim, uint8_t rpm);
void StepperMotor_StopRotation(StepperMotor_T *stepper, TIM_HandleTypeDef *htim);

#endif /* INC_STEPPER_MOTOR_H_ */
