#include "tasks.h"

static HBridge_t hbridge;
DCMotor_t motor;

static int8_t speed = 0; // Variable to store the motor speed

void tasksSetup(void)
{
	xTaskCreate(motorTask,
				"Motor Task",
				256,
				NULL,
				1,
				NULL
			);
			
	vTaskStartScheduler();
}

void HBridgeWriteWrapper(uint8_t pin, uint8_t value){
	if(value == HBRIDGE_HIGH)
		digitalWrite(pin, HIGH);
	else if(value == HBRIDGE_LOW)
		digitalWrite(pin, LOW);
	else
		analogWrite(pin, value);
}

void motorSpeedWrapper(uint8_t value)
{
	hbridgeSetPwm(&hbridge, value);
}

void motorDirectionWrapper(uint8_t value)
{
	if (value == DC_MOTOR_FORWARD)
		hbridgeSetDirection(&hbridge, HBRIDGE_FORWARD);
	else if (value == DC_MOTOR_BACKWARD)
		hbridgeSetDirection(&hbridge, HBRIDGE_BACKWARD);
	else if (value == DC_MOTOR_STOP)
		hbridgeSetDirection(&hbridge, HBRIDGE_STOP);
	else
		hbridgeSetDirection(&hbridge, HBRIDGE_STOP); // Default to stop if invalid value
}

void motorTaskInit(void)
{
	//set motor pins to output
	pinMode(HBRIDGE_ENABLE_PIN, OUTPUT);
	pinMode(HBRIDGE_IN1_PIN, OUTPUT);
	pinMode(HBRIDGE_IN2_PIN, OUTPUT);

	hbridgeInit(&hbridge,
				HBRIDGE_IN1_PIN,
				HBRIDGE_IN2_PIN,
				HBRIDGE_ENABLE_PIN,
				HBridgeWriteWrapper
			);
			
	dcMotorInit(&motor,
				0,
				false,
				DC_MOTOR_STOP,
				motorSpeedWrapper,
				motorDirectionWrapper				
			);
	dcMotorEnable(&motor);
}

void motorTask(void *pvParameters)
{
	static uint8_t needInit = true;

	if (needInit)
	{
		motorTaskInit();
		needInit = false;
	}

	// Motor loop task
	for(;;)
	{
		dcMotorCycleCall(&motor);
		if(speed != dcMotorGetSpeed(&motor))
		{
			speed = dcMotorGetSpeed(&motor);
			hbridgeSetPwm(&hbridge, speed);
		}
		vTaskDelay(100 / portTICK_PERIOD_MS); // Delay for 1 second
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