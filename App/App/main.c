#include <pins.h>
#include <driver_init.h>
#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>

#define TASK_EXAMPLE_STACK_SIZE (128 / sizeof(portSTACK_TYPE))
#define TASK_EXAMPLE_STACK_PRIORITY (tskIDLE_PRIORITY + 1)
static TaskHandle_t      xCreatedExampleTask;

int main(void);
static void example_task(void *p);

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	system_init();

	if (xTaskCreate(
	example_task, "Example", TASK_EXAMPLE_STACK_SIZE, NULL, TASK_EXAMPLE_STACK_PRIORITY, xCreatedExampleTask)
	!= pdPASS) {
		while (1) {
			;
		}
	}

	vTaskStartScheduler();

	/* Replace with your application code */
	while (1) {
	}
}

static void example_task(void *p)
{
	(void)p;
	while (1) {
		gpio_toggle_pin_level(MCU_STATUS_LED);
		vTaskDelay(100/portTICK_PERIOD_MS);
	}
}
