#ifndef HBRIDGE_H
#define HBRIDGE_H

#include <stdint.h>
#include <stdlib.h>

#define HBRIDGE_PWM_MAX 255
#define HBRIDGE_PWM_MIN 0

#define HBRIDGE_HIGH	1
#define HBRIDGE_LOW		0

typedef enum
{
	HBRIDGE_BACKWARD = 0,
	HBRIDGE_FORWARD,
	HBRIDGE_STOP
} HBridgeDirection_t;

typedef struct
{
	uint8_t in_1;
	uint8_t in_2;
	uint8_t enable;
	HBridgeDirection_t direction;
	uint8_t pwmValue;
	void (*pinWrite)(uint8_t pin, uint8_t value);
} HBridge_t;

void hbridgeInit(HBridge_t *hbridge,
				uint8_t in_1,
				uint8_t in_2,
				uint8_t enable,
				void (*pinWrite)(uint8_t pin, uint8_t value)
			);

void hbridgeSetPwm(HBridge_t *hbridge, int16_t value);
uint8_t hbridgeGetPwm(HBridge_t *hbridge);
void hbridgeSetDirection(HBridge_t *hbridge, HBridgeDirection_t direction);
uint8_t hbridgeGetDirection(HBridge_t *hbridge);
void hbridgeEnable(HBridge_t *hbridge);
void hbridgeDisable(HBridge_t *hbridge);
uint8_t hbridgeGetState(HBridge_t *hbridge);
void hbridgeStop(HBridge_t *hbridge);
void hbridgeEmergencyStop(HBridge_t *hbridge);



#endif // HBRIDGE_H