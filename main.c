#include "parameters.h"
#include "functions.h"

void get_input(){
	printf("lolz\n");
}

int main(int argc, char* argv[]){

	int running = 1;
	char path[PATH_LENGTH];
	char input_buffer[BUFFER_LENGTH];

	while(running){
		path = "/etc/lolz";
		printf("$ %s > ", path);

		get_input();

	}

	return 1;
}