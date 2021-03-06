#include "uart.h"
#include "keyboard.h"
#include "printf.h"
#include "shell.h"
#include "../display.h"
#include "../motor.h"
#include "timer.h"
#include "../ds18b20.h"
#include "../crc1w.h"



void main(void) 
{
    uart_init();
    keyboard_init();
    timer_init();
	gpio_init();
    shell_init(printf);
    
  	display_run();
}