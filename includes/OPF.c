#include "OPF.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


static boolean setConfigurations(const char** args, Configs confs);
static boolean checkNumArgs(const int numArgs);

struct _Configs{

	char* nameProyectFile;
	boolean isProyect;
	boolean isC;
	boolean isCmake;
	boolean noBuild;

};




Configs initConfigs(void){

	Configs newConfigs = malloc(sizeof(struct _Configs));

	newConfigs->isProyect = false;
	newConfigs->isC = false;
	newConfigs->isCmake = false;
	newConfigs->noBuild = false;
	newConfigs->nameProyectFile = "\0";

	return newConfigs;
}


Configs freeConfigs(Configs confs){

	free(confs->nameProyectFile);
	confs->nameProyectFile = NULL;

	free(confs);
	confs = NULL;

	return confs;
}



boolean checkArguments(const int numArgs, const char** args, Configs confs){

	if(checkNumArgs(numArgs) && setConfigurations(args, confs)) 
		return true;

	return false;
}




/*	Checa que el numero de argumentos se ha correcto
 *	!Importane El orden de los argumentos no son importantes excepto el nombre del arhcio o proyecto ese 
 *		siempre debe de ir al final
 *
 *	1) El nombre del ejecutable --> ese no se toma en cuenta
 *	2) P -> Proyecto // F -> File(archivo)
 *	3) C // C++
 *	4) M -> MakeFile // CM --> CMAKE --> si se escogio archivo estos no se tomaran en cuenta
 *	5) Nombre del archivo o proyecto
 */
static boolean checkNumArgs(const int numArgs){
	
	if(numArgs > 5 || numArgs < 5)
		return false;

	return true;
}


static boolean setConfigurations(const char** args, Configs confs){

	boolean argumentConfigured = false;
	for(uint8_t i = 1; i < 4; i++){
		
		if(strcmp(args[i], "P") == 0){
			confs->isProyect = true;
			confs->noBuild = false;
			argumentConfigured = true;
		}
		else if(strcmp(args[i], "F") == 0){
			confs->isProyect = false;
			confs->noBuild = true;
			argumentConfigured = true;
		}

		if(strcmp(args[i], "C") == 0){

			confs->isC = true;
			argumentConfigured = true;
		}
		else if(strcmp(args[i], "+") == 0){

			confs->isC = false;
			argumentConfigured = true;
		}
	
		if(strcmp(args[i], "M") == 0 && !confs->noBuild){
			confs->isCmake = false;	
			argumentConfigured = true;
		}
		else if(strcmp(args[i], "CM") == 0 && !confs->noBuild){
			confs->isCmake = true;
			argumentConfigured = true;
		}
	
		if(!argumentConfigured)
			return false;

	}

	confs->nameProyectFile = strdup(args[4]);
	return true;
}





boolean getAnswer(void){
	char answer = 'q';

	while (answer != 'y' || answer != 'n') {
		SYSCLEAR
		printf("Ya existe un archivo con ese nombre, seguro quieres reesecibirlo (Se perdera todo lo que tenga dentro!) [Y/N]\n");
		scanf("%c", &answer);
	}

	if(answer == 'n')
		return false;
	return true;
}
