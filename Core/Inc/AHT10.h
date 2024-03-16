#ifndef AHT10_H_

#define AHT10_H_

//------------------------------------------------------------
#include "stm32f1xx_hal.h"

#include <stdio.h>
#include <string.h>
//------------------------------------------------------------

#define AHT10_ADDRESS 0x38 << 1

//------------------------------------------------------------

typedef struct {
	uint32_t ADC_Raw;
	float Temperature;
	float Moisture;
	uint8_t RX_Data[6];
} AHT10_DataStruct_T;

AHT10_DataStruct_T AHT10_DataStruct;

//------------------------------------------------------------

void AHT10_Measure(void);

#endif /* AHT10_H_ */
