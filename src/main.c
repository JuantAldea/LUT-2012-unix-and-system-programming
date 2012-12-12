#include "generic.h"

int builtin_command(char *input_buffer, int *parameters_index){

    if (!strncmp(input_buffer, CMD_CD, strlen(CMD_CD)) && input_buffer[strlen(CMD_CD) == ' ']){
        *parameters_index = strlen(CMD_CD) + 1;
        return COD_CD;
    } else if (!strncmp(input_buffer, CMD_HISTORY, strlen(CMD_HISTORY))){
        *parameters_index = -1;
        return COD_HISTORY;
    } else if (!strncmp(input_buffer, CMD_HISTORY_ID, strlen(CMD_HISTORY_ID))){
        *parameters_index = strlen(CMD_HISTORY_ID);
        return COD_HISTORY_ID;
    } else {
        *parameters_index = -1;
        return COD_ERROR;
    }
}


int find_first_redirector(char *command){
    int i;
    for (i = 0; i < strlen(command); ++i){
        if (command[i] == '<' || command[i] == '>'){
            return i;
        }
    }
    return i+1;
}


int main(int argc, char* argv[]){

    int running = 1;
    char path[MAXPATHLEN]; // MAXPATHLEN as defined in sys/params.h

    history *h = new_history();

    int input_pipe = 0;
    int output_pipe = 0;

    while(running){
        getwd(path);
        printf("$ %s > ", path);

        char partial_buffer[BUFFER_LENGTH];
        int parameters_index;

        fgets(partial_buffer, BUFFER_LENGTH, stdin);
        partial_buffer[strnlen(partial_buffer, BUFFER_LENGTH) - 1] = '\0';

        char input_buffer[BUFFER_LENGTH];
        memset(input_buffer, 0, BUFFER_LENGTH);

        char temp_buffer[BUFFER_LENGTH];
        char temp2_buffer[BUFFER_LENGTH];

        strcpy(temp2_buffer, partial_buffer);

        while(strchr(partial_buffer, '!') != NULL){
            memset(temp_buffer, 0, BUFFER_LENGTH);
            memset(temp2_buffer, 0, BUFFER_LENGTH);
            int id;

            if (partial_buffer[0] == '!'){
                sscanf(partial_buffer, "!%d%[^\t\n]", &id, temp2_buffer);
            } else {
                sscanf(partial_buffer, "%[^!]!%d%[^\t\n]", temp_buffer, &id, temp2_buffer);
            }

            printf("%s - %d - %s\n", temp_buffer, id, temp2_buffer);

            strcat(input_buffer, temp_buffer);
            history_entry *he;
            if((he = get_history_entry(h, id))){
                strcat(input_buffer, he->line);
                strcat(input_buffer, " ");
            }

            strcpy(partial_buffer, temp2_buffer);
        }

        strcat(input_buffer, temp2_buffer);

        memset(temp_buffer, 0, BUFFER_LENGTH);
        memset(temp2_buffer, 0, BUFFER_LENGTH);

        printf("%s\n", input_buffer);
        add_history_entry(h, input_buffer);

        char *command = NULL;
        command = strtok(input_buffer, "|");

        while (command != NULL){
            printf("%s\n", command);
            int command_code = builtin_command(command, &parameters_index);

            int using_input_redirection = 0;
            char input_redirection[MAXPATHLEN];
            int using_output_redirection = 0;
            char output_redirection[MAXPATHLEN];

            int out_descriptor = STDOUT_FILENO;
            int in_descriptor = STDIN_FILENO;

            char *redirector;

            if ((redirector = strchr(command, '<'))){
                sscanf(redirector, "<%s>%*s", input_redirection);
                using_input_redirection = 1;
                printf("Redirección de entrada: |%s|\n", input_redirection);

                int in = open(input_redirection, O_RDONLY, S_IRUSR|S_IWUSR);
                if (in > 0){
                    in_descriptor = in;
                }else{
                    printf("ERROR\n");
                }
            }

            if ((redirector = strchr(command, '>'))){
                sscanf(redirector, ">%s<%*s", output_redirection);
                using_output_redirection = 1;
                printf("Salida: |%s|\n", output_redirection);

                int out = open(output_redirection, O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR);
                if (out > 0){
                    out_descriptor = out;
                }else{
                    printf("ERROR\n");
                }
            }

            switch (command_code){
                case COD_CD:
                    _cd(&command[parameters_index]);
                    break;
                case COD_HISTORY:
                    print_history(h);
                    break;
                default:
                    run_command(command, in_descriptor, out_descriptor, 1);
                    break;
            }

            command = strtok (NULL, "|");
        }

    }

    return 1;
}
