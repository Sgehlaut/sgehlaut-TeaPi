#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD


/* Function: begin() 
* Method: sets up the I2C interface and the hardware 
*/ 

void begin(void); 


/* Function: reset() 
* Method: Sends a reset command to the PCA9685 chip over I2C
*/ 
void reset(void); 


/* Function: setPWM 
* Method: Sets the PWM output of one of the PCA9685 pins
*  @param  num One of the PWM output pins, from 0 to 15
* @param  on At what point in the 4096-part cycle to turn the PWM output ON
* @param  off At what point in the 4096-part cycle to turn the PWM output OFF
*/ 
void setPWM(uint8_t num, uint16_t on, uint16_t off); 



/* setPWMFreq 
*  @brief  Sets the PWM frequency for the entire chip, up to ~1.6 KHz
*  @param  freq Floating point frequency that we will attempt to match
*/ 
void setPWMFreq(float freq); 


/* Method: read8 
* Description: reads a btye of data 
*/ 
uint8_t read8(uint8_t addr); 


/* write8
* Method: writes the functuins 
*/ 
void write8(uint8_t addr, uint8_t d); 

#endif 