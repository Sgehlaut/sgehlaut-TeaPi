#include "uart.h"
#include "keyboard.h"
#include "printf.h"
#include "shell.h"
#include "../display.h"
#include "../motor.h"


void main(void) 
{
    uart_init();
    keyboard_init();
    shell_init(printf);
    begin(); 
    setPWMFreq(60); 
    setPWM(0, 1000, 2000); 

    //display_run();
}