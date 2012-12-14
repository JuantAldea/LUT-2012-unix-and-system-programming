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

#include "param_split.h"
#include <stdio.h>
void param_split(char *command_str, int *argc, char ***argv)
{
    *argc = 0;
    char buffer[MAX_PARAM_LENGTH];
    memset(buffer, 0, MAX_PARAM_LENGTH);
    memcpy(buffer, command_str, strlen(command_str));

    //count the number of params
    char *offset = strtok(buffer, " ");
    while(offset != NULL){
        (*argc)++;
        offset = strtok(NULL, " ");
    }

    //add an empty null pointer at the end to mark the end of the argv vector
    //since exec family count calculates argc like this
    // while (argv[argc++]) ;
    *argv = malloc(sizeof(char **) * (*argc + 1));
    memset(*argv, 0, ((*argc) + 1)*sizeof(char**));

    memcpy(buffer, command_str, strlen(command_str));
    //count the number of params
    offset = strtok(buffer, " ");
    int current_param = 0;
    while(offset != NULL){
        (*argv)[current_param] = strdup(offset);
        current_param++;
        offset = strtok(NULL, " ");
    }
}

void free_param_array(int argc, char ***argv)
{
    int i;
    for (i = 0; i < argc; i++){
        free((*argv)[i]);
    }
    free(*argv);
    *argv = NULL;
}


#ifdef __PARAM_SPLIT_TEST__

int main(int argc, char **argv)
{
    char a[] = "Puedo escribir los versos mas tristes esta noche,    escribir, por ejemplo, la noche esta estrellada y tiritan   azules los astros, a lo lejos.";
    int number_of_params = 0;
    char **params = NULL;
    param_split(a, &number_of_params, &params);
    int i;

    for (i = 0; i < number_of_params; i++){
        printf("Param %d: %s\n", i, params[i]);
    }

    free_param_array(number_of_params, &params);
    return 1;
}

#endif //__SPLIT_TEST__
