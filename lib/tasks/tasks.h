#ifndef TASKS_H
#define TASKS_H

#include <Arduino.h>
#include <config.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>

void freeRTOSInit(void);

void motorTaskInit(void);
void motorTask(void *pvParameters);

void userInterfaceTaskInit(void);
void userInterfaceTask(void *pvParameters);


#endif