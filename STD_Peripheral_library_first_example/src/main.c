
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"

#define LED4_PIN  GPIO_Pin_12

void GPIO_Setup(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  GPIO_InitStructure.GPIO_Pin = LED4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void USART_Setup(void)
{

  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; // Pull Up. Keep it always on HIGH
  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);


  USART_InitTypeDef USART_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

  USART_InitStructure.USART_BaudRate 	            = 9600; 
  USART_InitStructure.USART_HardwareFlowControl     = USART_HardwareFlowControl_None;  
  USART_InitStructure.USART_Mode                    = USART_Mode_Tx | USART_Mode_Rx;
  USART_InitStructure.USART_Parity                  = USART_Parity_No; 
  USART_InitStructure.USART_StopBits                = USART_StopBits_1; 
  USART_InitStructure.USART_WordLength              = USART_WordLength_8b; 
  USART_Init(USART2, &USART_InitStructure);   

  USART_Cmd(USART2, ENABLE); 
}
void delay(uint32_t cnt)
{
  while(cnt)
    cnt--;
}

int main(void)
{
  
  GPIO_Setup();
  USART_Setup();

  while(1)
  {
    printf("Hello World!\r\n");
    // Toggle LED
    GPIO_ToggleBits(GPIOD, LED4_PIN);
    delay(500000);
  }
  return 0;
}
