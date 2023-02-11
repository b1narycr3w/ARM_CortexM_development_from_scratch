
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

#include "stm32f4xx.h"
#include "misc.h"
//#include "stm32f4xx_gpio.h"
//#include "stm32f4xx_rcc.h"
//#include "stm32f4xx_usart.h"

#define LED4_PIN  	GPIO_Pin_12
#define BUTTON_PIN  GPIO_Pin_0

#define MY_TIMER_PERIOD_MS		(1000UL / portTICK_PERIOD_MS)

extern uint32_t SystemCoreClock;

static TimerHandle_t myTimer;
static QueueHandle_t myQueue;

typedef enum msg_type_e {
	MSG_TYPE_BUTTON_PRESSED,
	MSG_TYPE_TIMER_TOUT,
} msg_type_t;

typedef struct msg_s {
	msg_type_t type;
	uint32_t data;
} msg_t;

void GPIO_Setup(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = LED4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = BUTTON_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

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

void read_button(void *arg)
{
	msg_t msg;
	uint32_t current;
	uint32_t last = 0;
	msg.type = MSG_TYPE_BUTTON_PRESSED;
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOA, BUTTON_PIN))
		{
			current = xTaskGetTickCount();
			vTaskDelay(100 / portTICK_PERIOD_MS); // wait 100ms

			if(last == 0)
			{
				// First time the button is pressed
				msg.data = current;
			}
			else
			{
				msg.data = current - last;
			}
			last = current;
			BaseType_t ret = xQueueSend(myQueue, &msg, 0);
			if(ret != pdTRUE)
			{
				printf("Error in read_button queue\n");
			}
		}
		else
		{
			vTaskDelay(50 / portTICK_PERIOD_MS); // wait 50ms
		}
	}
}

void send_message(void *arg)
{
	msg_t msg;
	while(1)
	{
		BaseType_t ret = xQueueReceive(myQueue, &msg, portMAX_DELAY);
		if(ret == pdTRUE)
		{
			if(msg.type == MSG_TYPE_BUTTON_PRESSED)
			{
				printf("Button pressed. Time elapsed: %ld\n", msg.data);
			}
			else if(msg.type == MSG_TYPE_TIMER_TOUT)
			{
				printf("Timer time out. Count: %ld\n", msg.data);
			}
		}
	}
}

void myTimer_callback(TimerHandle_t xTimer)
{
	static uint32_t cnt = 0;
	msg_t msg;
	msg.type = MSG_TYPE_TIMER_TOUT;
	msg.data = cnt++;
	GPIO_ToggleBits(GPIOD, LED4_PIN);
	BaseType_t ret = xQueueSend(myQueue, &msg, 0);
	if(ret != pdTRUE)
	{
		printf("Error in read_button queue\n");
	}
}

int main(void)
{
  
  GPIO_Setup();
  USART_Setup();
  NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

  printf("Initialized at %ldHz\r\n", SystemCoreClock);

  myQueue = xQueueCreate(2, sizeof(msg_t));

  xTaskCreate(read_button, "read_button", configMINIMAL_STACK_SIZE, (void *) NULL, tskIDLE_PRIORITY, NULL);
  xTaskCreate(send_message, "send_message", configMINIMAL_STACK_SIZE, (void *) NULL, tskIDLE_PRIORITY, NULL);

  myTimer = xTimerCreate("myTimer", MY_TIMER_PERIOD_MS, pdTRUE, NULL, myTimer_callback);
  xTimerStart(myTimer, 0);

  vTaskStartScheduler();

  return 0;
}
