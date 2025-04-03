#include "hbridge.h"

void hbridgeInit(HBridge_t *hbridge,
				uint8_t in_1,
				uint8_t in_2,
				uint8_t enable,
				void (*pwm)(uint8_t pin, uint8_t value),
				void (*pinWrite)(uint8_t pin, uint8_t value)
			)
{
	hbridge->in_1 = in_1;
	hbridge->in_2 = in_2;
	hbridge->enable = enable;
	hbridge->pwm = pwm;
	hbridge->pinWrite = pinWrite;
	hbridge->wasModified = true;
}

void hbridgeCycleCall(HBridge_t *hbridge)
{
	if (hbridge->wasModified)
	{
		hbridge->pinWrite(hbridge->in_1,
						hbridge->direction == HBRIDGE_FORWARD ? HBRIDGE_HIGH : HBRIDGE_LOW);
		hbridge->pwm(hbridge->in_2, hbridge->pwmValue);
		hbridge->wasModified = false;
	}
}

void hbridgeSetPwm(HBridge_t *hbridge, int16_t value)
{
	if (value > HBRIDGE_PWM_MAX)
		value = HBRIDGE_PWM_MAX;
	else if (value < HBRIDGE_PWM_MIN)
		value = HBRIDGE_PWM_MIN;

	hbridge->pwmValue = value;
	hbridge->wasModified = true;
}

uint8_t hbridgeGetPwm(HBridge_t *hbridge)
{
	return hbridge->pwmValue;
}

void hbridgeSetDirection(HBridge_t *hbridge, HBridgeDirection_t direction)
{
	hbridge->direction = direction;
	hbridge->wasModified = true;
}

uint8_t hbridgeGetDirection(HBridge_t *hbridge)
{
	return hbridge->direction;
}

void hbridgeEnable(HBridge_t *hbridge)
{
	hbridge->pinWrite(hbridge->enable, HBRIDGE_HIGH);
	hbridge->wasModified = true;
}

void hbridgeDisable(HBridge_t *hbridge)
{
	hbridge->pinWrite(hbridge->enable, HBRIDGE_LOW);
	hbridge->wasModified = true;
}

uint8_t hbridgeGetState(HBridge_t *hbridge)
{
	return hbridge->enable;
}

void hbridgeStop(HBridge_t *hbridge)
{
	hbridge->pwm(hbridge->enable, HBRIDGE_LOW);
	hbridge->wasModified = true;
}

void hbridgeEmergencyStop(HBridge_t *hbridge)
{
	hbridge->pinWrite(hbridge->in_1, HBRIDGE_LOW);
	hbridge->pinWrite(hbridge->in_2, HBRIDGE_LOW);
	hbridge->pwm(hbridge->enable, HBRIDGE_LOW);
	hbridge->wasModified = true;
}

