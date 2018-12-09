// This file will control our display and include appropriate functions.

#include "shell.h"
#include "shell_commands.h"
#include "uart.h"
#include "pi.h"
#include "keyboard.h"
#include "malloc.h"
#include "printf.h"
#include "strings.h"
#include "timer.h"
#include "display.h"
#include "motor.h"
static const teaStruct teaList[] = {
    {"Black", 93, 100, 4},
    {"Green", 82,  85, 3},
    {"White", 79,  85, 2},
};

/*
 * Functions strndup, isspace, and tokenize copied from lab4.
 */

/*
 * Returns a pointer to a new null-terminated string containing at most 'n'
 * bytes copied from the string pointed to by 'src'.
 *
 * Example: strndup("cs107e", 4) == "cs10"
 */
static char *strndup(const char *src, int n)
{
    char *dst = malloc(n + 1);
    dst[n] = '\0';
    return memcpy(dst, src, n);
}

static int isspace(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n';
}

static int tokenize(const char *line, const char *array[], int max)
{
    int ntokens = 0;

    while (*line != '\0' && ntokens < max) {
        while (isspace(*line)) line++;  // skip past spaces
        if (*line == '\0') break; // no more non-white chars
        const char *start = line;
        while (*line != '\0' && !isspace(*line)) line++; // advance to next space/null
        int nchars = line - start;
        array[ntokens++] = strndup(start, nchars);   // make heap-copy, add to array
    }
    return ntokens;
}

bool teaType_evaluate(const char *teaName, teaStruct currTea)
{
    const char *argv[strlen(teaName)];
    tokenize(teaName, argv, strlen(teaName));
    if(strcmp(argv[0], "Black") == 0) {
        currTea = teaList[0];
        return true;
    }
    else if(strcmp(argv[0], "Green") == 0) {
        currTea = teaList[1];
        return true;
    }
    else if(strcmp(argv[0], "White") == 0) {
        currTea = teaList[2];
        return true;
    }
    else 
    {
        printf("Error: '%s' isn't a recognized type of tea.\n", argv[0]);
        return false;
    }
}

bool yesOrNo_evaluate() 
{
    char bagConfirmation[LINE_LEN];
    printf("Please place the tea-bag on the arm. Once you've done so, type 'Yes' to confirm!\n");
    shell_readline(bagConfirmation, sizeof(bagConfirmation));
    const char *argv[strlen(bagConfirmation)];
    tokenize(bagConfirmation, argv, strlen(bagConfirmation));
    if(strcmp(argv[0], "Yes") == 0) {
        printf("Thank you for confirming!\n");
        return true;
    }
    else {
        printf("Please type 'Yes' to confirm.\n");
        return false;
    }

}

//The "main" function call. It will call all the functions and make a working display.
void display_run(void)
{
    teaStruct todaysTea;
    int currTemp = 0; //Replace with the temperature read from the sensor
    bool isTea = false;
    printf("Welcome to your Raspberry Pi-Tea Experience! Please type using your PS/2 Keyboard.\n");

    while (isTea == false) 
    {
        printf("What type of tea will you be enjoying today?\n");
        shell_readline(todaysTea.teaType, sizeof(todaysTea.teaType));
        isTea = teaType_evaluate(todaysTea.teaType, todaysTea);
    }

    printf("%s Tea is a great choice!\n", todaysTea.teaType);
    printf("%s\n", "Now placing tea bag into kettle");

    int teaPin = GPIO_PIN21;             // Tells Pi the relay is connected to pin 21


    gpio_set_output(relay);

    gpio_write(relay, 1);   // Turn the relay on (HIGH is the voltage level = 1)
    timer_delay(5);                 // Stay ON for 5 seconds
    gpio_write(relay, 0);   // Turn the relay off by making the voltage LOW = 0
    timer_delay(5);                 // Stay OFF for 5 seconds

    while(yesOrNo_evaluate() == false) {}

/*    begin(); 
    setPWMFreq(200); 
    setPWM(0, 1000, 2000); 
    timer_delay(2); 
    //setPWMFreq(0); 
    setPWM(0, 0, 4096); 
    //display_run();
    timer_delay(2);
    setPWMFreq(60);
    setPWM(0, 1000, 2000); 
    timer_delay(2);
    setPWM(0, 0, 4096);
*/ 


    // while (currTemp < todaysTea.teaTempMax)
    // {
    //  //This while loop will read temperature until it hits the ideal temperature for the first time!
    // }

    // while()
    // {

    // }
}