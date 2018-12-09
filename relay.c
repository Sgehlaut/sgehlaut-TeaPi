// This file will control our relay and include appropriate functions.

#include "gpio.h"
#include "timer.h"

void activateSwitch(int pin) {
	gpio_write(pin, 1);   // Turn the relay on (HIGH is the voltage level = 1)
}

void deactivateSwitch(int pin) {
	gpio_write(pin, 0);   // Turn the relay off by making the voltage LOW = 0
}
