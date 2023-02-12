
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "stm32f4xx.h"


#define LED4_PIN  GPIO_Pin_12
#define BUTTON_PIN  GPIO_Pin_0

extern uint32_t SystemCoreClock;

static QueueHandle_t myQueue;
static TimerHandle_t myTimer;

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
			if (last == 0)
			{
				// First time the button is pressed
				msg.data = current;
			}
			else
			{
				msg.data = current - last;
			}
			last = current;
			// push msg to queue
			BaseType_t ret = xQueueSend(myQueue, &msg, 0);
			if (ret != pdTRUE)
			{
				printf("Error in read_button queue\r\n");
			}
		}
	}
}

void send_message(void *arg)
{
	msg_t msg;
	while(1)
	{
		BaseType_t ret = xQueueReceive(myQueue, &msg, portMAX_DELAY);
		if (ret == pdTRUE)
		{
			if (msg.type == MSG_TYPE_BUTTON_PRESSED)
			{
				printf("Button pressed. Ticks elapsed: %ld\r\n", msg.data);
			}
			else if (msg.type == MSG_TYPE_TIMER_TOUT)
			{
				printf("Timer time out. Count: %ld\r\n", msg.data);
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
	// push msg to queue
	BaseType_t ret = xQueueSend(myQueue, &msg, 0);
	if (ret != pdTRUE)
	{
		printf("Error in myTimer_callback queue\r\n");
	}
}

int main(void)
{
  
  GPIO_Setup();
  USART_Setup();

  printf("Initialized at %ldHz\r\n", SystemCoreClock);

  // Create tasks
  xTaskCreate(read_button, "read_button", 512, NULL, tskIDLE_PRIORITY,NULL);
  xTaskCreate(send_message, "send_message", 512, NULL, tskIDLE_PRIORITY,NULL);

  // Create queue
  myQueue = xQueueCreate(2, sizeof(msg_t));

  // Create timer
  myTimer = xTimerCreate("myTimer", pdMS_TO_TICKS(1000), pdTRUE, NULL, myTimer_callback);
  xTimerStart(myTimer, 0);

  vTaskStartScheduler();

  return 0;
}
