#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "portmacro.h"
#include "task.h"

void Delay(int t);
void GPIO_Config(void);

#define STACK_SIZE ( (unsigned short ) 256)
#define PRIORITY ( (unsigned portBASE_TYPE) 2)

/*---------------------------------------------*/
static void vLEDTask1(void *pvParameters);
static void vLEDTask2(void *pvParameters);
static void vLEDTask3(void *pvParameters);
static void vLEDTask4(void *pvParameters);

//-----------------------------------------------//
/* Malloc failed hook */
void vApplicationMallocFailedHook(void)
{
	taskDISABLE_INTERRUPTS();
	for(;;);
}

/* stack overflow hook */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
	(void)xTask;
	(void)pcTaskName;

	taskDISABLE_INTERRUPTS();
	for(;;);
}
//**//

void Delay(int t){
	while(t--);
}
/*--*/
void  GPIO_Config(){
	GPIO_InitTypeDef gpioInit;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);


	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpioInit);

	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInit);

}
int main(void){
	SystemInit();
	GPIO_Config();

	xTaskCreate(vLEDTask1, "LED_PB8", STACK_SIZE, NULL, PRIORITY, NULL);
	xTaskCreate(vLEDTask2, "LED_PB9", STACK_SIZE, NULL, PRIORITY, NULL);
	xTaskCreate(vLEDTask3, "LED_PA9", STACK_SIZE, NULL, PRIORITY, NULL);
	xTaskCreate(vLEDTask4, "LED_PA10", STACK_SIZE, NULL, PRIORITY, NULL);
	vTaskStartScheduler();
	return;

while(1){
	/*	GPIO_SetBits(GPIOB, GPIO_Pin_9);
		Delay(1000000);
		GPIO_ResetBits(GPIOB, GPIO_Pin_9);
		Delay(1000000);*/
	 }
}

static void vLEDTask1(void *pvParameters){
	while(1)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_9);
		vTaskDelay(pdMS_TO_TICKS(200));
		GPIO_ResetBits(GPIOB, GPIO_Pin_9);
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}
static void vLEDTask2(void *pvParameters){
	while(1)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_8);
		vTaskDelay(pdMS_TO_TICKS(400));
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		vTaskDelay(pdMS_TO_TICKS(400));
	}
}

static void vLEDTask3(void *pvParameters){
	while(1)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_9);
		vTaskDelay(pdMS_TO_TICKS(400));
		GPIO_ResetBits(GPIOA, GPIO_Pin_9);
		vTaskDelay(pdMS_TO_TICKS(400));
	}
}

static void vLEDTask4(void *pvParameters){
	while(1)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_10);
		vTaskDelay(pdMS_TO_TICKS(400));
		GPIO_ResetBits(GPIOA, GPIO_Pin_10);
		vTaskDelay(pdMS_TO_TICKS(400));
	}
}

