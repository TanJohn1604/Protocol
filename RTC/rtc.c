#include "stm32f4xx.h" 

typedef struct{
  uint8_t Hours;           
  uint8_t Minutes;         
  uint8_t Seconds;         
	
}RTC_TimeTypeDef;


typedef struct{
	uint8_t Day;
  uint8_t Month;     
  uint8_t Year;  
	
}RTC_DateTypeDef;


	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;

void RTC_Init(unsigned char h,unsigned char m,unsigned char s,
							unsigned char day,unsigned char month,unsigned char year){

	RCC->APB1ENR |= RCC_APB1ENR_PWREN;					//enable peripheral clock power
	PWR->CR |= PWR_CR_DBP;											//enable access to the RTC registers - 17.3.5 RTC register write protection
	///17.3.1 Clock and prescalers. chon LSI 
	RCC->CSR |= RCC_CSR_LSION;									//enable LSI - 6.3.18 RCC clock control & status register
	while(!(RCC->CSR & RCC_CSR_LSIRDY));				//wait for LSI ready flag - 6.3.18 RCC clock control & status register
	
	//6.3.17 
	//Bits 9:8 RTCSEL[1:0]: RTC clock source selection
	//Bit 15 RTCEN: RTC clock enable
	RCC->BDCR |= 0x8200;												//select LSI and enable RTC 
	//17.3.5 
	//RTC register write protection
	RTC->WPR |= 0xCA;														//enter key to unlock write protection
	RTC->WPR |=	0x53;
	//17.3.5 
	//Calendar initialization and configuration
	RTC->ISR |= RTC_ISR_INIT;
	while(!(RTC->ISR & RTC_ISR_INITF));					//wait for RTC init ready flag
	//first
	//15-bit synchronous prescaler configured through the PREDIV_S
	RTC->PRER |=0xF9;//32000Hz / (249+1) = 128
	
	//second
	//7-bit asynchronous prescaler configured through the PREDIV_A
	RTC->PRER |=0x7F<<16;//128 /(127 +1 ) =1Hz
	
	//Calendar initialization and configuration
	// Load the initial time and date values in the shadow registers (RTC_TR and RTC_DR),
	//and configure the time format (12 or 24 hours) through the FMT bit in the RTC_CR
	//register.
	
	RTC->TR &=~ RTC_TR_PM;//24hour format
	RTC->TR = 0;
	RTC->TR |= h<<16 | m<<8 | s; 					//set time

  RTC->DR = 0;
	RTC->DR |= year<<16 | month<<8 | day ;//set date
	
	//1: Calendar values (when reading from RTC_SSR, RTC_TR, and RTC_DR) are taken
	//directly from the calendar counters.
	RTC->CR |= RTC_CR_BYPSHAD;
	
	//Exit the initialization mode by clearing the INIT bit.
	RTC->ISR &= ~RTC_ISR_INIT;			//clear init bit
	// disable access to RTC registers
	PWR->CR &= ~PWR_CR_DBP;					

}


void RTC_get_time (void){
	
	sTime.Seconds=(((RTC->TR & 0x7f) >> 4)*10)+(RTC->TR & 0xf);
	sTime.Minutes=((RTC->TR & 0x7f00) >> 8);
	sTime.Minutes=(((sTime.Minutes & 0x7f)>>4)*10)+(sTime.Minutes & 0xf);
	sTime.Hours=((RTC->TR & 0x7f0000) >> 16);
	sTime.Hours=(((sTime.Hours & 0x7f)>>4)*10)+(sTime.Hours & 0xf);

}

void RTC_get_date(void){

	sDate.Year=((RTC->DR >> 20)*10) + ((RTC->DR >>16) & 0xf);
	sDate.Month=((RTC->DR >> 12) & 1)*10 + ((RTC->DR >>8) & 0xf);
	sDate.Day=((RTC->DR >> 4) & 3)*10 + (RTC->DR & 0xf);

}

