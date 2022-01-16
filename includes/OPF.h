#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>


#ifdef  __APPLE__  
#define SYSCLEAR system("clear");
#else
#define SYSCLEAR system("close");
#endif 


#define false 0
#define true 1

typedef uint8_t boolean;



typedef struct _Configs* Configs;


Configs initConfigs(void);
Configs freeConfigs(Configs confs);
boolean checkArguments(const int numArgs, const char** args, Configs confs);
boolean getAnswer(void);
