// This file will control our display and include appropriate functions.

#include "shell.h"
#include "shell_commands.h"
#include "uart.h"
#include "pi.h"
#include "keyboard.h"
#include "malloc.h"
#include "printf.h"
#include "strings.h"

#define LINE_LEN 80

typedef struct {
	char teaType[LINE_LEN];
	int teaTemp;
	int teaBrewTime;
} teaStruct;

void fillInTeaInfo(char buf[]) 
{
	//Function will access a data structure in order to fill in the current tea struct
}

bool display_readTeaType(char buf[], int bufsize)
{
	//Given a type of tea, it will call fillInTeaInfo and return true if the type was filled in.
}

//The "main" function call. It will call all the functions and make a working display.
void display_run(void)
{
	teaStruct todaysTea;
	todaysTea.teaType = '';
	bool isTea = false;
	display_printf("Welcome to your Raspberry Pi-Tea Experience. Remember to type on your PS/2 keyboard!\n");

	while (teaType == ) 
    {
        printf("What type of tea will you be enjoying today?\n");
        isTea = display_readTeaType(teaType, sizeof(teaType));
        teaType_evaluate(teaType, todaysTea);
    }
}