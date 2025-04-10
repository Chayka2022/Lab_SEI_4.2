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
	hbridge->in_1 = in_1;
	hbridge->in_2 = in_2;
	hbridge->enable = enable;
	hbridge->pinWrite = pinWrite;
}

uint8_t hbridgeCheckLimits(int16_t value)
{
	if (value > HBRIDGE_PWM_MAX)
	{
		return HBRIDGE_PWM_MAX;
	}
	else if (value < HBRIDGE_PWM_MIN)
	{
		return HBRIDGE_PWM_MIN;
	}
	return value;
}

void hbridgeSetPwm(HBridge_t *hbridge, int16_t value)
{
	value = hbridgeCheckLimits(value);
	// TODO: Add function to set PWM value
	hbridge->pwmValue = value;
}

uint8_t hbridgeGetPwm(HBridge_t *hbridge)
{
	return hbridge->pwmValue;
}

void hbridgeSetDirection(HBridge_t *hbridge, HBridgeDirection_t direction)
{
	hbridge->direction = direction;
	// TODO: Add function to set direction
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
}

void hbridgeEmergencyStop(HBridge_t *hbridge)
{
	// TODO: Add function to stop the motor
	hbridge->pinWrite(hbridge->in_1, HBRIDGE_LOW);
	hbridge->pinWrite(hbridge->in_2, HBRIDGE_LOW);
}

