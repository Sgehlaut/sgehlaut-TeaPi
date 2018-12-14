#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "ds18b20.h"
#include "printf.h"
#include "gpio.h"

// This function takes in a ds18b20_t struct and references the temperature
// from ds18b20_read_temperature(&dev). This returns the value and converts
// it into a Celsius degree value that can be used by other programs.
int getCurrTemp(ds18b20_t dev);

// This test is an error checking function for the temperature sensor. It tries
// to read the temperature, and if it cannot do so, prints various error codes.
// It returns 0 if there are no errors and -1 if there is at least one.
int main_test(void);

#endif