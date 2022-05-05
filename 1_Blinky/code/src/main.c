/* Includes */
#include "stm32f4xx.h"
#include "led/led.h"

//GPIO_InitTypeDef gpiostr;
uint16_t sysTickCnt = 0;


void SysTick_Handler(void)
{
	sysTickCnt++;
}

void delay_ms(uint16_t delay)
{
	sysTickCnt=0;
	while(sysTickCnt < delay);
}

void configClk(void)
{

//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
//
//	gpiostr.GPIO_Mode = GPIO_Mode_OUT;
//	gpiostr.GPIO_Pin = GPIO_Pin_0;
//	gpiostr.GPIO_OType = GPIO_OType_PP;
//	gpiostr.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	gpiostr.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_Init(GPIOE, &gpiostr);

	SysTick_Config(SystemCoreClock/10000);
}

int main(void){

	configClk();

	LED led1;
	led1.GPIO_Mode = GPIO_Mode_OUT;
	led1.GPIO_Pin = GPIO_Pin_0;
	led1.GPIO_OType = GPIO_OType_PP;
	led1.GPIO_PuPd = GPIO_PuPd_NOPULL;
	led1.GPIO_Speed = GPIO_Speed_100MHz;
	led1.RCC_AHB1Periph = RCC_AHB1Periph_GPIOE;
	led1.PORT = GPIOE;

	led_config(&led1);

	led_turn_on(&led1);

  while (1)
  {
	  led_toggle(&led1);
	  delay_ms(100);
  }
}
