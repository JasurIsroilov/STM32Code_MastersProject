/*
 * ADC_modules.h
 *
 *  Created on: Mar 23, 2024
 *      Author: Mi
 */

#ifndef INC_ADC_MODULES_H_
#define INC_ADC_MODULES_H_

#define ADC1_N_CHANNELS 1

#include "stm32f1xx_hal.h"


#define WaterLevelSensor_EMPTY 1000
#define WaterLevelSensor_HALF 1980
#define WaterLevelSensor_FULL 2000

typedef struct {
	uint16_t Data[ADC1_N_CHANNELS];
	uint8_t Level;
	uint8_t NChannels;
} ADC_Module_T;

ADC_Module_T ADC1_Module;

void ADC1_Module_Init();

#endif /* INC_ADC_MODULES_H_ */
