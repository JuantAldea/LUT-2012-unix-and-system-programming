#include "run_command.h"

void run_command(char *command_str, int in_fd, int out_fd, int wait_children)
{
    char **argv;
    int argc;
    param_split(command_str, &argc, &argv);
    int pid = vfork();
    if (pid == 0){
        dup2(out_fd, STDOUT_FILENO);
        dup2(in_fd, STDIN_FILENO);
        close(out_fd);
        close(in_fd);
        execvpe(argv[0], &argv[0], NULL);
    }else if(wait_children){
        int state;
        wait(&state);
    }
    free_param_array(argc, &argv);
}
