/*
 * SysTick.h
 *
 *  Created on: May 6, 2022
 *      Author: Mahmoud Mohamed Abd El Qader
 */
#include "stm32f4xx.h"

uint16_t sysTickCnt = 0;

void SysTick_Handler(void)
{
	sysTickCnt++;
}

void delayMS(uint16_t delay)
{
	sysTickCnt=0;
	while(sysTickCnt < delay);
}

void configClk(void)
{
	SysTick_Config(SystemCoreClock/10000);
}
