#include <stdint.h>
#include "stm32f4xx.h"
#include "delay.h"
#include "main.h"
#include "cmsis_compiler.h"
#define GPIO_C *((volatile uint32_t*) 0x40020818u)//bsrrgpioc
#define LED_PC13_ALIAS *((volatile uint32_t*) 0x424102B4u) /*
Alias_Address = Alias_Base + (Peripheral_Offset x 32) + (Bit_Number x 4)
Target Register: GPIOC Base (0x40020800) + ODR Offset (0x14) = 0x40020814
Peripheral Offset: Target (0x40020814) - Peripheral Base (0x40000000) = 0x20814
Bit Number: 13 */
volatile uint32_t utick;
void SysTick_Handler (void);
void SysTick_Handler (){
	++utick ;
}


uint32_t* swap (uint32_t* x, uint32_t* y);//prototype
uint32_t* swap (uint32_t* x, uint32_t* y){
	static uint32_t temp [2];
	temp[0] = *y;
	temp[1]= *x;
	return temp;// swap is called once i have checked for shared resource race conditions

}


int main(void) {
	SystemClock_Config();// hse , clock config



volatile uint32_t ca = 9;
volatile int8_t doofus = -10;
volatile uint32_t result = ca + doofus ;


if (doofus>0u && result>ca )// true
{

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;//= 0x00000004u ;// clock enable bit2->portc
	*((volatile uint32_t*) 0x40020800u) &= ~(3<<26) ;// clear 26th and 27th bit
	*((volatile uint32_t*) 0x40020800u) |= (1<<26) ; //moder26thbit>>
	//2^26=0x04000000 01=write
	SystemCoreClockUpdate();
	SysTick->LOAD = (SystemCoreClock/1000 -1 );
	SysTick->VAL = 67467 ; // write anything it will reset


 typedef enum {
     Led_on,
     led_off
 } led_current;



     uint32_t bright[2];
     bright[0] = 400;
     bright[1] = 1200;

     uint32_t last_tick = utick;
     led_current state = Led_on;
     GPIO_C = (1 << 29);             // Turn LED ON (Active-Low)
     SysTick->CTRL= 7u ; // 7 = 111 in binary used to set bit 0,1 and 2
     while(1) {
         switch(state) {
             case Led_on: // check on
                 if (delay(bright[0] + 300, last_tick)) {
                     LED_PC13_ALIAS = 1;
                     last_tick = utick;
                     state = led_off;
                 }
                 break;

             case led_off: // Check if the OFF duration has elapsed
                 if (delay(bright[1] + 300, last_tick)) {
                     GPIO_C = (1 << 29);
                     last_tick = utick;             // Swap
                     uint32_t* temp = swap(&bright[0], &bright[1]);
                     bright[0] = temp[0];
                     bright[1] = temp[1];

                     state = Led_on;
                 }
                 break;
         }
     }
     return 0;
 }

    return 0; }

void SystemClock_Config(void)
{LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	  LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);
	  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_3)
	  {
	  }
	  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	  LL_RCC_HSE_Enable();

	   /* Wait till HSE is ready */
	  while(LL_RCC_HSE_IsReady() != 1)
	  {

	  }
	  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 200, LL_RCC_PLLP_DIV_2);
	  LL_RCC_PLL_Enable();

	   /* Wait till PLL is ready */
	  while(LL_RCC_PLL_IsReady() != 1)
	  {

	  }
	  while (LL_PWR_IsActiveFlag_VOS() == 0)
	  {
	  }
	  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
	  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
	  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

	   /* Wait till System clock is ready */
	  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	  {

	  }
	  LL_SetSystemCoreClock(100000000);

	   /* Update the time base */
	  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
	  {
	  while(1) {}
	  }
	  LL_RCC_SetTIMPrescaler(LL_RCC_TIM_PRESCALER_TWICE);
}
