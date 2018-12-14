#ifndef DISPLAY_H
#define DISPLAY_H

#define LINE_LEN 80

typedef struct {
	char teaType[LINE_LEN]; //The name of the type of tea
	int teaTempMin; //The min ideal brewing temperature
	int teaTempMax; //The max ideal brewing temperature
	int teaBrewTime; //The ideal brewing time
} teaStruct;

//Given a type of tea, it will call fillInTeaInfo and return true if the type was filled in.
//This function could alternatively access an array that we wrote earlier.
teaStruct teaType_evaluate(const char *teaName, teaStruct currTea);

//The "main" function call. It will call all the functions and make a working display.
void display_run(void);

#endif