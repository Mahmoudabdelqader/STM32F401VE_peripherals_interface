/*
 * led.h
 *
 *  Created on: May 4, 2022
 *      Author: Mahmoud Mohamed Abd El Qader
 */

#ifndef LED_LED_H_
#define LED_LED_H_
/* includes */
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"


typedef struct __led{

	  uint32_t GPIO_Pin;


	  GPIOMode_TypeDef GPIO_Mode;


	  GPIOSpeed_TypeDef GPIO_Speed;


	  GPIOOType_TypeDef GPIO_OType;


	  GPIOPuPd_TypeDef GPIO_PuPd;


	  uint32_t RCC_AHB1Periph;


	  GPIO_TypeDef *PORT;

}LED;

void led_config(LED *pl);

void led_turn_on(LED *pl);

void led_turn_off(LED *pl);

void led_toggle(LED *pl);

#endif /* LED_LED_H_ */
