#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include <stdint.h>

#define MAX_SPEED 100
#define MIN_SPEED 0

#define MAX_PWM 255
#define MIN_PWM 0

#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef enum
{
	DC_MOTOR_BACKWARD = 0,
	DC_MOTOR_FORWARD,
	DC_MOTOR_STOP
} DCMotorDirection_t;

typedef struct
{
	uint8_t enable;
	uint8_t direction;
	uint8_t speed; 
	uint8_t wasModified;  // Flag to check if the state was modified
	void (*setSpeed)(uint8_t value);
	void (*setDirection)(uint8_t value);
} DCMotor_t;

void dcMotorInit(DCMotor_t *motor,
				uint8_t enable,
				uint8_t direction,
				void (*speed)(uint8_t value),
				void (*setDirection)(uint8_t value)
			);

void dcMotorCycleCall(DCMotor_t *motor);

void dcMotorSetSpeed(DCMotor_t *motor, uint8_t value);
uint8_t dcMotorGetSpeed(DCMotor_t *motor);
void dcMotorSetDirection(DCMotor_t *motor, uint8_t direction);
uint8_t dcMotorGetDirection(DCMotor_t *motor);
void dcMotorEnable(DCMotor_t *motor);
void dcMotorDisable(DCMotor_t *motor);
uint8_t dcMotorGetState(DCMotor_t *motor);
void dcMotorStop(DCMotor_t *motor);
void dcMotorEmergencyStop(DCMotor_t *motor);



#endif // DC_MOTOR_H