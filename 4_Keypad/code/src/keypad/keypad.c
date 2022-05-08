/*
 * keypad.c
 *
 *  Created on: May 8, 2022
 *      Author: Mahmoud Mohamed Abd El Qader
 */
/* includes */
#include "keypad.h"

/* External functions */
extern void delayMS(uint16_t delay);

//================== init function ====================
void keypad4x4_config(Keypad4X4 *pk){
	// A.1.Configure Rows as output pins.
	pk->Row_GPIO_initTypeDef.GPIO_Mode = GPIO_Mode_OUT;
	pk->Row_GPIO_initTypeDef.GPIO_OType = GPIO_OType_PP;
	pk->Row_GPIO_initTypeDef.GPIO_PuPd =  GPIO_PuPd_NOPULL;
	pk->Row_GPIO_initTypeDef.GPIO_Speed = GPIO_Speed_100MHz;


	// A.2.Set Rows Pins.
	pk->Row_GPIO_initTypeDef.GPIO_Pin = pk->Rows_pins[0] | pk->Rows_pins[1] | pk->Rows_pins[2] | pk->Rows_pins[3];

	// A.3.Enable RCC.
	RCC_AHB1PeriphClockCmd(pk->Row_RCC, ENABLE);

	// A.4.initialize ROW_GPIO.
	GPIO_Init(pk->Row_PORT, &pk->Row_GPIO_initTypeDef);

	// B.1.Configure Columns as input pins.
	pk->Col_GPIO_initTypeDef.GPIO_Mode  = GPIO_Mode_IN;		// Input
	pk->Col_GPIO_initTypeDef.GPIO_OType = GPIO_OType_PP;		// Push-Pull
	pk->Col_GPIO_initTypeDef.GPIO_PuPd  = GPIO_PuPd_UP;		// pull-UP
	pk->Col_GPIO_initTypeDef.GPIO_Speed = GPIO_Speed_100MHz; 	// 100 MHZ speed

	// B.2.Set Columns Pins.
	pk->Col_GPIO_initTypeDef.GPIO_Pin = pk->Cols_pins[0] | pk->Cols_pins[1] | pk->Cols_pins[2] | pk->Cols_pins[3];

	// B.3.Enable RCC.
	RCC_AHB1PeriphClockCmd(pk->Col_RCC, ENABLE);

	// B.4.initialize Col_GPIO.
	GPIO_Init(pk->Col_PORT, &pk->Col_GPIO_initTypeDef);
}

//================== read function ====================
void keypad4x4_getKey(Keypad4X4 *pk, uint8_t* key){
	for(uint8_t row=0; row<=3; row++){
		// 1.Deactivate all rows, all rows are High.
		GPIO_SetBits(pk->Row_PORT, pk->Row_GPIO_initTypeDef.GPIO_Pin);

		// 2.Activate one row.
		GPIO_ResetBits(pk->Row_PORT, pk->Rows_pins[row]);

		// 3.Read all columns.
		for(uint8_t col=0; col<=3; col++){
			if(GPIO_ReadInputDataBit(pk->Col_PORT, pk->Cols_pins[col]) == (uint8_t)0){
				*key = keymap[row][col];
				while(GPIO_ReadInputDataBit(pk->Col_PORT, pk->Cols_pins[col]) == (uint8_t)0);
			}

			asm("nop");
		}
	}
}
