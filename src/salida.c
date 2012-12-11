#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "run_command.h"

int main(int argc, char **argv)
{
    int pid = -1;
    if ((pid = fork()) == 0){
        int destination = open("broza", O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR);
        //dup2(destination, STDOUT_FILENO);
        //close(destination);
        run_command("ls -la", STDIN_FILENO, destination, 1);
    }else if (pid > 0){
        int status;
        printf("ESPERANDO %d\n", pid);

        wait(&status);
        printf("SALIENDO\n");
    }else{
        printf("ERROR\n");
    }
}

/*
int out_descriptor = STDOUT_FILENO;
int in_descriptor = STDIN_FILENO;
int previous_piped = 0;
int next_piped = 0;

char out_file[] = "out";
char in_file[] = "in";

if (redirect_in){
    int in = open(in_file, O_RDONLY, S_IRUSR|S_IWUSR);
    //close(pipe);
    if (in > 0){
        in_descriptor = in;
    }else{
        printf("ERROR\n");
    }
}else if(previous_piped){
    //redirect_in = pipe;
}

if (redirect_out){
    int out = open(on_file, O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR);
    //close(pipe);
    if (out > 0){
        redirect_out = out;
    }else{
        printf("ERROR\n");
    }
}else if (next_piped){
    //redirect_out = pipe
}

//run_command(...);
*/