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
#include <BLE_task.h>

static TaskHandle_t xBLE_Task;
static TaskHandle_t xUISender_Task;
static TaskHandle_t xUI_Task;
QueueHandle_t xUI_Queue;

static void _task_UI_Sender(void *p);

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	system_init();
	
	if (xTaskCreate(task_UI, "UI Task", TASK_UI_STACK_SIZE, NULL, TASK_UI_STACK_PRIORITY, xUI_Task) != pdPASS) {
		while (1) {;}
	}

	xUI_Queue = xQueueCreate(5, sizeof(UI_Task_Msg));


	if (xTaskCreate(task_BLE, "BLE Task", TASK_BLE_STACK_SIZE, NULL, TASK_BLE_STACK_PRIORITY, xBLE_Task) != pdPASS) {
		while (1) {;}
	}

	if (xTaskCreate(_task_UI_Sender, "UI Sender Task", TASK_UISender_STACK_SIZE, NULL, TASK_UISender_STACK_PRIORITY, xUISender_Task) != pdPASS) {
		while (1) {;}
	}

	vTaskStartScheduler();
}

static void _task_UI_Sender(void *p)
{
	(void)p;
	TickType_t xBlockTime = 5/portTICK_PERIOD_MS;
	UI_Task_Msg TxMsg;
	TxMsg.led = MCU_LED;
	TxMsg.dur = UI_OFF;
	for(;;)
	{
		TxMsg.dur = UI_FAST_FLASH;
		xQueueSend( xUI_Queue, ( void * ) &TxMsg, xBlockTime );
		vTaskDelay(5000/portTICK_PERIOD_MS);
		
		TxMsg.dur = UI_SLOW_FLASH;
		xQueueSend( xUI_Queue, ( void * ) &TxMsg, xBlockTime );
		vTaskDelay(5000/portTICK_PERIOD_MS);
	}
}
