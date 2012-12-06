#include "generic.h"

int get_command(char * input_buffer, int * parameters_index){
	if (!strncmp(input_buffer, CMD_LS, strlen(CMD_LS)) && input_buffer[strlen(CMD_LS) == ' ']){
		*parameters_index = strlen(CMD_LS) + 1;
		return COD_LS;
	} else if (!strncmp(input_buffer, CMD_CD, strlen(CMD_CD)) && input_buffer[strlen(CMD_CD) == ' ']){
		*parameters_index = strlen(CMD_CD) + 1;
		return COD_CD;
	} else {
		*parameters_index = -1;
		return COD_ERROR;
	}
}

int main(int argc, char* argv[]){

	int running = 1;
	char path[MAXPATHLEN]; // MAXPATHLEN as defined in sys/params.h
	char input_buffer[BUFFER_LENGTH];

	while(running){
		getwd(path);
		printf("$ %s > ", path);

		fgets(input_buffer, BUFFER_LENGTH, stdin);
		input_buffer[strlen(input_buffer) - 1] = '\0';

		int parameters_index;

		switch (get_command(input_buffer, &parameters_index)){
			case COD_LS:
				break;
			case COD_CD:
				cd(&input_buffer[parameters_index]);
				break;
			case COD_ERROR:
				printf("Command not recogniced.\n");
				break;
		}
	}

	return 1;
}
