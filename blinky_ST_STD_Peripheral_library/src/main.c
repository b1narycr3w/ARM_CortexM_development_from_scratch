
#include <stdio.h>
#include <unistd.h>
#include "stm32f4xx.h"
//#include "stm32f4xx_conf.h"

#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define LED4_PIN  GPIO_Pin_12



void GPIO_Setup(void)
{

  GPIO_InitTypeDef  GPIO_InitStructure;

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

void USART_Setup(void)
{

  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  //Configuration of the GPIO pin for communication
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; // Pull Up. Keep it always on HIGH
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);

  //When we set a pin as Alternate Function, we need to specify what function do we use for, here we specified it as USART 2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);


  USART_InitTypeDef USART_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

  USART_InitStructure.USART_BaudRate 	              = 9600; 
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

  char buf[64];
  while(1)
  {

    int cnt = read(STDIN_FILENO, buf, sizeof(buf));
    if(cnt > 0)
    {
      buf[cnt] = '\0';
      printf("\r\n%s\r\n", buf);
    }
    else
    {
      printf("Error\r\n");
    }
    GPIO_ToggleBits(GPIOD, LED4_PIN);
    delay(500000);
  }
  return 0;
}
