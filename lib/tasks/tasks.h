#ifndef TASKS_H
#define TASKS_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>

#include "config.h"
#include "own_stdio.h"
#include "control.h"
#include "hbridge.h"
#include "dc_motor.h"

void tasksSetup(void);

void motorTaskInit(void);
void motorTask(void *pvParameters);

void userInterfaceTaskInit(void);

#endif