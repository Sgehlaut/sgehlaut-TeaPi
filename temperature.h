#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "ds18b20.h"
#include "printf.h"
#include "gpio.h"

int main_test(void);

int getCurrTemp(ds18b20_t dev);

#endif