#include "hbridge.h"

void hbridgeInit(HBridge_t *hbridge,
				uint8_t in_1,
				uint8_t in_2,
				uint8_t enable,
				void (*pinWrite)(uint8_t pin, uint8_t value)
			)
{
	if (hbridge == NULL || pinWrite == NULL)
	{
		return;
	}
	hbridge->in_1 = HBRIDGE_IN1_PIN;
	hbridge->in_2 = HBRIDGE_IN2_PIN;
	hbridge->enable = enable;
	hbridge->pinWrite = pinWrite;
}

int8_t hbridgeCheckLimits(int8_t value)
{
	if (value > MAX_SPEED)
	{
		return MAX_SPEED;
	}
	else if (value < MIN_SPEED)
	{
		return MIN_SPEED;
	}

	return value;
}

void hbridgeSetPwm(HBridge_t *hbridge, int8_t value)
{
    value = hbridgeCheckLimits(value);

    if (value > 0) {
        hbridge->pinWrite(hbridge->in_1, HBRIDGE_HIGH);
        hbridge->pinWrite(hbridge->in_2, HBRIDGE_LOW);
    } else if (value < 0) {
        hbridge->pinWrite(hbridge->in_1, HBRIDGE_LOW);
        hbridge->pinWrite(hbridge->in_2, HBRIDGE_HIGH);
    } else {
        hbridge->pinWrite(hbridge->in_1, HBRIDGE_LOW);
        hbridge->pinWrite(hbridge->in_2, HBRIDGE_LOW);
    }
    hbridge->pinWrite(hbridge->enable, ABS(value)); // Set PWM value
    //hbridge->pwmValue = value;
}

uint8_t hbridgeGetPwm(HBridge_t *hbridge)
{
	return hbridge->pwmValue;
}

void hbridgeSetDirection(HBridge_t *hbridge, uint8_t direction)
{
	//find the same value of direction in the enum
	if (direction == 0)
	{
		hbridge->direction = HBRIDGE_BACKWARD;
	}
	else if (direction == 1)
	{
		hbridge->direction = HBRIDGE_FORWARD;
	}
	else if (direction == 2)
	{
		hbridge->direction = HBRIDGE_STOP;
	}
	hbridge->pinWrite(hbridge->in_1, (direction == HBRIDGE_FORWARD) ? HBRIDGE_HIGH : HBRIDGE_LOW);
	hbridge->pinWrite(hbridge->in_2, (direction == HBRIDGE_BACKWARD) ? HBRIDGE_HIGH : HBRIDGE_LOW);
}

uint8_t hbridgeGetDirection(HBridge_t *hbridge)
{
	return hbridge->direction;
}

void hbridgeEnable(HBridge_t *hbridge)
{
	hbridge->pinWrite(hbridge->enable, HBRIDGE_HIGH);
}

void hbridgeDisable(HBridge_t *hbridge)
{
	hbridge->pinWrite(hbridge->enable, HBRIDGE_LOW);
}

uint8_t hbridgeGetState(HBridge_t *hbridge)
{
	return hbridge->enable;
}

void hbridgeStop(HBridge_t *hbridge)
{
	// TODO: Add function to stop the motor
	// Set both inputs to low to stop the motor
	hbridge->pinWrite(hbridge->in_1, HBRIDGE_LOW);
	hbridge->pinWrite(hbridge->in_2, HBRIDGE_LOW);
	hbridge->pwmValue = 0;
}

void hbridgeEmergencyStop(HBridge_t *hbridge)
{
	// TODO: Add function to stop the motor
	// Set both inputs to low to stop the motor
	hbridge->pinWrite(hbridge->in_1, HBRIDGE_LOW);
	hbridge->pinWrite(hbridge->in_2, HBRIDGE_LOW);
}

