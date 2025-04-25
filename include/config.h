#ifndef CONFIG_H
#define CONFIG_H

#define BAUDRATE 115200

#define ABS(x) ((x) < 0 ? -(x) : (x))

#define MAX_SPEED 			100
#define MIN_SPEED 			-100

#define MAX_PWM 			255
#define MIN_PWM 			0

#define CHANGE_SPEED_STEP 	10

#define HBRIDGE_HIGH		1
#define HBRIDGE_LOW			0

enum HBRRIDGE_PINS
{
	HBRIDGE_ENABLE_PIN = 8,
	HBRIDGE_IN1_PIN,
	HBRIDGE_IN2_PIN
};

#endif