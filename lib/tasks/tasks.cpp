#include "tasks.h"

void tasksSetup(void)
{
	xTaskCreate(motorTask,
				"Motor Task",
				configMINIMAL_STACK_SIZE,
				NULL,
				1,
				NULL
			);

	vTaskStartScheduler();
}

void motorTaskInit(void)
{
	
}

void motorTask(void *pvParameters)
{
	// Motor task code goes here
	for(;;)
	{
		vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
	}
}

void userInterfaceTaskInit(void)
{
	own_stdio_setup();
	controlInit();
}

void vApplicationIdleHook(void)
{
	static uint8_t needInit = true;

	if (needInit)
	{
		userInterfaceTaskInit();
		needInit = false;
	}

	controlGetCommand();
	controlExecute();
}