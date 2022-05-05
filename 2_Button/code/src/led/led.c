/*
 * led.c
 *
 *  Created on: May 4, 2022
 *      Author: Mahmoud Mohamed Abd El Qader
 */
/* includes */
#include "led.h"
void led_config(LED *pl){

	RCC_AHB1PeriphClockCmd(pl->RCC_AHB1Periph, ENABLE);

	GPIO_InitTypeDef gpio;

	gpio.GPIO_Mode = pl->GPIO_Mode;

	gpio.GPIO_OType = pl->GPIO_OType;

	gpio.GPIO_Pin = pl->GPIO_Pin;

	gpio.GPIO_PuPd = pl->GPIO_PuPd;

	gpio.GPIO_Speed = pl->GPIO_Speed;

	GPIO_Init(pl->PORT, &gpio);
}

void led_turn_on(LED *pl){
	GPIO_SetBits(pl->PORT, pl->GPIO_Pin);
}

void led_turn_off(LED *pl){
	GPIO_ResetBits(pl->PORT, pl->GPIO_Pin);
}

void led_toggle(LED *pl){
	GPIO_ToggleBits(pl->PORT, pl->GPIO_Pin);
}

