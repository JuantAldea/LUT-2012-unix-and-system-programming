/*******************************************************************\
 *                                                                 *
 *             CT50A3000 - Unix and System Programming             *
 *                                                                 *
 *    Shell Project                                                *
 *                                                                 *
 *    Authors:                                                     *
 *        Juan Antonio Aldea Armenteros - 0404450                  *
 *        Pablo Caro Martin - 0404489                              *
 *                                                                 *
\*******************************************************************/

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

void get_command(char *buffer, history *h){
    char ch = getchar();
    int w = 0;
    int w_max = 0;

    int y = 0;
    history_entry *t = h->last;

    char w_buffer[BUFFER_LENGTH];

    while (ch != '\r' && ch != '\n'){
        if (ch == 27){
            if (getchar() == 91){
                ch = getchar();

                if (ch == 65){ // Up
                    if (y < MAX_HISTORY_LENGTH && y < h->entries){
                        if (y == 0){
                            strcpy(w_buffer, buffer);
                        }
                        y++;
                        strcpy(buffer, t->line);
                        for (int i = w; i < w_max; ++i){
                            printf(" ");
                        }
                        for (int i = 0; i < w; ++i){
                            printf("\b \b");
                        }
                        w = w_max = strlen(buffer);
                        printf("%s", buffer);
                        t = t->previous;
                    }
                } else if (ch == 66){ // Down
                    if (y == 1){
                        y = 0;
                        strcpy(buffer, w_buffer);
                        for (int i = w; i < w_max; ++i){
                            printf(" ");
                        }
                        for (int i = 0; i < w; ++i){
                            printf("\b \b");
                        }
                        w = w_max = strlen(buffer);
                        printf("%s", buffer);

                    } else if (y > 1){
                        y--;
                        t = t->next;
                        strcpy(buffer, t->line);
                        for (int i = w; i < w_max; ++i){
                            printf(" ");
                        }
                        for (int i = 0; i < w; ++i){
                            printf("\b \b");
                        }
                        w = w_max = strlen(buffer);
                        printf("%s", buffer);
                    }
                } else if (ch == 67){ // Right
                    if (w < w_max){
                        printf("%c", buffer[w]);
                        w++;

                    }
                } else if (ch == 68){ // Left
                    if (w > 0){
                        w--;
                        printf("\b");
                    }
                }
            }
        } else if (ch == 0x7f){
            if (w > 0){
                w--;
                w_max--;
                buffer[w] = '\0';
                printf("\b \b");
            }

        } else if (isprint(ch)){
            buffer[w] = ch;
            w++;
            w_max++;
            printf("%c", ch);
        }

        buffer[w_max] = '\0';

        ch = getchar();
    }
    printf("\r\n");
}


