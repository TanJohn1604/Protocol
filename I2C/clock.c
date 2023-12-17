#include "clock.h"
void SysClockConfig (void)
{
// 1. ENABLE HSE and wait for the HSE to become Ready
RCC->CR |= RCC_CR_HSEON;  // RCC->CR |= 1<<16; 
while (!(RCC->CR & RCC_CR_HSERDY));  // while (!(RCC->CR & (1<<17)));

// 2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
RCC->APB1ENR |= RCC_APB1ENR_PWREN;  // RCC->APB1ENR |= 1<<28;
PWR->CR |= PWR_CR_VOS;  // PWR->CR |= 3<<14; 

//RCC->CFGR |= RCC_CFGR_HPRE_DIV8;
//8Mhz
// 3. Select the Clock Source and wait for it to be set
RCC->CFGR |= RCC_CFGR_SW_HSE;  
while ((RCC->CFGR & RCC_CFGR_SWS_HSE) != RCC_CFGR_SWS_HSE);

}


void GPIO_Config (void)
{
	/************ STEPS FOLLOWED ***********
	1. Enable the GPIO CLOCK
	2. Set the Pin as OUTPUT
	3. Configure the OUTPUT MODE
	***************************************/
       
	// 1. Enable the GPIO CLOCK
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	
	// 2. Set the Pin as OUTPUT
	GPIOD->MODER |= GPIO_MODER_MODER12_0;	
	GPIOD->MODER |= GPIO_MODER_MODER13_0;	
	GPIOD->MODER |= GPIO_MODER_MODER14_0;	
	GPIOD->MODER |= GPIO_MODER_MODER15_0;	
	
	GPIOD->MODER |= GPIO_MODER_MODER7_0;	
	

	// 3. Configure the OUTPUT MODE
	GPIOD->OTYPER = 0;
	GPIOD->OSPEEDR = 0;

	
// 4.1 Set the PA0 as INPUT
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

GPIOA->MODER &= ~GPIO_MODER_MODER0;	
//pull DOWN
GPIOA->PUPDR &=~GPIO_PUPDR_PUPD0_0;
GPIOA->PUPDR |= GPIO_PUPDR_PUPD0_1;
GPIOA->OTYPER = 0;
	

	
	
}
void TIM2_Config (void)
{
RCC->APB1ENR |=RCC_APB1ENR_TIM2EN;
TIM2->ARR =0xffffffff-1;
TIM2->PSC =8-1;
TIM2->CNT = 0;
TIM2->CR1 |= TIM_CR1_CEN;
TIM2->EGR |= TIM_EGR_UG;
while(!(TIM2->SR & TIM_SR_UIF));
TIM2->SR = 0;

}

void delay_us(unsigned int us ){
	TIM2->CNT=0;
	while(TIM2->CNT <us);

}
void delay_ms(unsigned int ms){

	for (uint16_t i=0; i<ms ;i++){
		delay_us(1000);
	}
}




