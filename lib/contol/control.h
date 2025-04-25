#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dc_motor.h"

#define COMMAND_BUFFER_SIZE 32

typedef enum 
{
	CONTROL_MOTOR = 0u,
	CONTROL_SET,
	CONTROL_STOP,
	CONTROL_MAX,
	CONTROL_INC,
	CONTROL_DEC,
	CONTROL_HELP,
	CONTROL_NUMBER_OF_COMMANDS
} ControlCommand_t;


void controlInit(void);
void controlExecute(void);
void controlGetCommand(void);
void controlPrintHelp(DCMotor_t *motor);

#endif // !CONTROL_H