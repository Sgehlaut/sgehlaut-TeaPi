// This file will control our display and include appropriate functions.

#include "display.h"
#include "ds18b20.h"
#include "keyboard.h"
#include "malloc.h"
#include "motor.h"
#include "pi.h"
#include "printf.h"
#include "relay.h"
#include "shell.h"
#include "shell_commands.h"
#include "strings.h"
#include "temperature.h"
#include "timer.h"
#include "uart.h"

static const teaStruct teaList[] = {
    {"Black", 93, 99, 4},
    {"Green", 82,  85, 3},
    {"White", 79,  85, 2}, // 
};

bool isTea;

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

/*
 * Returns 1 if the character of a given string is a space.
 */
static int isspace(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n';
}

/*
 * Turns the words of a given input line into an array of the words without spaces.
 */
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

teaStruct teaType_evaluate(const char *teaName, teaStruct currTea)
{
    const char *argv[strlen(teaName)];
    tokenize(teaName, argv, strlen(teaName));
    if(strcmp(argv[0], "Black") == 0) {
        currTea = teaList[0];
        isTea = true;
        return currTea;
    }
    else if(strcmp(argv[0], "Green") == 0) {
        currTea = teaList[1];
        isTea = true;
        return currTea;
    }
    else if(strcmp(argv[0], "White") == 0) {
        currTea = teaList[2];
        isTea = true;
        return currTea;
    }
    else 
    {
        printf("Error: '%s' isn't a recognized type of tea.\n", argv[0]);
        isTea = false;
        return currTea;
    }
}

// This function returns true if the user inputs "Yes" in response
// to the query, and false if the user inputs anything else.
bool yesOrNo_evaluate() 
{
    char bagConfirmation[LINE_LEN];
    printf("Please place the tea bag on the pin. Once you've done so, type 'Yes' to confirm!\n");
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

void display_run(void) 
{
	printf("Welcome to your Raspberry Tea-Pi Experience! Please type using your PS/2 Keyboard.\n");

    teaStruct todaysTea;
    teaStruct currTea;
    isTea = false;

    while (!isTea) 
    {
        printf("What type of tea will you be enjoying today? The types of tea you can brew are 'Black', 'Green', or 'White'.\n");
        shell_readline(todaysTea.teaType, sizeof(todaysTea.teaType));
        currTea = teaType_evaluate(todaysTea.teaType, todaysTea);
    }

    todaysTea = currTea;

    printf("%s Tea is a great choice!\n", todaysTea.teaType);

    while(yesOrNo_evaluate() == false) {}

    printf("Heating up the water.\n");

    ds18b20_t dev;
    ds18b20_init(&dev);
    dev.pin = GPIO_PIN4;

    int currTemp = getCurrTemp(dev);

    int relayPin = GPIO_PIN21;
    activateSwitch(relayPin);

    printf("The starting temperature is %d. Your tea will brew at %d degrees Celsius.\n", currTemp, todaysTea.teaTempMax);
 

    while (currTemp < todaysTea.teaTempMax)
    {
        currTemp = getCurrTemp(dev);
        printf("Current Temperature: %d\n", currTemp);
        timer_delay(2);
    }

    printf("Ideal temperature reached.\n");
    deactivateSwitch(relayPin);

    printf("%s\n", "Now placing tea bag into kettle.");
    lowerTea();

    printf("Your %s tea is brewing for the ideal time of %d minutes.\n", todaysTea.teaType, todaysTea.teaBrewTime);

    unsigned int totalSeconds = 0;
    unsigned int initial_ticks = timer_get_ticks();

    while ((todaysTea.teaBrewTime * 60) > totalSeconds) {
        unsigned int tick_value = (timer_get_ticks() - initial_ticks)/1000000;
        unsigned int unit_seconds = tick_value % 10;
        unsigned int tens_seconds = (tick_value/10) % 10;
        unsigned int hundreds_seconds = (tick_value/100) % 100;
        int newTotalSeconds = unit_seconds + (tens_seconds * 10) + (hundreds_seconds * 100);

        if(newTotalSeconds >= (totalSeconds+60)) {
            totalSeconds = newTotalSeconds;
            if(totalSeconds/60 == 1) printf("It has been %d minute.\n", (totalSeconds/60));
            else printf("It has been %d minutes.\n", (totalSeconds/60));
        }

        currTemp = getCurrTemp(dev);
        if(currTemp > todaysTea.teaTempMax) {
            deactivateSwitch(relayPin);
        }
        else if(currTemp < todaysTea.teaTempMin) {
            activateSwitch(relayPin);
        }
    }

    printf("%s\n\n", "Now removing tea bag from kettle.");
    raiseTea();

    printf("Your %s tea is ready!\nThank you for using the Tea-Pi.", todaysTea.teaType);
}
