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

#include "sleep.h"

void intr(int sig){
	// Does nothing.
}

int _sleep(char * seconds){
	signal(SIGALRM, &intr);
	alarm(atoi(seconds));

	pause();

	return 0;
}
