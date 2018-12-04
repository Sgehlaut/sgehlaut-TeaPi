#ifndef MOTOR_H
#define MOTOR_H



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
void read8(uint8_t addr); 


/* write8
* Method: writes the functuins 
*/ 
void write8(uint8_t addr, uint8_t d); 

#endif 