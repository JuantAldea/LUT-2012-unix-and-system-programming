#include "param_split.h"

void param_split(char *command_str, int *argc, char ***argv)
{
    *argc = 0;
    char buffer[MAX_PARAM_LENGTH];
    memset(buffer, 0, MAX_PARAM_LENGTH);
    memcpy(buffer, command_str, strlen(command_str));

    char *offset = strtok(buffer, " ");
    //count the number of params
    while(offset != NULL){
        //printf("Param %d: %s\n", *argc, offset);
        (*argc)++;
        offset = strtok(NULL, " ");
    }

    char **argv_array = malloc(sizeof(char **) * (*argc));
    
    memcpy(buffer, command_str, strlen(command_str));    
    offset = strtok(buffer, " ");
    //count the number of params
    int current_param = 0;
    while(offset != NULL){
        argv_array[current_param] = strdup(offset);
        current_param++;
        offset = strtok(NULL, " ");
    }

    *argv = argv_array;
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
