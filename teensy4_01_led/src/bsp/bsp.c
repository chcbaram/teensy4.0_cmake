#include "bsp.h"





static volatile uint32_t systick_counter = 0;




bool bspInit(void)
{
  BOARD_InitPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();


  SysTick_Config(SystemCoreClock / 1000);
  return true;
}

void delay(uint32_t time_ms)
{
  uint32_t pre_time = systick_counter;

  while(systick_counter-pre_time < time_ms);
}

uint32_t millis(void)
{
  return systick_counter;
}

void SysTick_Handler(void)
{
  systick_counter++;
}

