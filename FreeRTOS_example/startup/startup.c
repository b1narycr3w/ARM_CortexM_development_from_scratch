
#include <stdint.h>
#include "system_stm32f4xx.h"

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);

void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void Default_Handler(void)
{
    while(1);
}

void Reset_Handler(void)
{

  uint32_t *psrc = &_sidata;
  uint32_t *pdst = &_sdata;

  while(pdst < &_edata)
  {
    *pdst = *psrc;
    ++psrc;
    ++pdst;
  }

  pdst = &_sbss;
  while(pdst < &_ebss)
  {
    *pdst = 0;
    ++pdst;
  }

  SystemInit();

  main();

  while(1);
}


uint32_t vector_table[] __attribute__ ((section(".isr_vector"))) =
{
  (uint32_t)&_estack,
  (uint32_t)&Reset_Handler,
  (uint32_t)&Default_Handler, //NMI
  (uint32_t)&Default_Handler, // Hard fault
  (uint32_t)&Default_Handler, // memManage
  (uint32_t)&Default_Handler, // BusFault
  (uint32_t)&Default_Handler, // UsageFault
  0,
  0,
  0,
  0,
  (uint32_t)&SVC_Handler,		// SVCall
  (uint32_t)&Default_Handler,	// Debug Monitor
  0,
  (uint32_t)&PendSV_Handler,	// PendSV
  (uint32_t)&SysTick_Handler,	// Systick
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  0,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler

};

__attribute__((__weak__)) void  SVC_Handler(void)
{
	Default_Handler();
}
__attribute__((__weak__)) void  PendSV_Handler(void)
{
	Default_Handler();
}
__attribute__((__weak__)) void  SysTick_Handler(void)
{
	Default_Handler();
}

