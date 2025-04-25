#include "dc_motor.h"
#include "own_stdio.h"

void dcMotorInit(DCMotor_t *motor,
				uint8_t pwm,
				uint8_t enable,
				uint8_t direction,
				void (*speed)(uint8_t value),
				void (*setDirection)(uint8_t value)
			)
{
	if (motor == NULL || speed == NULL || setDirection == NULL)
	{
		return;
	}
	motor->pwm = pwm;
	motor->enable = enable;
	motor->direction = direction;
	motor->speed = 0; // Initialize speed to 0
	motor->wasModified = false; // Initialize wasModified to false
	motor->setSpeed = speed;
	motor->setDirection = setDirection;

	motor->setDirection(motor->enable);
	motor->setSpeed(motor->speed);
}

void dcMotorCycleCall(DCMotor_t *motor)
{
	if (motor->wasModified)
	{
	
		motor->direction = dcMotorComputeDirection(motor->speed);
		motor->pwm = dcMotorConvertSpeedToPwm(motor->speed);

		printf("Motor speed equals %d\n\r", motor->speed);
		printf("Motor pwm equals %d\n\r", motor->pwm);

		motor->setDirection(motor->direction);
		motor->setSpeed(motor->pwm);
		motor->wasModified = false;
	}
}

int16_t dcMotorConvertSpeedToPwm(int16_t speed)
{
	int16_t pwmValue = 0;

	printf("Converting speed %d to PWM\n\r", speed);

	speed = ABS(speed);

	if (speed > MAX_SPEED)
		speed = MAX_SPEED;
	else if (speed < MIN_SPEED)
		speed = MIN_SPEED;

	pwmValue = (speed * MAX_PWM) / MAX_SPEED;
	return pwmValue;
}

uint8_t dcMotorComputeDirection(int8_t speed)
{
	if (speed > 0)
		return DC_MOTOR_FORWARD;
	else if (speed < 0)
		return DC_MOTOR_BACKWARD;
	else
		return DC_MOTOR_STOP;
}

void dcMotorSetSpeed(DCMotor_t *motor, int8_t value)
{
	motor->speed = 0;
	printf("!!Setting motor speed to %d\n\r", value);
	if(value > MAX_SPEED)
		value = MAX_SPEED;
	else if(value < MIN_SPEED)
		value = MIN_SPEED;
	motor->speed = value;
	printf("!!Motor speed set to %d\n\r", motor->speed);
	motor->wasModified = true;
}

int8_t dcMotorGetSpeed(DCMotor_t *motor)
{
	return motor->speed;
}

void dcMotorSetDirection(DCMotor_t *motor, uint8_t direction)
{
	motor->direction = direction;
	motor->wasModified = true;
}

uint8_t dcMotorGetDirection(DCMotor_t *motor)
{
	return motor->direction;
}

void dcMotorEnable(DCMotor_t *motor)
{
	motor->setDirection(motor->enable);
	motor->wasModified = true;
}

void dcMotorDisable(DCMotor_t *motor)
{
	motor->setDirection(motor->enable);
	motor->wasModified = true;
}

uint8_t dcMotorGetState(DCMotor_t *motor)
{
	return motor->enable;
}

void dcMotorStop(DCMotor_t *motor)
{
	motor->speed = 0; // Set speed to 0
	motor->wasModified = true;
}

void dcMotorEmergencyStop(DCMotor_t *motor)
{
	motor->setDirection(DC_MOTOR_STOP);
	motor->wasModified = true;
}

void dcMotorSetMaxSpeed(DCMotor_t *motor)
{
	motor->speed = MAX_SPEED; // Update the speed value
	motor->setSpeed(motor->speed); // Apply the new speed
	motor->wasModified = true;
}

void dcMotorSpeedUp(DCMotor_t *motor)
{
	if (motor->speed >= MAX_SPEED) motor->speed = MAX_SPEED;
	if (motor->speed < MAX_SPEED)
	{
		motor->speed += CHANGE_SPEED_STEP;
		motor->wasModified = true;
	}
}

void dcMotorSpeedDown(DCMotor_t *motor)
{
	if (motor->speed <= MIN_SPEED) motor->speed = MIN_SPEED;
	if (motor->speed > MIN_SPEED)
	{
		motor->speed -= CHANGE_SPEED_STEP;
		motor->wasModified = true;
	}
}