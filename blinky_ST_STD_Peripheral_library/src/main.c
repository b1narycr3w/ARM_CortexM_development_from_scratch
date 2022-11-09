
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "stm32f4xx.h"
//#include "stm32f4xx_conf.h"

#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define LED4_PIN  GPIO_Pin_12

// LIBC SYSCALLS
/////////////////////

extern int _end;

void *_sbrk(int incr) {
  static unsigned char *heap = NULL;
  unsigned char *prev_heap;

  if (heap == NULL) {
    heap = (unsigned char *)&_end;
  }
  prev_heap = heap;

  heap += incr;

  return prev_heap;
}

int _close(int file) {
  return -1;
}

int _fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;

  return 0;
}

int _isatty(int file) {
  return 1;
}

int _lseek(int file, int ptr, int dir) {
  return 0;
}

void _exit(int status) {
  //__asm("BKPT #0");
  while(1);
}

void _kill(int pid, int sig) {
  return;
}


int _getpid(void) {
  return -1;
}

int _write (int file, char * ptr, int len) {
  int written = 0;

  if ((file != 1) && (file != 2) && (file != 3)) {
    return -1;
  }

  for (; len != 0; --len) {
    while(!(USART2->SR & 0x00000040));
    USART_SendData(USART2, (uint16_t) *ptr++);
    ++written;
  }
  return written;
}

int _read (int file, char * ptr, int len) {
  int read = 0;

  if (file != 0) {
    return -1;
  }

  for (; len > 0; --len) {
    //usart_serial_getchar(&stdio_uart_module, (uint8_t *)ptr++);
    read++;
  }
  return read;
}


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
