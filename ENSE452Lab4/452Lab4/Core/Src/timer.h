#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_


#include "main.h"

extern TIM_HandleTypeDef htim4;

uint16_t startTimer();
uint16_t stopTimer(uint16_t first);

#endif
