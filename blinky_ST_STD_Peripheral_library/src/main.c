
#include <stdio.h>
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
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; //This is important. We will this pin except of INPUT, OUTPUT and ANALOG so we set as Alternate Function
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3;   //Communicate on PA2 and PA3
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//We set the pin as Push Pull
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; //And Pull Up. Keep it always on HIGH
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz; //And pin frequency
	GPIO_Init(GPIOA, &GPIO_InitStructure);

  //When we set a pin as Alternate Function, we need to specify what function do we use for, here we specified it as USART 2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);


  USART_InitTypeDef USART_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

  USART_InitStructure.USART_BaudRate 	              = 9600; //Set the baudrate. Hw many datas will be sent in a second.
	USART_InitStructure.USART_HardwareFlowControl     = USART_HardwareFlowControl_None;  //Do not check the data transmitted 
	USART_InitStructure.USART_Mode                    = USART_Mode_Tx | USART_Mode_Rx;//Data tansmission modes
	USART_InitStructure.USART_Parity                  = USART_Parity_No; // USART parity settings
	USART_InitStructure.USART_StopBits                = USART_StopBits_1; //Set the stop bits
	USART_InitStructure.USART_WordLength              = USART_WordLength_8b;  //we will send the 8bit data
	USART_Init(USART2, &USART_InitStructure);   //and started the this configuration

	USART_Cmd(USART2, ENABLE); //USART is activated and ready to use
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

    printf("Test\r\n");
    GPIO_ToggleBits(GPIOD, LED4_PIN);
    delay(500000);
  }
  return 0;
}
