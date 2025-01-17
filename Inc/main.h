/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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

#define __ENABLE_5V_BUCK ( GPIOB->PUPDR = (GPIOB->PUPDR & ~(3 << 0)) | (1 << 0) )
#define __DISABLE_5V_BUCK ( GPIOB->PUPDR = (GPIOB->PUPDR & ~(3 << 0)) | (1 << 1) )

#define __ENABLE_CHG ( GPIOA->BSRR = (1 << 8) )
#define __DISABLE_CHG ( GPIOA->BSRR = (1 << 24) )

#define __ENABLE_BAT_VOLTAGE ( GPIOB->BSRR = (1 << 2) )
#define __DISABLE_BAT_VOLTAGE ( GPIOB->BSRR = (1 << 18) )

#define __ENABLE_CHARGER_VOLTAGE ( GPIOB->BSRR = (1 << 12) )
#define __DISABLE_CHARGER_VOLTAGE ( GPIOB->BSRR = (1 << 28) )

#define __BLUE_LED_ON ( GPIOB->BSRR |= (1 << 31) )
#define __BLUE_LED_OFF ( GPIOB->BSRR |= (1 << 15) )

#define __GREEN_LED_ON ( GPIOB->BSRR |= (1 << 30) )
#define __GREEN_LED_OFF ( GPIOB->BSRR |= (1 << 14) )

#define __RED_LED_ON ( GPIOB->BSRR |= (1 << 29) )
#define __RED_LED_OFF ( GPIOB->BSRR |= (1 << 13) )

#define __TIME_HOUR_TICKS ( 3600000 )
#define __TIME_MINUTES_TICKS ( 60000 )

#include "stm32l4xx_hal.h"

typedef enum
{
	fault_lowPackVoltage = 0,
	fault_highPackVoltage,
	fault_lowCellVoltage0,
	fault_highCellVoltage0,
	fault_lowCellVoltage1,
	fault_highCellVoltage1,
	fault_lowCellVoltage2,
	fault_highCellVoltage2,
	fault_lowCellVoltage3,
	fault_highCellVoltage3,
	fault_lowCellVoltage4,
	fault_highCellVoltage4,
	fault_lowCellVoltage5,
	fault_highCellVoltage5,
	fault_lowCellVoltage6,
	fault_highCellVoltage6,
	fault_lowCellVoltage7,
	fault_highCellVoltage7,
	fault_lowCellVoltage8,
	fault_highCellVoltage8,
	fault_lowCellVoltage9,
	fault_highCellVoltage9,
	fault_lowCellVoltage10,
	fault_highCellVoltage10,
	fault_lowCellVoltage11,
	fault_highCellVoltage11,
	fault_voltageErrorCell0,
	fault_voltageErrorCell1,
	fault_voltageErrorCell2,
	fault_voltageErrorCell3,
	fault_voltageErrorCell4,
	fault_voltageErrorCell5,
	fault_voltageErrorCell6,
	fault_voltageErrorCell7,
	fault_voltageErrorCell8,
	fault_voltageErrorCell9,
	fault_voltageErrorCell10,
	fault_voltageErrorCell11,
	fault_highChargerVoltage,
	fault_highChargingCurrent,
	fault_lowBMStemp,
	fault_highBMStemp,
	fault_lowNTCtemp,
	fault_highNTCtemp,
	fault_heartbeatTimeout,
	fault_parallelUnitFault1,
	fault_parallelUnitFault2,
	fault_parallelUnitFault3,
	fault_numberOfElements
}_fault_ID;

typedef enum
{
	chargingEnd_none,
	chargingEnd_termPackVoltage,
	chargingEnd_termCellVoltage0,
	chargingEnd_termCellVoltage1,
	chargingEnd_termCellVoltage2,
	chargingEnd_termCellVoltage3,
	chargingEnd_termCellVoltage4,
	chargingEnd_termCellVoltage5,
	chargingEnd_termCellVoltage6,
	chargingEnd_termCellVoltage7,
	chargingEnd_termCellVoltage8,
	chargingEnd_termCellVoltage9,
	chargingEnd_termCellVoltage10,
	chargingEnd_termCellVoltage11,
	chargingEnd_termChargingCurrent,
	chargingEnd_numberOfElements
}_chargingEnd_ID;

typedef enum
{
	usb5vRequest = 0,
	charging5vRequest,
	ntc5vRequest,
	led5vRequest,
	balancing5vRequest,
	always5vRequest,
	opto5vRequest,
	active5vRequest
}_5vRequest_ID;

enum
{
	notCharging = 0,
	chargingStarting,
	startingCurrent,
	charging,
	chargingEnd,
	chargerDisconnected,
	faultState,
	waiting
}_chargingState_ID;

