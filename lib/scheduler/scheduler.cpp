#include "scheduler.h"

void schedulerSetup(void)
{
	timer_init_ISR_1KHz(TIMER_DEFAULT);
}

void schedulerRun(void)
{
	static uint32_t ledTaskTimer = LED_TASK_OFFSET;
	static uint32_t buttonTaskTimer = BUTTON_TASK_OFFSET;
	static uint32_t blinkLedTaskTimer = BLINK_LED_TASK_OFFSET;
	static uint32_t changeBlinkFrequencyTaskTimer = CHANGE_BLINK_FREQUENCY_TASK_OFFSET;
	static uint32_t idleTaskTimer = IDLE_TASK_OFFSET;

	if (--ledTaskTimer == 0)
	{
		ledTask(NULL);
		ledTaskTimer = LED_TASK_RECURRENCE;
	}

	if (--buttonTaskTimer == 0)
	{
		buttonTask(NULL);
		buttonTaskTimer = BUTTON_TASK_RECURRENCE;
	}

	//TODO: Implement the rest of the tasks
}

void timer_handle_interrupts(int timer)
{
	schedulerRun();
}