#ifndef AHT10_H_

#define AHT10_H_

//------------------------------------------------------------
#include "stm32f1xx_hal.h"

#include <stdio.h>
#include <string.h>
//------------------------------------------------------------

#define AHT10_ADDRESS 0x38 << 1

#define AHT10_TRIGGER_MEASUREMENTS_PERIOD 10
#define AHT10_READ_DATA_PERIOD 15

//------------------------------------------------------------

typedef struct {
	uint32_t ADC_Raw;
	float Temperature;
	float Humidity;
	uint8_t RX_Data[6];
	uint8_t TriggerTimeCounter;
	uint8_t ReadDataTimerCounter;
} AHT10_DataStruct_T;

AHT10_DataStruct_T AHT10_DataStruct;

//------------------------------------------------------------

void AHT10_Measure(void);
void AHT10_TriggerMeasurements(void);
void AHT10_Init();

#endif /* AHT10_H_ */
