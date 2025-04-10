#include "own_stdio.h"

static FILE stream = {0};

int own_putchar(char ch, FILE *stream)
{
	Serial.write(ch);

	return 0;
}

int own_getchar(FILE *stream)
{
	while (!Serial.available());
	return Serial.read();
}

void own_stdio_setup(void)
{
	Serial.begin(BAUDRATE);

	fdev_setup_stream(	&stream,
						own_putchar,
						own_getchar,
						_FDEV_SETUP_RW
					);

	stdin = &stream;
	stdout = &stream;
}
	