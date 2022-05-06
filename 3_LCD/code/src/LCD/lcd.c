/*
 * lcd.c
 *
 *  Created on: May 6, 2022
 *      Author: Mahmoud Mohamed Abd El Qader
 */
/* includes */
#include "lcd.h"

extern void delayMS(uint16_t delay);

/* Static Variables */
//static uint8_t line = 0;

/* Static functions */
//================== Enable Pulse ==================
static void EnablePulse(LCD16X2 *plcd){
	GPIO_SetBits(plcd->Control_port, plcd->EN);
	delayMS(1);
	GPIO_ResetBits(plcd->Control_port, plcd->EN);
	delayMS(1);
}
//================== Send Command ==================
static void Send_Command(LCD16X2 *plcd, uint8_t command){
	// send upper nibble of command.
	// 1.select command register {RS=0}.
	GPIO_ResetBits(plcd->Control_port, plcd->RS);

	// 2.send upper bits.
	for(uint8_t i=4; i<=7; i++){
		if( ((command&(1<<i))>>i) == (uint8_t)1 ){
			GPIO_SetBits(plcd->Data_port, plcd->data_pins[i-4]);
		}
		else{
			GPIO_ResetBits(plcd->Data_port, plcd->data_pins[i-4]);
		}
		asm("nop");
	}

	// 3.Enable Pulse.
	EnablePulse(plcd);

	// send Lower nibble of command.
	// 1.send upper bits.
	for(uint8_t i=0; i<=3; i++){
		if( ((command&(1<<i))>>i) == (uint8_t)1 ){
			GPIO_SetBits(plcd->Data_port, plcd->data_pins[i]);
		}
		else{
			GPIO_ResetBits(plcd->Data_port, plcd->data_pins[i]);
		}
		asm("nop");
	}

	// 2.Enable Pulse.
	EnablePulse(plcd);
}

//======================== Init function ===================
void lcd16x2_init(LCD16X2 *plcd){
	GPIO_InitTypeDef gpio_data, gpio_control;

	//========= init data ===============
	gpio_data.GPIO_Mode   = plcd->GPIO_data_MODE;
	gpio_data.GPIO_OType  = plcd->GPIO_data_OType;
	gpio_data.GPIO_PuPd   = plcd->GPIO_data_PuPd;
	gpio_data.GPIO_Speed  = plcd->GPIO_data_Speed;
	gpio_data.GPIO_Pin = plcd->data_pins[0] | plcd->data_pins[1] |plcd->data_pins[2] | plcd->data_pins[3];

	RCC_AHB1PeriphClockCmd(plcd->RCC_AHB1Periph_data, ENABLE);
	GPIO_Init(plcd->Data_port, &gpio_data);

	//======== init control ==================
	gpio_control.GPIO_Mode   = plcd->GPIO_control_MODE;
	gpio_control.GPIO_OType  = plcd->GPIO_control_OType;
	gpio_control.GPIO_PuPd   = plcd->GPIO_control_PuPd;
	gpio_control.GPIO_Speed  = plcd->GPIO_control_Speed;
	gpio_control.GPIO_Pin = plcd->RS | plcd->EN;

	RCC_AHB1PeriphClockCmd(plcd->RCC_AHB1Periph_Control, ENABLE);
	GPIO_Init(plcd->Control_port, &gpio_control);

	//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

	delayMS(20); //LCD Power ON delay always > 15 ms.

	// *********** Send 4 bit mode command ***************
	Send_Command(plcd, __init__);
	delayMS(1);

	// *********** Send lines and dots command ***********
	Send_Command(plcd, _4_bits_2_lines_5x8_dots);
	delayMS(1);

	// ********** Send display and cursor command ********
	Send_Command(plcd, _display_on_cursor_blinking);
	delayMS(1);

	// ********** Send cursor direction command **********
	Send_Command(plcd, _increment_cursor);
	delayMS(1);

	// ********** Send Clear command *********************
	Send_Command(plcd, _clear_display);
	delayMS(1);
}

//============== print one character =================
void lcd16x2_print_char(LCD16X2 *plcd, uint8_t ch){
	// send upper nibble of character.
	// 1.select command register {RS=1}.
	GPIO_SetBits(plcd->Control_port, plcd->RS);

	// 2.send upper bits.
	for(uint8_t i=4; i<=7; i++){
		if( ((ch&(1<<i))>>i) == (uint8_t)1 ){
			GPIO_SetBits(plcd->Data_port, plcd->data_pins[i-4]);
		}
		else{
			GPIO_ResetBits(plcd->Data_port, plcd->data_pins[i-4]);
		}
		//asm("nop");
	}

	// 3.Enable Pulse.
	EnablePulse(plcd);

	// send Lower nibble of command.
	// 1.send upper bits.
	for(uint8_t i=0; i<=3; i++){
		if( ((ch&(1<<i))>>i) == (uint8_t)1 ){
			GPIO_SetBits(plcd->Data_port, plcd->data_pins[i]);
		}
		else{
			GPIO_ResetBits(plcd->Data_port, plcd->data_pins[i]);
		}
		//asm("nop");
	}

	// 2.Enable Pulse.
	EnablePulse(plcd);
}

//================= print string ========================
void lcd16x2_print_string(LCD16X2 *plcd, const char str[]){
	for(uint8_t i=0; i<strlen(str); i++){
		if(i<16){
			lcd16x2_print_char(plcd, str[i]);
		}
		else{
			lcd16x2_goto(plcd, 1, i-16);
			lcd16x2_print_char(plcd, str[i]);
		}

	}

}

//=============== print new line ============
//void lcd16x2_println(LCD16X2 *plcd){
//	//lcd16x2_print_char(plcd, '\n');
//	lcd16x2_print_char(plcd, '\r');
//}

//========== Clear ==============
void lcd16x2_clear(LCD16X2 *plcd){
	Send_Command(plcd, _clear_display);
}

//============ change position ================
void lcd16x2_goto(LCD16X2 *plcd, uint8_t row, uint8_t column){
	if (row == 0 && column<16)
		/* Command of first row and required position<16 */
		Send_Command(plcd, (column & 0x0F)|_force_cusror_to_start_with_1st_row);
	/* Command of second row and required position<16 */
	else if (row == 1 && column<16)
		Send_Command(plcd, (column & 0x0F)|_force_cusror_to_start_with_2nd_row);
}
