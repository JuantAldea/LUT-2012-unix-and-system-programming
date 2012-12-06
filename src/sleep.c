
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
