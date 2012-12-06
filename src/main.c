#include "parameters.h"
#include "functions.h"
#include "generic.h"

int main(int argc, char* argv[]){

	int running = 1;
	char path[PATH_LENGTH];
	char input_buffer[BUFFER_LENGTH];

	while(running){
		strcpy(path, "/etc/lolz");
		printf("$ %s > ", path);

		fgets(input_buffer, BUFFER_LENGTH, stdin);
		printf("Lo que has escrito rulea: %s", input_buffer);
	}

	return 1;
}
