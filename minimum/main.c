
#include <stdint.h>

#define RCC_AHB1ENR (*(uint32_t *)0x40023830UL)
#define GPIOD_MODER (*(uint32_t *)0x40020C00UL)
#define GPIOD_ODR (*(uint32_t *)0x40020C14UL)


uint8_t buff[32];
uint8_t my_init_data = 37;

void delay(uint32_t cnt)
{
  while(cnt--);
}

int main(void)
{

 // uint8_t myvar[300] = {0};

  // Enable GPIOD clock
  RCC_AHB1ENR |= 0x08;

  // Set GPIOD Pin12 as output
  GPIOD_MODER &= ~(0x03 << (12 * 2));
  GPIOD_MODER |= (0x01 << (12 * 2));

  // (The rest of the GPIO configurations
  // are ok as default values)

  while(1)
  {
    // Toogle GPIOD pin12 (green LED)
    GPIOD_ODR ^= (1 << 12);
    delay(1000000);
  }
  return 0;
}
