#include "run_command.h"

void run_command(char *command_str, int in_fd, int out_fd, int wait_children)
{
    char **argv = NULL;
    int argc = 0;
    int first_glob_read = 0;

    int i = 0;
    glob_t globbuf;
    memset(&globbuf, 0, sizeof(glob_t));

    param_split(command_str, &argc, &argv);
    //argc the number of params
    for (i = 0; i < argc; i++){
        if (argv[i][0] != '-' &&
            (strchr(argv[i], '*') != NULL ||
             strchr(argv[i], '?') != NULL ||
             strchr(argv[i], '[') != NULL)){
        }else{
            globbuf.gl_offs++;
        }
    }
    //expand the globs
    for (i = 0; i < argc; i++){
        if (argv[i][0] != '-' &&
            (strchr(argv[i], '*') != NULL ||
             strchr(argv[i], '?') != NULL ||
             strchr(argv[i], '[') != NULL)){
            if (first_glob_read == 0){
                glob(argv[i], GLOB_DOOFFS, NULL, &globbuf);
                first_glob_read = 1;
            }else{
                glob(argv[i], GLOB_DOOFFS | GLOB_APPEND, NULL, &globbuf);
            }
        }
    }

    //globs found so globuff is ready and the params can be added
    if (first_glob_read == 1){
        //add the params
        int j = 0;
        for (i = 0; i < argc; i++){
            if (argv[i][0] != '-' &&
                (strchr(argv[i], '*') != NULL ||
                 strchr(argv[i], '?') != NULL ||
                 strchr(argv[i], '[') != NULL)){
            }else{
                globbuf.gl_pathv[j] = argv[i];
                j++;
            }
        }
    }

    int pid = vfork();
    if (pid == 0){
        if (out_fd != STDOUT_FILENO){
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }

        if (in_fd != STDIN_FILENO){
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }

        if (first_glob_read == 1){
            execvpe(globbuf.gl_pathv[0], globbuf.gl_pathv, NULL);
        }else{
            //no globs found, argv can be used directly
            execvpe(argv[0], argv, NULL);
        }

    }else if(wait_children){
        int state;
        wait(&state);
    }
    globfree(&globbuf);
    free_param_array(argc, &argv);
}
