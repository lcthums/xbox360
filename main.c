#include "xbox360.h"
#include "err.h"

int main(int argc, char** args) {
	if (argc < 2)
		err(EXIT_FAILURE, USAGE_STRING);

	char *filename = NULL;

	if (operation == MANUAL || operation == ENCODED)
		operation = atoi(args[1]);
	else if (operation == ENCODED) {
		if (argc < 3)
			err(EXIT_FAILURE, USAGE_STRING);
		else
			filename = args[2];
	} else
		err(EXIT_FAILURE, USAGE_STRING);
	    
	bus = i2c_open(I2C_BUS);

	delay.tv_sec = 0;
	delay.tv_nsec = 10000000L;

	PCA9685_setFreq(bus, 320);
	PCA9685_init(bus);

	PCA9685_setDutyCicle(bus, MOTOR_CHANNEL, 50);
	PCA9685_setDutyCicle(bus, SERVO_CHANNEL, 50);
	PCA9685_setDutyCicle(bus, LED_CHANNEL, 50);

	GamepadInit();

	failsafe(CONTROLLER);

	PCA9685_stop(bus);

	return 0;
}
