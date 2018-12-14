#ifndef RELAY_H
#define RELAY_H

// Turn the relay on by making the voltage HIGH = 1 for the given pin
void activateSwitch(int pin);

 // Turn the relay off by making the voltage LOW = 0 for the given pin
void deactivateSwitch(int pin);

#endif