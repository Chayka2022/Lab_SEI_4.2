#include "dc_motor.h"

void dcMotorInit(DCMotor_t *motor,
				uint8_t enable,
				uint8_t direction,
				void (*speed)(uint8_t value),
				void (*setDirection)(uint8_t value)
			)
{
	motor->enable = enable;
	motor->direction = direction;
	motor->speed = 0;
	motor->setDirection = setDirection;
	motor->wasModified = true;
}

void dcMotorCycleCall(DCMotor_t *motor)
{
	if (motor->wasModified)
	{
		motor->setDirection(motor->direction);
		motor->setSpeed(motor->speed);
		motor->wasModified = false;
	}
}

int16_t dcMotorConvertSpeedToPwm(int16_t speed)
{
	uint8_t pwmValue = 0;

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
	motor->speed = value;

	motor->direction = dcMotorComputeDirection(motor->speed);
	motor->speed = dcMotorConvertSpeedToPwm(motor->speed);

	motor->wasModified = true;
}

uint8_t dcMotorGetSpeed(DCMotor_t *motor)
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
	motor->setDirection(DC_MOTOR_STOP);
	motor->wasModified = true;
}

void dcMotorEmergencyStop(DCMotor_t *motor)
{
	motor->setDirection(DC_MOTOR_STOP);
	motor->wasModified = true;
}