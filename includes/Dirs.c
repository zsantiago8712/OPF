#include "Dirs.h"
#include <stdio.h>
#include <sys/stat.h>



static boolean checkDirsExists(const char* nameDir);


boolean createDir(const char* nameDir){

	if(checkDirsExists(nameDir)){
		if(!getAnswer())
			return false;
	}
	
	mkdir(nameDir, 0777);
	puts("DIR CREADO!");
	return true;
}


static boolean checkDirsExists(const char* nameDir){

	DIR* dir = opendir(nameDir);
	if(!dir)
		return false;

	closedir(dir);
	return true;
}


