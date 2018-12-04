#include "i2c.h" 

typedef unsigned char uint8_t; 

void setPWMFreq(float freq){

  freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
  float prescaleval = 25000000;
  prescaleval /= 4096;
  prescaleval /= freq;
  prescaleval -= 1;


  uint8_t oldmode = read8(PCA9685_MODE1);
  uint8_t newmode = (oldmode&0x7F) | 0x10; // sleep
  write8(PCA9685_MODE1, newmode); // go to sleep
  write8(PCA9685_PRESCALE, prescale); // set the prescaler
  write8(PCA9685_MODE1, oldmode);
  delay(5);
  write8(PCA9685_MODE1, oldmode | 0xa0);  //  This sets the MODE1 register to turn on auto increment.
}



void read8(uint8_t addr) {
	i2c_write(_i2c, &addr, 1);
	char byte_read; 
	read(_i2c, &byte_read, 1); 

}

void write8(uint8_t addr, uint8_t d){
	i2c_write(_i2c, &addr, 1); 
	i2c_write(_i2c, d, 1); 
}


void begin(){
	i2c.init(); 
	reset(); 
	setPWMFreq(1000); 
}

void reset(){
	// store as a data length 
	write8(PCA9685_MODE1, 0x80); 
	delay(10); 

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





