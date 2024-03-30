/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define DEVICE_ID "SecretToken"

#define LED_GPIO_PORT GPIOA
#define LED_PIN GPIO_PIN_5

#define LED_ON HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET)
#define LED_OFF HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET)
#define LED_TOGGLE HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN)
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define YL63_R_Pin GPIO_PIN_0
#define YL63_R_GPIO_Port GPIOC
#define YL63_R_EXTI_IRQn EXTI0_IRQn
#define YL63_L_Pin GPIO_PIN_1
#define YL63_L_GPIO_Port GPIOC
#define YL63_L_EXTI_IRQn EXTI1_IRQn
#define RKPSS_Pin GPIO_PIN_2
#define RKPSS_GPIO_Port GPIOC
#define RKPSS_EXTI_IRQn EXTI2_IRQn
#define Stepper_A_Pin GPIO_PIN_0
#define Stepper_A_GPIO_Port GPIOA
#define Stepper_B_Pin GPIO_PIN_1
#define Stepper_B_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define AirPump_Pin GPIO_PIN_13
#define AirPump_GPIO_Port GPIOB
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define Stepper_C_Pin GPIO_PIN_10
#define Stepper_C_GPIO_Port GPIOC
#define Stepper_D_Pin GPIO_PIN_12
#define Stepper_D_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define FAN_Pin GPIO_PIN_8
#define FAN_GPIO_Port GPIOB
#define IR_Lamp_Pin GPIO_PIN_9
#define IR_Lamp_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
