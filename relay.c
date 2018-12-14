// This file will control our relay and include appropriate functions.

#include "gpio.h"
#include "relay.h"

void activateSwitch(int pin) {

	gpio_set_output(pin);
	gpio_write(pin, 1);   // Turn the relay on (HIGH voltage level = 1)
}

void deactivateSwitch(int pin) {

	gpio_set_output(pin);
	gpio_write(pin, 0);   // Turn the relay off (LOW voltage level = 0)
}
