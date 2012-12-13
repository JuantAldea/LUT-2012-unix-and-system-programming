#ifndef __HISTORY_H
#define __HISTORY_H

#include "generic.h"

typedef struct history history;
typedef struct history_entry history_entry;

struct history_entry{
	int id;
	char line[BUFFER_LENGTH];
	struct timeval timestamp;

	history_entry *previous;
	history_entry *next;
};

struct history{
	int max;
	int entries;

	int last_assigned;

	history_entry *first;
	history_entry *last;
};

history * new_history();
int add_history_entry(history *h, char *line);
history_entry * get_history_entry(history *h, int id);
int free_history(history *h);

void print_history(history *h);

#endif
