#include "Files.h"
#include <stdio.h>


static boolean checkFileExists(const char* nameFile);
static FILE* openFile(const char* nameFile);
static void convertFileNameToMacro(char* macro, const char* nameFile);


boolean createSrcFile(const boolean isC, const boolean isProyect,const char* fileName){

	const char* extensionsSrc[2] = {"c", "cpp"};
	const char* extensionsHeader[2] = {"h", "hpp"};
	char answer;
	char newNameFile[BUFSIZ];
	FILE* file;

	if(isProyect)
		sprintf(newNameFile, "includes/%s.%s", fileName, extensionsSrc[isC]);
	else 
		sprintf(newNameFile, "%s.%s", fileName, extensionsSrc[isC]);

	if(checkFileExists(newNameFile)){

		if(!getAnswer())
			return false;
	}		
	
	file = openFile(newNameFile);
	
	fprintf(file, "#include <stdio.h>\n#include<stdlib.h>\n");
	if(!isProyect)
		fprintf(file, "int main(int argc, char** argv){\n\n\nreturn 0\n}");
	else
		fprintf(file, "#include \"%s.%s\"\n", fileName, extensionsHeader[isC]);

	fclose(file);
	return true;
}

boolean createHeaderFile(const boolean isC, const char* fileName){

	const char* extensionsHeader[2] = {"h", "hpp"};
	char answer;
	char newNameFile[BUFSIZ];
	char macrofileName[BUFSIZ];
	FILE* file;

	sprintf(newNameFile, "includes/%s.%s", fileName, extensionsHeader[isC]);
	convertFileNameToMacro(macrofileName, fileName);

	if(checkFileExists(newNameFile)){

		if(!getAnswer())
			return false;
	}		
	
	file = openFile(newNameFile);
	
	fprintf(file, "#ifndef %s\n", macrofileName);
	fprintf(file, "#define %s\n\n\n", macrofileName);
	fprintf(file, "#endif //%s\n", macrofileName);
	fprintf(file, "#include <stdio.h>\n#include<stdlib.h>\n");

	fclose(file);
	return true;
}


boolean createCMakeFiles(const char* proyectName){

	
	FILE* cmake1, *cmake2;
	char cmakeList1[BUFSIZ], cmakeList2[BUFSIZ];

	sprintf(cmakeList1, "%s/CMakeLists.txt", proyectName);
	sprintf(cmakeList2, "%s/includes/CMakeLists.txt", proyectName);

	cmake1 = fopen(cmakeList1, "w");
	fprintf(cmake1, "");	
	fclose(cmake1);


	cmake2 = fopen(cmakeList2, "w");

	fclose(cmake2);
	
	return true;
}



static FILE* openFile(const char* nameFile){

	FILE* newFile = fopen(nameFile, "w"); 
	
	return newFile;
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
	for(i = 0; i < strlen(nameFile); i++)
		macro[i] = toupper(nameFile[i]);
	
	macro[i + 1] = '_';
	macro[i + 2] = 'H';
	macro[i + 3] = '\0';

}
