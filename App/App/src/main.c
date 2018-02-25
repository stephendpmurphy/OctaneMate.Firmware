//FreeRTOS Headers
#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>
#include <queue.h>
//Project Headers
#include <main.h>
#include <pins.h>
#include <driver_init.h>
#include <UI_task.h>

#define TASK_UI_STACK_SIZE (128 / sizeof(portSTACK_TYPE))
#define TASK_UISender_STACK_SIZE (128 / sizeof(portSTACK_TYPE))
#define TASK_UI_STACK_PRIORITY (tskIDLE_PRIORITY + 1)
#define TASK_UISender_STACK_PRIORITY (tskIDLE_PRIORITY + 2)

static TaskHandle_t xUI_Task;
static TaskHandle_t xUISender_Task;
QueueHandle_t xUI_Queue;

static void _task_UI(void *p);
static void _task_UI_Sender(void *p);

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	system_init();

	if (xTaskCreate(_task_UI, "UI Task", TASK_UI_STACK_SIZE, NULL, TASK_UI_STACK_PRIORITY, xUI_Task) != pdPASS) {
		while (1) {;}
	}
	
	if (xTaskCreate(_task_UI_Sender, "UI Sender Task", TASK_UISender_STACK_SIZE, NULL, TASK_UISender_STACK_PRIORITY, xUISender_Task) != pdPASS) {
		while (1) {;}
	}
	
	xUI_Queue = xQueueCreate(5, sizeof(UI_LED_STATE_t));

	vTaskStartScheduler();
}

static void _task_UI(void *p)
{
	(void)p;
	task_UI();
	//Should never return
	while(1){;}
}

static void _task_UI_Sender(void *p)
{
	(void)p;
	TickType_t xBlockTime = 5/portTICK_PERIOD_MS;
	UI_LED_STATE_t state = UI_FAST_FLASH;
	for(;;)
	{
		for(UI_LED_STATE_t x = UI_OFF; x <= UI_SLOW_FLASH; x++)
		{	
			state = x;
			xQueueSend( xUI_Queue, ( void * ) &state, xBlockTime );
			vTaskDelay(5000/portTICK_PERIOD_MS);
		}
	}
}
