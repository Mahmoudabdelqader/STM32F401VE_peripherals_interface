/*
 * Button.h
 *
 *  Created on: May 5, 2022
 *      Author: Mahmoud Mohamed Abd El Qader
 */

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_
// =========== includes ===============
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "led/led.h"

// =========== Button struct ============
typedef struct __button{

	uint32_t GPIO_PIN;

	GPIOMode_TypeDef GPIO_Mode;

	GPIOSpeed_TypeDef GPIO_Speed;

	GPIOOType_TypeDef GPIO_OType;

	GPIOPuPd_TypeDef GPIO_PUPD;

	uint32_t RCC_AHB1Periph;

	GPIO_TypeDef *PORT;

	uint8_t state;

}Button;

// =========== functions =============
void btn_config(Button *pb);

uint8_t btn_read(Button *pb);

void btn_click_to_toggle_pin(Button *pb, LED *ppin);

#endif /* BUTTON_BUTTON_H_ */
