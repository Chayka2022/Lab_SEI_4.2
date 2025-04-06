#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>
#include <config.h>
#include <timer-api.h>
#include <tasks.h>

void schedulerSetup(void);
void schedulerRun(void);

#endif // SCHEDULER_H