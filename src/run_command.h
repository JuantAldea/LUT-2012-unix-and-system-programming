#ifndef __RUN_COMMAND_H__
#define __RUN_COMMAND_H__

#include "generic.h"

void run_command(char *command_str, int in_fd, int out_fd, int wait_children);

#endif
