#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "OPF.h"


boolean createSrcFile(const boolean isC, const boolean isProyect,const char* fileName);
boolean createHeaderFile(const boolean isC, const char* fileName);
boolean createCMakeFiles(const boolean isC, const char* proyectName);
boolean createMakeFile(const boolean isC, const char* proyectName);
boolean createMainProyect(const boolean isC, const char* nameProyect);
