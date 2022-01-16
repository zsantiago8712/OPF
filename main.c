#include "includes/OPF.h"
#include "includes/Dirs.h"
#include "includes/Files.h"
#include <stdio.h>

int main(int argc, char **argv){

	Configs confs = initConfigs();
	char includesDir[BUFSIZ];
	if (checkArguments(argc, (const char**) argv, confs)) {
		
		if(!getIsProyect(confs)){
			createSrcFile(getIsC(confs), false, getNameProyectFile(confs));
		}else{

			createDir(getNameProyectFile(confs));
			sprintf(includesDir, "%s/includes", getNameProyectFile(confs));
			createDir(includesDir);

			if(getIsCmake(confs)){
				createCMakeFiles(getIsC(confs), getNameProyectFile(confs));
				createMainProyect(getIsC(confs), getNameProyectFile(confs));
			}
			else
				createMakeFile(getIsC(confs), getNameProyectFile(confs));

			createSrcFile(getIsC(confs), true, getNameProyectFile(confs));
			createHeaderFile(getIsC(confs), getNameProyectFile(confs));
		}
		
	}

	confs = freeConfigs(confs);
	return 0;

}
