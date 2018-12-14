#ifndef DISPLAY_H
#define DISPLAY_H

#define LINE_LEN 80

typedef struct {
	char teaType[LINE_LEN]; //The name of the type of tea
	int teaTempMin; //The min ideal brewing temperature
	int teaTempMax; //The max ideal brewing temperature
	int teaBrewTime; //The ideal brewing time
} teaStruct;

// This function accesses an array that we wrote earlier.
// It returns a filled in teaStruct based on the name of the
// tea passed in.
teaStruct teaType_evaluate(const char *teaName, teaStruct currTea);

// The "main" function call. It will call all the functions and be
// the only mode of interaction between the user and the code.
void display_run(void);

#endif