/* Includes */
#include "stm32f4xx.h"
#include "led/led.h"
#include "Button/Button.h"

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

int main(void){

	// configure the clock of the system to generate delay.
	configClk();

	// Configure LED#1
	LED led1;
	led1.GPIO_Mode = GPIO_Mode_OUT;
	led1.GPIO_Pin = GPIO_Pin_12;
	led1.GPIO_OType = GPIO_OType_PP;
	led1.GPIO_PuPd = GPIO_PuPd_NOPULL;
	led1.GPIO_Speed = GPIO_Speed_100MHz;
	led1.RCC_AHB1Periph = RCC_AHB1Periph_GPIOD;
	led1.PORT = GPIOD;

	led_config(&led1);

	//=================================================

	// Configure LED#2
	LED led2;
	led2.GPIO_Mode = GPIO_Mode_OUT;
	led2.GPIO_Pin = GPIO_Pin_5;
	led2.GPIO_OType = GPIO_OType_PP;
	led2.GPIO_PuPd = GPIO_PuPd_NOPULL;
	led2.GPIO_Speed = GPIO_Speed_100MHz;
	led2.RCC_AHB1Periph = RCC_AHB1Periph_GPIOE;
	led2.PORT = GPIOE;

	led_config(&led2);

	//==================================================

	// Configure Button.
	Button btn;
	btn.GPIO_Mode = GPIO_Mode_IN;
	btn.GPIO_PIN = GPIO_Pin_0;
	btn.GPIO_OType = GPIO_OType_PP;
	btn.GPIO_PUPD = GPIO_PuPd_UP;
	btn.GPIO_Speed = GPIO_Speed_100MHz;
	btn.RCC_AHB1Periph = RCC_AHB1Periph_GPIOD;
	btn.PORT = GPIOD;
	btn.state = (uint8_t) 0;

	btn_config(&btn);

  while (1)
  {
	  // toggle led2 continuously.
	  led_toggle(&led2);

	  // toggle led1 if the button pressed.
	  btn_click_to_toggle_pin(&btn, &led1);

	  // delay
	  delayMS(100);
  }
}
