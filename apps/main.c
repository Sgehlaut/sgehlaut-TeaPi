#include "uart.h"
#include "keyboard.h"
#include "printf.h"
#include "shell.h"
#include "../display.h"


void main(void) 
{
    uart_init();
    keyboard_init();
    shell_init(printf);

    display_run();
}