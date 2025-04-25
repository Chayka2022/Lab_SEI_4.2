#include "control.h"

const char *command = NULL;
static int16_t value = 0;

extern DCMotor_t motor;

static const char *motorControlCommands[CONTROL_NUMBER_OF_COMMANDS] =
	{
		"motor",
		"set",
		"stop",
		"max",
		"inc",
		"dec",
		"help"};

static const char *motorControlDescriptions[] =
	{
		"Set the motor speed from -100 to 100",
		"Stop the motor",
		"Set the motor to max speed",
		"Increase the motor speed",
		"Decrease the motor speed",
		"Show this help"};

void dcMotorSetSpeedWrapper(DCMotor_t *motor)
{
	dcMotorSetSpeed(motor, value);
}

void (*commandHandler[])(DCMotor_t *motor) =
	{
		NULL,					// Placeholder for motor command
		dcMotorSetSpeedWrapper, // Wrapper for setting motor speed
		dcMotorStop,			// Stop the motor
		dcMotorSetMaxSpeed,		// Set motor to max speed
		dcMotorSpeedUp,			// Increase motor speed
		dcMotorSpeedDown,		// Decrease motor speed
		controlPrintHelp
	};

void controlInit(void)
{
	command = NULL;
	printf("System initialized!\n\r");
	printf("Available commands:\n\r");
	controlPrintHelp(NULL);
	printf("Enter command:\n\r");
}

void controlExecute(void)
{
	if (command == NULL)
	{
		return;
	}

	if (!strncmp(command,
				 motorControlCommands[CONTROL_SET],
				 strlen(motorControlCommands[CONTROL_SET])))
	{
		value = atoi(command + 4); // Skip the "set " part
		if (value < -100 || value > 100)
		{
			printf("Invalid value. Please enter a value between -100 and 100.\n\r");
			return;
		}
		printf("Setting motor speed to %d\n\r", value);
		
		
		static char buff[4];
		strncpy(buff, command, 3); // Copy the value to a buffer
		command = buff;
	}

	for (size_t i = CONTROL_MOTOR; i < CONTROL_NUMBER_OF_COMMANDS; i++)
	{
		if (!strcmp(command, motorControlCommands[i]))
		{
			printf("Command: %s - %s\n\r",
				   motorControlCommands[i],
				   motorControlDescriptions[i - CONTROL_SET]);

			if (commandHandler[i] != NULL)
			{
				printf("Executing command: %d\n\r", i);
				commandHandler[i](&motor); // Call the command handler function
			}
		}	
	}

	command = NULL; // Reset command after processing
	printf("Enter command: ");
}

void controlGetCommand(void)
{
	static char commandBuffer[COMMAND_BUFFER_SIZE];

	scanf("%*c%[^\n]", commandBuffer);

	if (!strncmp(commandBuffer,
				 motorControlCommands[CONTROL_MOTOR],
				 strlen(motorControlCommands[CONTROL_MOTOR])))
	{
		command = strstr(commandBuffer, " ");
		command += 1; // Skip the space character
	}
}

void controlPrintHelp(DCMotor_t *motor)
{
	for (size_t i = CONTROL_SET; i < CONTROL_NUMBER_OF_COMMANDS; i++)
	{
		printf("%s %s - %s\n\r",
			   motorControlCommands[CONTROL_MOTOR],
			   motorControlCommands[i],
			   motorControlDescriptions[i - CONTROL_SET]);
	}
}