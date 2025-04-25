#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include <stdint.h>
#include <stdlib.h>
#include "config.h"

typedef enum
{
	DC_MOTOR_BACKWARD = 0,
	DC_MOTOR_FORWARD,
	DC_MOTOR_STOP
} DCMotorDirection_t;

typedef struct
{
	uint8_t pwm;
	uint8_t enable;
	uint8_t direction;
	int8_t speed; 
	uint8_t wasModified;
	void (*setSpeed)(uint8_t value);
	void (*setDirection)(uint8_t value);
} DCMotor_t;

void dcMotorInit(DCMotor_t *motor,
				uint8_t pwm,
				uint8_t enable,
				uint8_t direction,
				void (*speed)(uint8_t value),
				void (*setDirection)(uint8_t value)
			);

void dcMotorCycleCall(DCMotor_t *motor);

void dcMotorSetSpeed(DCMotor_t *motor, int8_t value);
int8_t dcMotorGetSpeed(DCMotor_t *motor);
void dcMotorSetDirection(DCMotor_t *motor, uint8_t direction);
uint8_t dcMotorGetDirection(DCMotor_t *motor);
void dcMotorEnable(DCMotor_t *motor);
void dcMotorDisable(DCMotor_t *motor);
uint8_t dcMotorGetState(DCMotor_t *motor);
void dcMotorStop(DCMotor_t *motor);
void dcMotorEmergencyStop(DCMotor_t *motor);
void dcMotorSetMaxSpeed(DCMotor_t *motor);
void dcMotorSpeedUp(DCMotor_t *motor);
void dcMotorSpeedDown(DCMotor_t *motor);
uint8_t dcMotorComputeDirection(int8_t speed);
int16_t dcMotorConvertSpeedToPwm(int16_t speed);


#endif // !DC_MOTOR_H