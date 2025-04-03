#ifndef TASKS_H
#define TASKS_H

#include <Arduino.h>
#include <config.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

void freeRTOSInit(void);


void buttonLedTaskSetup(void);
void buttonLedTask(void *pvParameters);


#endif