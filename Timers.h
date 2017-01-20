#ifndef TIMERS_H
#define TIMERS_H

#include "stm32f7xx_hal.h"

//Prototipos
void Timer_Inicializar(void);
private void TIM7_IRQHandler(void);

//Variables privadas
TIM_HandleTypeDef Timer;

//Handler de interrupcion
void TIM7_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&Timer);
	//Serial_AtencionBuzzer();
}

/* TIM7 init function */
void Timer_Inicializar(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;

  Timer.Instance = TIM7;
  Timer.Init.Prescaler = 108;
  Timer.Init.CounterMode = TIM_COUNTERMODE_DOWN;
  Timer.Init.Period = 999;
  HAL_TIM_Base_Init(&Timer);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&Timer, &sMasterConfig);
	HAL_NVIC_SetPriority(TIM7_IRQn,2,0);
	HAL_NVIC_EnableIRQ(TIM7_IRQn);
}

#endif