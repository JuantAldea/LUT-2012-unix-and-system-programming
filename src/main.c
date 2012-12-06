#include "generic.h"

int get_command(char * input_buffer, int * parameters_index){

	fgets(input_buffer, BUFFER_LENGTH, stdin);
	input_buffer[strlen(input_buffer) - 1] = '\0';

	if (!strncmp(input_buffer, CMD_LS, strlen(CMD_LS)) && input_buffer[strlen(CMD_LS) == ' ']){
		*parameters_index = strlen(CMD_LS) + 1;
		return COD_LS;
	} else if (!strncmp(input_buffer, CMD_CD, strlen(CMD_CD)) && input_buffer[strlen(CMD_CD) == ' ']){
		*parameters_index = strlen(CMD_CD) + 1;
		return COD_CD;
	} else if (!strncmp(input_buffer, CMD_SLEEP, strlen(CMD_SLEEP)) && input_buffer[strlen(CMD_SLEEP) == ' ']){
		*parameters_index = strlen(CMD_SLEEP);
		return COD_SLEEP;
	} else {
		*parameters_index = -1;
		return COD_ERROR;
	}
}

int main(int argc, char* argv[]){

	int running = 1;
	char path[MAXPATHLEN]; // MAXPATHLEN as defined in sys/params.h
	char input_buffer[BUFFER_LENGTH];
	int parameters_index;

	while(running){
		getwd(path);
		printf("$ %s > ", path);

		switch (get_command(input_buffer, &parameters_index)){
			case COD_LS:
				break;
			case COD_CD:
				_cd(&input_buffer[parameters_index]);
				break;
			case COD_SLEEP:
				_sleep(&input_buffer[parameters_index]);
				break;
			case COD_ERROR:
				printf("Command not recogniced.\n");
				break;
		}
	}

	return 1;
}
