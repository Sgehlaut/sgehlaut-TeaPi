#include "i2c.h" 
#include "motor.h"
#include "timer.h"
#include "math.h"

unsigned _i2c = 0x40; 

uint8_t read8(uint8_t addr) {
	i2c_write(_i2c, (char *)&addr, 1);
	char byte_read; 
	i2c_read(_i2c, &byte_read, 1); 
	return byte_read; 

}

void write8(uint8_t addr, uint8_t d){
	char array[2]; 
	array[0] = addr; 
	array[1] = d; 
	i2c_write(_i2c, &array[0], 2); 
}

void setPWMFreq(float freq){

  freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
  float prescaleval = 25000000;
  prescaleval /= 4096;
  prescaleval /= freq;
  prescaleval -= 1;

  uint8_t prescale = floor(prescaleval + 0.5);


  uint8_t oldmode = read8(PCA9685_MODE1);
  uint8_t newmode = (oldmode&0x7F) | 0x10; // sleep
  write8(PCA9685_MODE1, newmode); // go to sleep
  write8(PCA9685_PRESCALE, prescale); // set the prescaler
  write8(PCA9685_MODE1, oldmode);
  write8(PCA9685_MODE1, oldmode | 0xa0);  //  This sets the MODE1 register to turn on auto increment.
}




void begin(){
	i2c_init();
	reset(); 
	setPWMFreq(1000); 
}

void reset(){
	// store as a data length
	timer_delay(1);
	write8(PCA9685_MODE1, 0x80); 
} 


void setPWM(uint8_t num, uint16_t on, uint16_t off){
	char data[5]; 
	data[0] = LED0_ON_L+4*num;
	data[1] = on; 
	data[2] = on>>8; 
	data[3] =  off; 
	data[4] = off>>8;
	// write the data to the screen 
	i2c_write(_i2c, data, 5); 
}

void lowerTea(){
	begin(); 
    setPWMFreq(200); 
    setPWM(0, 1000, 2000); 
    timer_delay(5); 
    setPWM(0, 0, 4096); 
}

void raiseTea(){
    setPWMFreq(60);
    setPWM(0, 1000, 2000); 
    timer_delay(5);
    setPWM(0, 0, 4096);
}




