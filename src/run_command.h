#ifndef __RUN_COMMAND_H__
#define __RUN_COMMAND_H__


#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <glob.h>

#include  "param_split.h"

void run_command(char *command_str, int in_fd, int out_fd, int wait_children);

#endif
