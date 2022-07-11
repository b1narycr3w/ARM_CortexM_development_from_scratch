
#include "stm32f4xx_conf.h"


#define LED4_PIN  GPIO_Pin_12

GPIO_InitTypeDef  GPIO_InitStructure;

void GPIO_Setup(void)
{
  /* GPIOG Peripheral clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PG6 and PG8 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = LED4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

}

void delay(uint32_t cnt)
{
  while(cnt)
    cnt--;
}

int main(void)
{
  GPIO_Setup();

  while(1)
  {

    GPIO_ToggleBits(GPIOD, LED4_PIN);
    delay(100000);
  }
  return 0;
}
