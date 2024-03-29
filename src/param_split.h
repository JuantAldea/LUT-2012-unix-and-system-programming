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

#ifndef __PARAM_SPLIT_H__
#define __PARAM_SPLIT_H__

#include <string.h>
#include <stdlib.h>

//#define __PARAM_SPLIT_TEST__
#ifdef __PARAM_SPLIT_TEST__
    #include <stdio.h>
#endif

#define MAX_PARAM_LENGTH 1024

void param_split(char *command_str, int *argc, char ***argv);
void free_param_array(int argc, char ***argv);

#endif
