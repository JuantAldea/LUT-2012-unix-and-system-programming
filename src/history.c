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

#include "history.h"

history * new_history(){
	history *h = (history*)malloc(sizeof(history));

	h->max = MAX_HISTORY_LENGTH;
	h->entries = 0;
	h->last_assigned = 0;

	h->first = NULL;
	h->last = NULL;

	char buffer[BUFFER_LENGTH];
	FILE *history_file = fopen(HISTORY_FILE, "r");
	if (history_file){
		while(fgets(buffer, BUFFER_LENGTH, history_file)){
			buffer[strnlen(buffer, BUFFER_LENGTH)-1] = '\0';
			add_history_entry(h, buffer);
		}

		fclose(history_file);
	}

	return h;
}

int add_history_entry(history *h, char *line){
	history_entry *previous = h->last;
	if (h->entries < h->max){ // History not full
		if (h->entries == 0){ // Empty history
			h->first = (history_entry*)malloc(sizeof(history_entry));
			h->last = h->first;
			previous = h->first;
		} else { // Still not full
			h->last->next = (history_entry*)malloc(sizeof(history_entry));
			h->last = h->last->next;
		}
		h->entries++;
	} else { // Full history
		h->first = h->first->next;
		h->last = h->last->next;
	}

	h->last_assigned++;

	h->last->id = h->last_assigned;
	strncpy(h->last->line, line, BUFFER_LENGTH);
	gettimeofday(&(h->last->timestamp), NULL);
	h->last->next = h->first;
	h->last->previous = previous;

	return h->entries;
}

history_entry * get_history_entry(history *h, int id){

	history_entry *t = h->first;
	for (int i = 0; i < h->entries; ++i){
		if (t->id == id){
			return t;
		}
		t = t->next;
	}

	return NULL;
}

int free_history(history *h){
	history_entry *t = h->first;
	for (int i = 0; i < h->entries; ++i){
		free(h->first);
		t = t->next;
		h->first = t;
	}
	h->entries = 0;
	h->first = NULL;
	h->last = NULL;
	return 0;
}

void print_history(history *h){
	history_entry *t = h->first;
	for (int i = 0; i < h->entries; ++i){
		printf("%*d  %s\n", 6, t->id, t->line);
		t = t->next;
	}
}

void dump_history(history *h){
	FILE *history_file = fopen(HISTORY_FILE, "w");
	history_entry *t = h->first;

	for (int i = 0; i < h->entries; ++i){
		fputs(t->line, history_file);
		fputs("\n", history_file);
		t = t->next;
	}

	fclose(history_file);
}