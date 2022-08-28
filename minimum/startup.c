
#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);

void Default_Handler(void)
{
    while(1);
}

//void __attribute__((naked)) Reset_Handler(void)
void Reset_Handler(void)
{

//  __asm__ __volatile__ ("ldr r0,=_estack");    
//  __asm__ __volatile__ ("mov sp, r0");    

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

  main();

  while(1);
}


uint32_t vector_table[] __attribute__ ((section(".isr_vector"))) =
{
  (uint32_t)&_estack,
  (uint32_t)&Reset_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  0,
  0,
  0,
  0,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  0,
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
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler,
  0,
  (uint32_t)&Default_Handler,
  (uint32_t)&Default_Handler

};


