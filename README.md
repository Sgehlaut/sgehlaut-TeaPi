Project: TeaPi 
Creators: Medha Verma and Sidhu Gehlaut 
Description: TeaPi is an automated tea brewer. It makes you the perfect cup of tea by brewing it for the ideal amount of time
and at the ideal temperature. A user can interact with tea maker using terminal. The terminal will also provide feedback information like when the tea is performing a different step, how long the tea has currently been steeping for, and what the temperature currently is. 

How it works? 
1. Display asks what type of tea the user would like to drink. 
2. After user inputs data, it asks user to place tea bag on hook and confirm once they have done so. 
3. The pi turns on the tea kettle and checks the temperature until it reaches the perfect temperature. 
4. Once the ideal temperature has been reached, it turns the kettle off and the tea bag enters the water. 
5. If the temperature drops during the brewing session, the kettle turns back on to return it to the correct temperature. 
6. Once your tea has brewed for the right amount of time, the tea bag leaves the water. 

Work Distribution 
Medha -> in charge of hardware design + software for sensors 
Sidhu -> in charge of display + tying interface with software 
both worked on cleaning up the code. We mostly worked together in each part, but we chose to have one "lead" who somewhat created a timeline for the particular part and headed the research. 

References: 
1. For the servo motor: We ended up using a PWM servo driver. We found https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/blob/master/Adafruit_PWMServoDriver.cpp this cpp file online which was in Arduino. We used it as a basic structure in our own code, translating Arduino functionality to Pi functionality. We used the same i2c functions they used. We used their constants. We removed a lot of the functions they had like setPin, and added a few others like raise pin and lower pin as a way to more easily interact with the interface. The way we read and wrote our bits was also different. 
2. For the temperature sensor: We luckily found a file which was for raspberry pi libraries for this interface. We understood how they used the one-wire interface and then used their outline and constants to create our own functions using the pi libraries provided to us. We did not choose to create a file and map to the file, we rather just directly interacted the inputs and outputs with the GPIO pins. We also chose to use our time function a bit differently. Lastly, the way we read inputs and outputs were in a slightly different order. The time delays they used actually came really in handy because it helped us avoid the trickiness with the falling clock edge.  
