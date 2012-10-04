/*
###############################################
#   CT50A3000 - Unix and System Programming   #
#         Pre-assignment: Linked List         #
#   Juan Antonio Aldea Armenteros (0404450)   #
#        juan.aldea.armenteros@lut.fi         #
#                  linked_list.h              #
###############################################
*/

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct node_s node_t;
struct node_s {
	//void *payload;
	int number;
	char *string;
	node_t *next;
	node_t *previous;
};

typedef struct linked_list_s linked_list_t;
struct linked_list_s {
	node_t *head;
	node_t *tail;
	int count;
};

void list_init(linked_list_t *list);

void list_add_first(node_t *n, linked_list_t *list);
void list_add_last (node_t *n, linked_list_t *list);

void list_free(linked_list_t *list);
void list_clear(linked_list_t *list);
void list_remove_node(node_t *n, linked_list_t *list);

node_t *list_create_node(int number, char *string);

void list_print(linked_list_t *list);
void list_reverse_print(linked_list_t *list);

#endif
