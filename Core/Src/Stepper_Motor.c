/*
 * Stepper_Motor.c
 *
 *  Created on: 29 мар. 2024 г.
 *      Author: Mi
 */

#include "stm32f1xx_hal.h"

#include "main.h"
#include "Stepper_Motor.h"

void StepperMotor_Init(StepperMotor_T *stepper)
{
	stepper->ntact = 0;
	stepper->rpm = 0;
}

void StepperMotor_SetSpeed(StepperMotor_T *stepper, TIM_HandleTypeDef *htim, uint8_t rpm)
{
	htim->Init.Prescaler = STEPPER_MOTOR_TIMER_CLK / 10000 - 1;
	htim->Init.Period = 10000 / (STEPPER_MOTOR_HS_ROTOR_NSTEPS / (60 / 10)) - 1; // 10000 / (4096 / (60secs / 10 rpm )) - 1
}

void StepperMotor_StopRotation(StepperMotor_T *stepper, TIM_HandleTypeDef *htim)
{
	HAL_TIM_Base_Stop_IT(htim);
	STEPPER_MOTOR_1_A_L;
	STEPPER_MOTOR_1_B_L;
	STEPPER_MOTOR_1_C_L;
	STEPPER_MOTOR_1_D_L;
	stepper->ntact = 0;
}

/*
 * Half-Step mode is recommended.
 * 8 states for a step
 * Gear ratio is about 64
 * So 8*64 = 4096 steps for a 360 degrees rotation
 */
void StepperMotor_HalfStep_RotateCounterClockWise(StepperMotor_T *stepper)
{
	switch(stepper->ntact)
	{
		case 0:
			STEPPER_MOTOR_1_A_H;
			STEPPER_MOTOR_1_B_L;
			STEPPER_MOTOR_1_C_L;
			STEPPER_MOTOR_1_D_L;
			stepper->ntact++;
			break;

		case 1:
			STEPPER_MOTOR_1_A_H;
			STEPPER_MOTOR_1_B_H;
			STEPPER_MOTOR_1_C_L;
			STEPPER_MOTOR_1_D_L;
			stepper->ntact++;
			break;

		case 2:
			STEPPER_MOTOR_1_A_L;
			STEPPER_MOTOR_1_B_H;
			STEPPER_MOTOR_1_C_L;
			STEPPER_MOTOR_1_D_L;
			stepper->ntact++;
			break;

		case 3:
			STEPPER_MOTOR_1_A_L;
			STEPPER_MOTOR_1_B_H;
			STEPPER_MOTOR_1_C_H;
			STEPPER_MOTOR_1_D_L;
			stepper->ntact++;
			break;

		case 4:
			STEPPER_MOTOR_1_A_L;
			STEPPER_MOTOR_1_B_L;
			STEPPER_MOTOR_1_C_H;
			STEPPER_MOTOR_1_D_L;
			stepper->ntact++;
			break;

		case 5:
			STEPPER_MOTOR_1_A_L;
			STEPPER_MOTOR_1_B_L;
			STEPPER_MOTOR_1_C_H;
			STEPPER_MOTOR_1_D_H;
			stepper->ntact++;
			break;

		case 6:
			STEPPER_MOTOR_1_A_L;
			STEPPER_MOTOR_1_B_L;
			STEPPER_MOTOR_1_C_L;
			STEPPER_MOTOR_1_D_H;
			stepper->ntact++;
			break;

		case 7:
			STEPPER_MOTOR_1_A_H;
			STEPPER_MOTOR_1_B_L;
			STEPPER_MOTOR_1_C_L;
			STEPPER_MOTOR_1_D_H;
			stepper->ntact = 0;
			break;

	}
}

void StepperMotor_HalfStep_RotateClockWise(StepperMotor_T *stepper)
{
	switch(stepper->ntact)
	{
		case 0:
			STEPPER_MOTOR_1_A_L;
			STEPPER_MOTOR_1_B_L;
			STEPPER_MOTOR_1_C_L;
			STEPPER_MOTOR_1_D_H;
			stepper->ntact++;
			break;

		case 1:
			STEPPER_MOTOR_1_A_L;
			STEPPER_MOTOR_1_B_L;
			STEPPER_MOTOR_1_C_H;
			STEPPER_MOTOR_1_D_H;
			stepper->ntact++;
			break;

		case 2:
			STEPPER_MOTOR_1_A_L;
			STEPPER_MOTOR_1_B_L;
			STEPPER_MOTOR_1_C_H;
			STEPPER_MOTOR_1_D_L;
			stepper->ntact++;
			break;

		case 3:
			STEPPER_MOTOR_1_A_L;
			STEPPER_MOTOR_1_B_H;
			STEPPER_MOTOR_1_C_H;
			STEPPER_MOTOR_1_D_L;
			stepper->ntact++;
			break;

		case 4:
			STEPPER_MOTOR_1_A_L;
			STEPPER_MOTOR_1_B_H;
			STEPPER_MOTOR_1_C_L;
			STEPPER_MOTOR_1_D_L;
			stepper->ntact++;
			break;

		case 5:
			STEPPER_MOTOR_1_A_H;
			STEPPER_MOTOR_1_B_H;
			STEPPER_MOTOR_1_C_L;
			STEPPER_MOTOR_1_D_L;
			stepper->ntact++;
			break;

		case 6:
			STEPPER_MOTOR_1_A_H;
			STEPPER_MOTOR_1_B_L;
			STEPPER_MOTOR_1_C_L;
			STEPPER_MOTOR_1_D_L;
			stepper->ntact++;
			break;

		case 7:
			STEPPER_MOTOR_1_A_H;
			STEPPER_MOTOR_1_B_L;
			STEPPER_MOTOR_1_C_L;
			STEPPER_MOTOR_1_D_H;
			stepper->ntact = 0;
			break;

	}
}
