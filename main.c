
/*
###############################################
#   CT50A3000 - Unix and System Programming   #
#         Pre-assignment: Linked List         #
#   Juan Antonio Aldea Armenteros (0404450)   #
#        juan.aldea.armenteros@lut.fi         #
#                      main.c                 #
###############################################
*/

#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

int main(void)
{
	linked_list_t *list = (linked_list_t*)malloc(sizeof(linked_list_t));
	list_init(list);

	for (int i = 0; i < 10; i++){
		char string[100];
		sprintf(string, "Number: %d", i);
		list_add_first(list_create_node(i, string), list);
		list_add_last (list_create_node(i, string), list);
	}

	printf("Non-empty list\n");
	list_print(list);

	list_clear(list);

	printf("Empty list\n");
	list_print(list);

	list_free(list);
	free(list);
	return 0;
}
