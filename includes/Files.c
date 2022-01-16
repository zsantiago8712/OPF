#include "Files.h"
#include <stdio.h>


static boolean checkFileExists(const char* nameFile);
static void convertFileNameToMacro(char* macro, const char* nameFile);


boolean createSrcFile(const boolean isC, const boolean isProyect,const char* fileName){

	const char* extensionsSrc[2] = {"cpp", "c"};
	const char* extensionsHeader[2] = {"hpp", "h"};
	char answer;
	char newNameFile[BUFSIZ];
	FILE* file = fopen(fileName, "w");

	if(isProyect)
		sprintf(newNameFile, "%s/includes/%s.%s", fileName, fileName, extensionsSrc[isC]);
	else 
		sprintf(newNameFile, "%s.%s", fileName, extensionsSrc[isC]);

	if(checkFileExists(newNameFile)){

		if(!getAnswer())
			return false;
	}		
	
	file = fopen(newNameFile, "w");
	
	if(isC)
		fprintf(file, "#include <stdio.h>\n#include <stdlib.h>\n");
	else
		fprintf(file, "#include <iostream>\n#include <vector>\n");

	if(!isProyect)
		fprintf(file, "int main(int argc, char** argv){\n\n\n\treturn 0;\n}");
	else
		fprintf(file, "#include \"%s.%s\"\n", fileName, extensionsHeader[isC]);

	fclose(file);
	return true;
}


boolean createMainProyect(const boolean isC, const char* nameProyect){

	char newNameFile[BUFSIZ];
	const char* extensionsSrc[2] = {"cpp", "c"};
	const char* extensionsHeader[2] = {"hpp", "h"};
	FILE* mainFile;

	sprintf(newNameFile, "%s/main.%s", nameProyect, extensionsSrc[isC]);
	mainFile = fopen(newNameFile, "w");

	if(isC)
		fprintf(mainFile, "#include <stdio.h>\n#include <stdlib.h>\n#include \"includes/%s.%s\"\n\n\n", nameProyect, extensionsHeader[isC]);
	else 
		fprintf(mainFile, "#include <iostream>\n#include <vector>\n#include \"includes/%s.%s\"\n\n\n", nameProyect, extensionsHeader[isC]);


	fprintf(mainFile, "int main(int argc, char** argv){\n\n\n\treturn 0;\n}");

	fclose(mainFile);
	return true;
}

boolean createHeaderFile(const boolean isC, const char* fileName){

	const char* extensionsHeader[2] = {"hpp", "h"};
	char answer;
	char newNameFile[BUFSIZ];
	char macrofileName[BUFSIZ];
	FILE* file;

	sprintf(newNameFile, "%s/includes/%s.%s", fileName, fileName, extensionsHeader[isC]);
	convertFileNameToMacro(macrofileName, fileName);

	if(checkFileExists(newNameFile)){

		if(!getAnswer())
			return false;
	}		
	
	file = fopen(newNameFile, "w");
	
	fprintf(file, "#ifndef %s\n", macrofileName);
	fprintf(file, "#define %s\n\n\n", macrofileName);

	if(isC)
		fprintf(file, "#include <stdio.h>\n#include <stdlib.h>\n\n\n");
	else
		fprintf(file, "#include <iostream>\n#include <vector>\n");

	fprintf(file, "#endif //%s\n", macrofileName);
	fclose(file);
	return true;
}