int main(int argc, char* argv[]){

    struct termios term, old;

    /* Get current terminal attributes. */
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("tcgetattr");
        exit(1);
    }

    old = term;

    // term.c_iflag &= ~(INLCR | ICRNL | ISTRIP | IXON);
    term.c_lflag &= ~(ICANON | ECHO);
    // term.c_oflag &= ~OPOST;

    /* One byte at a time input (MIN=1, TIME=0). */
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;

    int running = 1;
    char path[MAXPATHLEN]; // MAXPATHLEN as defined in sys/params.h

    history *h = new_history();

    while(running){
        getcwd(path, MAXPATHLEN);
        printf("[%s:%s]$ ", getenv("USER"), path);

        char partial_buffer[BUFFER_LENGTH];
        memset(partial_buffer, 0, BUFFER_LENGTH);
        int parameters_index;

        // fgets(partial_buffer, BUFFER_LENGTH, stdin);
        // partial_buffer[strnlen(partial_buffer, BUFFER_LENGTH) - 1] = '\0';

        if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) {
            perror("tcsetattr");
            exit(1);
        }

        get_command(partial_buffer, h);

        if (tcsetattr(STDIN_FILENO, TCSANOW, &old) == -1) {
            perror("tcsetattr");
            exit(1);
        }

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

        add_history_entry(h, input_buffer);
        dump_history(h);
        char *input_buffer_end = &input_buffer[strlen(input_buffer) + 1];


        int previous_pipes[2] = {-1, -1};
        int next_pipes[2] = {-1, -1};

        char *command = NULL;
        char *strtok_status = NULL;
        command = strtok_r(input_buffer, "|", &strtok_status);
        int first_command = 1;
        int last_command = 0;
        while (command != NULL){
            int command_end = strlen(command);

            //check if it is the last command
            if (&(command[command_end + 1]) == input_buffer_end){
                last_command = 1;
            }else{
                //if it is not, we need a pipe
                pipe(next_pipes);
            }

            // fprintf(stderr, "Current command: %s\n", command);

            int command_code = builtin_command(command, &parameters_index);

            int using_input_redirection = 0;
            char input_redirection[MAXPATHLEN];
            int using_output_redirection = 0;
            char output_redirection[MAXPATHLEN];

            int out_descriptor = STDOUT_FILENO;
            int in_descriptor = STDIN_FILENO;

            char *redirector;

            if ((redirector = strchr(command, '<'))){
                //if the input is redirected, the pipe is ignored, so close the pipe
                if (previous_pipes[0] != -1){
                    close(previous_pipes[0]);
                    previous_pipes[0] = -1;
                }
                sscanf(redirector, "<%s>%*s", input_redirection);
                using_input_redirection = 1;

                int in = open(input_redirection, O_RDONLY, S_IRUSR|S_IWUSR);
                if (in > 0){
                    in_descriptor = in;
                }else{
                    printf("ERROR\n");
                }
            }else if(!first_command){
                //if the current command is not the first, then we have an open pipe
                in_descriptor = previous_pipes[0];
            }else{
                // fprintf(stderr, "First command: %s\n", command);
                //if the current command is the first and it does not have redirection for input,7
                //then the input is STDIN_FILENO
                in_descriptor = STDIN_FILENO;
            }

            if ((redirector = strchr(command, '>'))){
                //if the output is redirected, the pipe is ignored, so close the pipe
                if (next_pipes[1] != -1){
                    close(next_pipes[1]);
                    next_pipes[1] = -1;
                }
                sscanf(redirector, ">%s<%*s", output_redirection);
                using_output_redirection = 1;

                int out = open(output_redirection, O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR);
                if (out > 0){
                    out_descriptor = out;
                }else{
                    printf("ERROR\n");
                }
            }else if(!last_command){
                //if the current command is not the last, then we need need to write to the pipe
                out_descriptor = next_pipes[1];
            }else{
                //if the current command is the last one and it does not have output redirection
                //then the output goes to STDOUT_FILENO
                // fprintf(stderr, "Last command: %s\n", command);
                out_descriptor = STDOUT_FILENO;
            }

            if (using_input_redirection || using_output_redirection){
                for (int i = 0; i < strlen(command); ++i){
                    if (command[i] == '>' || command[i] == '<'){
                        command[i] = '\0';
                    }
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
                    // fprintf(stderr, "Descriptores: %d %d\n", in_descriptor, out_descriptor);
                    run_command(command, in_descriptor, out_descriptor, 1);
                    break;
            }

            //close output_pipe
            if (next_pipes[1] != -1){
                close(next_pipes[1]);
                next_pipes[1] = -1;
            }
            //close input_pipe
            if (previous_pipes[0] != -1){
                close(previous_pipes[0]);
                previous_pipes[0] = -1;
            }

            if (in_descriptor != STDIN_FILENO && in_descriptor != -1){
                close(in_descriptor);
                in_descriptor = -1;
            }
            if (out_descriptor != STDOUT_FILENO && out_descriptor != -1){
                close(out_descriptor);
                out_descriptor = -1;
            }
            //the input of the next program will be the out_pipe
            //created during the current iteration
            previous_pipes[0] = next_pipes[0];

            command = strtok_r (NULL, "|", &strtok_status);
            first_command = 0;
        }
         //close output_pipe
        if (next_pipes[1] != -1){
            close(next_pipes[1]);
            next_pipes[1] = -1;
        }

        if (next_pipes[0] != -1){
            close(next_pipes[0]);
            next_pipes[0] = -1;
        }

        //close input_pipe
        if (previous_pipes[0] != -1){
            close(previous_pipes[0]);
            previous_pipes[0] = -1;
        }

        //close input_pipe
        if (previous_pipes[1] != -1){
            close(previous_pipes[1]);
            previous_pipes[1] = -1;
        }
    }

    return 1;
}
