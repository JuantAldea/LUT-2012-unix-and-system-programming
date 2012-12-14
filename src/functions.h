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

#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

// Command codes

#define COD_ERROR -1 // Error command code

#include "cd.h"
#define COD_CD 0
#define CMD_CD "cd"

#include "history.h"
#define COD_HISTORY 1
#define CMD_HISTORY "history"
#define COD_HISTORY_ID 2
#define CMD_HISTORY_ID "!"


#include "run_command.h"

#endif