boolean createCMakeFiles(const boolean isC, const char* proyectName){

	const char* extensionsSrc[2] = {"cpp", "c"};
	char fileName[BUFSIZ];
	FILE* cmake1, *cmake2;
	char cmakeList1[BUFSIZ], cmakeList2[BUFSIZ];

	sprintf(fileName, "%s.%s", proyectName, extensionsSrc[isC]);
	sprintf(cmakeList1, "%s/CMakeLists.txt", proyectName);
	sprintf(cmakeList2, "%s/includes/CMakeLists.txt", proyectName);

	cmake1 = fopen(cmakeList1, "w");
	fprintf(cmake1, "cmake_minimum_required(VERSION 3.19)\n\n");

	if(isC)
		fprintf(cmake1, "set(CMAKE_C_STANDARD 11)\n\n");
	else
		fprintf(cmake1, "set(CMAKE_CXX_STANDARD 17)\n\n");

	fprintf(cmake1, "proyect(%s)\n\n", proyectName);
	fprintf(cmake1, "set(SRC src)\n\n");
	fprintf(cmake1, "add_executable(${PROJECT_NAME} main.c)\n\n");
	fprintf(cmake1, "add_subdirectory(${SRC}/)");
	fprintf(cmake1, "target_include_directories(${PROJECT_NAME} PUBLIC ${SRC})\n\n");
	fprintf(cmake1, "target_link_directories(${PROJECT_NAME} PRIVATE ${SRC})\n\n");
	fprintf(cmake1, "target_link_libraries(${PROJECT_NAME} includes)");


	fclose(cmake1);


	cmake2 = fopen(cmakeList2, "w");
	fprintf(cmake2, "set(SRC ../src)\n\n");
	fprintf(cmake2, "AUX_SOURCE_DIRECTORY(${SRC}/ TARGET_SRC)\n");
	fprintf(cmake2, "add_library(includes %s ${TARGET_SRC})", fileName);

	fclose(cmake2);
	
	return true;
}


boolean createMakeFile(const boolean isC, const char* proyectName){

	const char* extensionsSrc[2] = {"cpp", "c"};
	FILE* makefile = fopen("Makefile.txt", "w");


	
	if(isC){
		fprintf(makefile, "CC = gcc\n");
		fprintf(makefile, "CXXFLAGS = -std=c11 -Wall -g\n");
	}
	else{
		fprintf(makefile, "CC = g++\n");
		fprintf(makefile, "CXXFLAGS = -std=cpp17 -Wall -g\n");
	}

	fprintf(makefile, "LDFLAGS =\n\n");
	fprintf(makefile, "MKDIR_P = mkdir -p\n\n");
	fprintf(makefile, "APPNAME = myApp.out\n");
	fprintf(makefile, "SRCDIR = includes\n");
	fprintf(makefile, "OBJDIR = obj\n");
	fprintf(makefile, "SRC = $(wildcard $(SRCDIR)/*.%s)\n", extensionsSrc[isC]);
	fprintf(makefile, "OBJ = $(SRC:$(SRCDIR)/%%.%s=$(OBJDIR)/%%.o)\n\n", extensionsSrc[isC]);
	fprintf(makefile, "RM = rm");
	fprintf(makefile, "all: $(APPNAME)\n");
	fprintf(makefile, "all: $(APPNAME)\n\n");
	fprintf(makefile, "$(APPNAME): $(OBJ)\n\t$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)\n\n\n");
	fprintf(makefile, "$(OBJDIR)/%%.o: $(SRCDIR)/%%.%s | obj\n\t$(CC) $(CXXFLAGS) -o $@ -c $<\n\n\n", extensionsSrc[isC]);
	fprintf(makefile, "obj:\n\t${MKDIR_P} ${OBJDIR}\n\n\n");
	fprintf(makefile, ".PHONY: clean\nclean:\n\t$(RM) $(DELOBJ) $(APPNAME)");

	fclose(makefile);
	return true;
}




static boolean checkFileExists(const char* nameFile){

	FILE* newFile = fopen(nameFile, "r");
	boolean exists = false;

	if(newFile)
		exists = true;

	fclose(newFile);
	return exists;
}


static void convertFileNameToMacro(char* macro, const char* nameFile){
	
	uint8_t i;

	puts(nameFile);
	for(i = 0; i < strlen(nameFile) - 1; i++){
		macro[i] = toupper(nameFile[i]);
	}
	
	macro[i] = toupper(nameFile[i]);
	macro[i + 1] = '_';
	macro[i + 2] = 'H';
	macro[i + 3] = '\0';

	puts(macro);
}