typedef struct __attribute__((packed)) _chargingParameters {
	uint16_t packCellCount;	//# number of series cells in the battery pack
	uint16_t maxChgCurr;	//mA (milliAmps), maximum current allowed to flow to battery
	uint16_t termCurr;		//mA (milliAmps), stop charging when current drops below this

	uint16_t minCellVolt;	//mV (milliVolts), minimum allowable cell voltage, no charging allowed if cell voltage below
	uint16_t maxCellVolt;	//mV (milliVolts), maximum allowable cell voltage, no charging allowed if cell voltage above
	uint16_t minChgVolt;	//mV (milliVolts), minimum allowable charger voltage, no charging allowed if charger voltage below
	uint16_t maxChgVolt;	//mV (milliVolts), minimum allowable charger voltage, no charging allowed if charger voltage above
	uint16_t minPackVolt;	//mV (milliVolts), minimum allowable pack voltage, no charging allowed if cell voltage below
	uint16_t maxPackVolt;	//mV (milliVolts), maximum allowable pack voltage, no charging allowed if cell voltage above

	uint16_t termCellVolt;	//mV (milliVolts), don't allow any cell to go above this voltage
	uint16_t termPackVolt;	//mV (milliVolts), don't allow pack to go above this voltage
	uint16_t cellBalVolt;	//mV (milliVolts), allow balancing once a cell goes above this voltage
	uint16_t cellDiffVolt;	//mV (milliVolts), maximum allowed voltage difference between cell groups, balance if difference bigger

	uint16_t balTempRatio;	//K (Kelvin), balancing temperature ratio of how many simultaneous resistors can be on at any time

	uint16_t minNTCtemp;		//K (Kelvin), if NTC probe enabled, the minimum temperature above which charging is allowed
	uint16_t maxNTCtemp;		//K (Kelvin), if NTC probe enabled, the maximum temperature below which charging is allowed
	uint16_t minBMStemp;		//K (Kelvin), PCB temperature, the minimum temperature above which charging is allowed
	uint16_t maxBMStemp;		//K (Kelvin), PCB temperature, the maximum temperature below which charging is allowed

	uint16_t refreshWaitTime;	//s (seconds), wait time
	uint16_t restartChargTime;	//s (seconds), how much time to wait before attempting to restart charging from a non-fault charging end

} chargingParameters;

typedef struct __attribute__((packed)) _ADCparameters {
	float ADC_chan_gain[5];		//gain adjustments for ADC_channels
	float ADC_chan_offset[5];	//offset adjustments ADC_channels
	uint16_t extNTCbetaValue;	//external NTC sensors beta value
	uint16_t AdcOversampling;	//oversampling setting for ADC
} ADCparameters;

typedef struct __attribute__((packed)) _generalParameters {
	uint16_t stayActiveTime;	//h (Hours), how long to stay in active mode
	uint8_t alwaysBalancing;	//1 or 0, allow balancing even when not charging
	uint8_t always5vRequest;	//1 or 0, force 5V buck always on
	uint8_t duringStandby5vOn;	//1 or 0, whether to keep 5V regulator on during active time, even if USB, charger or Opto not active

	uint16_t storageCellVoltage;	//mV (milliVolts), what voltage to discharge cells if storage voltage discharge enabled
	uint16_t timeToStorageDischarge;	//h (hours), how long to wait after active state to start discharging cells to storage voltage

	uint8_t canActivityTick;	//1 or 0, ticks the status led in magenta when can packets are received
	uint8_t canID;				//canID that the BMS uses to recognize as itself
	uint16_t canRxRefreshActive;	//min (minutes),Receiving CAN messages refresh activeTimer up to this length, 0 to disable
	uint8_t canWakeUp;			//1 or 0, allows or disallows CAN activity to wake-up BMS from sleep, increases quiescent current somewhat
	uint8_t parallelPackCount;	//how many parallel packs there is alongside this BMS, 0 to disable
	uint8_t currentVoltageRatio;		//used as a scaling factor to improve the behavior of parallel pack's joining into the charging session based on the charging curren
} generalParameters;

typedef struct __attribute__((packed)) _nonVolParameters {
	uint16_t FW_version;
	chargingParameters chgParas;
	ADCparameters adcParas;
	generalParameters genParas;
} nonVolParameters;

typedef struct _parallelPackInfo {
	uint8_t parPackCanId;	//parallel pack's CAN ID
	uint32_t packVoltage;	//parallel pack's reported pack voltage (10 mV LSB)
	uint16_t chargingCurrent;	//parallel pack's reported charging current (10 mA LSB)
	uint64_t lastMessageTick;	//system tick timestamp when the last heartbeat message received, used for timeout detection
	uint8_t bitFields;		//fault, current under termination limit, termination voltage hit, charging state
}parallelPackInfo;

typedef struct _runtimeParameters {
	uint16_t statePrintout;
	uint16_t statusTick;
	uint16_t ADCrunState;
	uint16_t LTC6803runState;
	uint16_t usbConnected;
	uint16_t chargerConnected;
	uint16_t optoActive;
	uint16_t activeTimerState;
	uint16_t storageTimerState;
	uint16_t storageDischarged;
	uint16_t chargingState;
	uint16_t currentRunMode;
	uint64_t latchedFaults;
	uint16_t faultCount[fault_numberOfElements];
	uint16_t chargingEndFlag;

	uint16_t buck5vEnabled;
	uint16_t buck5vRequest;
	uint16_t packVoltageEnabled;
	uint16_t packVoltageRequest;
	uint16_t chargerVoltageEnabled;
	uint16_t chargerVoltageRequest;
	uint16_t canActivity;

	uint16_t charging;
	uint16_t balancing;

	uint64_t activeTick;
	uint64_t storageTick;

	parallelPackInfo parPacks[3];

} runtimeParameters;

void Error_Handler(void);
extern uint8_t initNonVolatiles(nonVolParameters*, uint8_t);
extern void initRuntimeParameters(runtimeParameters*);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
