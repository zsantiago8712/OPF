#include "includes/OPF.h"

int main(int argc, char **argv){

	Configs confs = initConfigs();
	if (checkArguments(argc, (const char**) argv, confs)) {
		
		
	}

	confs = freeConfigs(confs);
	return 0;

}
