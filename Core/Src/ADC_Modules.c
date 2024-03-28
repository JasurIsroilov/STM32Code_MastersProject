/*
 * ADC_Modules.c
 *
 *  Created on: Mar 23, 2024
 *      Author: Mi
 */

#include "ADC_Modules.h"

void ADC1_Module_Init()
{
	ADC1_Module.NChannels = ADC1_N_CHANNELS;
	ADC1_Module.Level = 0;
}
