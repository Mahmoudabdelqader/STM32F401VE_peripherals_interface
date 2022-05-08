/*
 * lcd.h
 *
 *  Created on: May 6, 2022
 *      Author: Mahmoud Mohamed Abd El Qader
 */

#ifndef LCD_LCD_H_
#define LCD_LCD_H_
/* includes */
#include <stm32F4xx.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "lcd_alpha_16x2_commands.h"

/* lcd structure */
typedef struct __lcd{
	// Data Bus.
	GPIOMode_TypeDef GPIO_data_MODE;

	GPIOOType_TypeDef GPIO_data_OType;

	GPIOPuPd_TypeDef GPIO_data_PuPd;

	GPIOSpeed_TypeDef GPIO_data_Speed;

	uint32_t data_pins[4];

	uint32_t RCC_AHB1Periph_data;

	GPIO_TypeDef *Data_port;

	// Control Bus.
	GPIOMode_TypeDef GPIO_control_MODE;

	GPIOOType_TypeDef GPIO_control_OType;

	GPIOPuPd_TypeDef GPIO_control_PuPd;

	GPIOSpeed_TypeDef GPIO_control_Speed;

	uint32_t RS, EN;

	uint32_t RCC_AHB1Periph_Control;

	GPIO_TypeDef *Control_port;
}LCD16X2;

void lcd16x2_init(LCD16X2 *plcd);

void lcd16x2_print_char(LCD16X2 *plcd, uint8_t ch);

void lcd16x2_print_string(LCD16X2 *plcd, const char[]);

void lcd16x2_println(LCD16X2 *plcd);

void lcd16x2_clear(LCD16X2 *plcd);

void lcd16x2_goto(LCD16X2 *plcd, uint8_t row, uint8_t column);
#endif /* LCD_LCD_H_ */
