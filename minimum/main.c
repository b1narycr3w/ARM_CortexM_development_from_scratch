
#include <stdint.h>

#define RCC_AHB1ENR (*(uint32_t *)0x40023830UL)
#define GPIOD_MODER (*(uint32_t *)0x40020C00UL)
#define GPIOD_ODR (*(uint32_t *)0x40020C14UL)

void delay(uint32_t cnt)
{
  while(cnt--);
}

int main(void)
{

  RCC_AHB1ENR |= 0x08;
  GPIOD_MODER &= ~(0x03 << (12 * 2));
  GPIOD_MODER |= (0x01 << (12 * 2));

  while(1)
  {
    GPIOD_ODR ^= (1 << 12);
    delay(1000000);
  }
  return 0;
}
