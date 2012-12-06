
#include "cd.h"

int _cd(char * directory){
	if (!directory || !strlen(directory)){
		return chdir(getenv("HOME"));
	}
	return chdir(directory);
}
