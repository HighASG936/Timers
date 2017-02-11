#ifndef TIMERS_H
#define TIMERS_H

#include "stm32f7xx_hal.h"

#define MAX_NUMBER_COUNTERS 256
//Prototipos
void Timer_Inicializar(void);

//Estructuras y uniones

enum
{
	ec_Buzzer,
	ec_Delay,
	ec_Max
}eCounters;

typedef struct
{
	uint16_t MilisCounter[MAX_NUMBER_COUNTERS];
}sCounters;


typedef struct
{
	sCounters BaseTime;
	TIM_HandleTypeDef Timer;										//Estructura del temporizador (ms) del buzzer y otros servicios
}sTimer;

sTimer gsTimer;

/* Inicialización del temporizador */
void Timer_Inicializar(void)
{
  TIM_MasterConfigTypeDef sMasterConfig;
	gsTimer.Timer.Instance = TIM7;
  gsTimer.Timer.Init.Prescaler = 108;
  gsTimer.Timer.Init.CounterMode = TIM_COUNTERMODE_DOWN;
  gsTimer.Timer.Init.Period = 999;
  HAL_TIM_Base_Init(&gsTimer.Timer);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&gsTimer.Timer, &sMasterConfig);
	HAL_NVIC_SetPriority(TIM7_IRQn,5,0);
	HAL_NVIC_EnableIRQ(TIM7_IRQn);
	
	HAL_TIM_Base_Start_IT(&gsTimer.Timer);
}


/* Handler de interrupción temporizador */
void TIM7_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&gsTimer.Timer);
	
	if(gsTimer.BaseTime.MilisCounter[ec_Buzzer] == 0) return;
	if(gsTimer.BaseTime.MilisCounter[ec_Delay] == 0) return;
	
	gsTimer.BaseTime.MilisCounter[ec_Buzzer]--;
	gsTimer.BaseTime.MilisCounter[ec_Delay]--;
}

#endif
