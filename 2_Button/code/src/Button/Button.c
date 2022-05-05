/*
 * Button.c
 *
 *  Created on: May 5, 2022
 *      Author: Mahmoud Mohamed Abd El Qader
 */
// includes
#include "Button.h"

void btn_config(Button *pb){
	GPIO_InitTypeDef gpio;

	RCC_AHB1PeriphClockCmd(pb->RCC_AHB1Periph, ENABLE);


	gpio.GPIO_Mode = pb->GPIO_Mode;


	gpio.GPIO_OType = pb->GPIO_OType;


	gpio.GPIO_Pin = pb->GPIO_PIN;


	gpio.GPIO_PuPd = pb->GPIO_PUPD;


	gpio.GPIO_Speed = pb->GPIO_Speed;


	GPIO_Init(pb->PORT, &gpio);

}


uint8_t btn_read(Button *pb){
	return GPIO_ReadInputDataBit(pb->PORT, (uint16_t)pb->GPIO_PIN);
}


void btn_click_to_toggle_pin(Button *pb, LED *ppin){
	if(btn_read(pb) == (uint8_t)Bit_RESET){
		if(pb->state == (uint8_t)0){
			GPIO_ToggleBits(ppin->PORT, (uint16_t)ppin->GPIO_Pin);
			pb->state = (uint8_t)1;
			asm("nop");
		}
	}
	else if(btn_read(pb) == (uint8_t)Bit_SET){
		pb->state = 0;
	}
}
