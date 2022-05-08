/*
 * keypad.h
 *
 *  Created on: May 8, 2022
 *      Author: Mahmoud Mohamed Abd El Qader
 */

#ifndef KEYPAD_KEYPAD_H_
#define KEYPAD_KEYPAD_H_
//============= includes ===========
#include <stm32f4xx.h>

//================== KeyMap ====================
const uint8_t keymap[4][3] = {
		{'1', '2', '3'},
		{'4', '5', '6'},
		{'7', '8', '9'},
		{'*', '0', '#'}
};

//=========== Keypad 4X4 structure =============
typedef struct __keypad4x4{
	//*********** Rows **************
	uint32_t Row_RCC;
	uint32_t Rows_pins[4];
	GPIO_TypeDef *Row_PORT;
	GPIO_InitTypeDef Row_GPIO_initTypeDef;

	//*********** Columns ***********
	uint32_t Col_RCC;
	uint32_t Cols_pins[4];
	GPIO_TypeDef *Col_PORT;
	GPIO_InitTypeDef Col_GPIO_initTypeDef;
}Keypad4X4;

//================== init function ====================
void keypad4x4_config(Keypad4X4 *pk);

//================== read function ====================
void keypad4x4_getKey(Keypad4X4 *pk, uint8_t* key);

#endif /* KEYPAD_KEYPAD_H_ */
