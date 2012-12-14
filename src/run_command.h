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

#ifndef __RUN_COMMAND_H__
#define __RUN_COMMAND_H__

#include "generic.h"
#include <unistd.h>

void run_command(char *command_str, int in_fd, int out_fd, int wait_children);

#endif
