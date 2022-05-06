/* Includes */
#include "stm32f4xx.h"
#include "SysTick.h"
#include "led/led.h"
#include "Button/Button.h"
#include "LCD/lcd.h"

int main(void){

	// configure the clock of the system to generate delay.
	configClk();

	// lcd 16x2 object.
	LCD16X2 lcd;

	/* Initialize Data and control pins as output pins. */
	/*
	 * lcd pins are connected to PORTB PB0, PB1, PB2, PB3
	 *
	 * output type, NO pull-up/down, 100 MHZ speed, Push-Pull type
	 * */
	//========= Data ============
	lcd.GPIO_data_MODE  = GPIO_Mode_OUT;
	lcd.GPIO_data_OType = GPIO_OType_PP;
	lcd.GPIO_data_PuPd  = GPIO_PuPd_NOPULL;
	lcd.GPIO_data_Speed = GPIO_Speed_100MHz;
	lcd.Data_port = GPIOB;
	lcd.data_pins[0] = GPIO_Pin_6;
	lcd.data_pins[1] = GPIO_Pin_7;
	lcd.data_pins[2] = GPIO_Pin_8;
	lcd.data_pins[3] = GPIO_Pin_9;
	lcd.RCC_AHB1Periph_data = RCC_AHB1Periph_GPIOB;

	//=========== Control =================
	lcd.GPIO_control_MODE  = GPIO_Mode_OUT;
	lcd.GPIO_control_OType = GPIO_OType_PP;
	lcd.GPIO_control_PuPd  = GPIO_PuPd_NOPULL;
	lcd.GPIO_control_Speed = GPIO_Speed_100MHz;
	lcd.Control_port = GPIOD;
	lcd.EN = GPIO_Pin_9;
	lcd.RS = GPIO_Pin_10;
	lcd.RCC_AHB1Periph_Control = RCC_AHB1Periph_GPIOD;

	// init lcd
	lcd16x2_init(&lcd);
	lcd16x2_print_string(&lcd, (const char*)"Hello World, Mahmoud Younis");

  while (1)
  {
	  // delay
	  delayMS(100);
  }
}
