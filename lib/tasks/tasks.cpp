#include "tasks.h"

SemaphoreHandle_t xButtonSemaphore;

void freeRTOSInit(void)
{
	if (xButtonSemaphore == NULL)
	{
		xButtonSemaphore = xSemaphoreCreateBinary();
		if (xButtonSemaphore != NULL)
		{
			xSemaphoreGive(xButtonSemaphore);
		}
	}

	xTaskCreate(ledTask, "LedTask", 128, NULL, 1, NULL);
}

void buttonLedTaskSetup(void)
{
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	pinMode(RED_LED_PIN, OUTPUT);
}

void buttonLedTask(void *pvParameters)
{
	static uint32_t ledOnTime = 0;
	static uint8_t needInit = true;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = BUTTON_LED_TASK_RECURRENCE / portTICK_PERIOD_MS;

	xLastWakeTime = xTaskGetTickCount();

	if (needInit)
	{
		buttonLedTaskSetup();
		needInit = false;
	}

	for (;;)
	{
		if (xSemaphoreTake(xButtonSemaphore, 0) == pdTRUE)
		{
			if (digitalRead(BUTTON_PIN) == LOW)
			{
				digitalWrite(RED_LED_PIN, HIGH);
			}
			else
			{
				digitalWrite(RED_LED_PIN, LOW);
			}
			xSemaphoreGive(xButtonSemaphore);
		}

		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}