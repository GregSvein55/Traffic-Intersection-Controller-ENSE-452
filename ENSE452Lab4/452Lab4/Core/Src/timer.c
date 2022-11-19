#include "timer.h"


uint16_t startTimer()
{
	return __HAL_TIM_GET_COUNTER(&htim4);
}

uint16_t stopTimer(uint16_t start)
{
	uint16_t end = __HAL_TIM_GET_COUNTER(&htim4);

	if(end < start)
	{
		return ((0xFFFF + end) - start);
	}

	return (end - start);
}
