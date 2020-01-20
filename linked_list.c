#include "linked_list.h"
//Double linked list implementation of the list
//ADT

void line_remove(Set *set) {
	Line *temp = NULL;
	//edge case: set is empty
	if(set->head == NULL || set->tail == NULL) 
		return;
	//edge case: set contains a single line
	if(set->head == set->tail)
		set->head = (set->tail)->next;
	//standard line insertion step
	if((set->tail)->prev != NULL) {
		(set->tail)->prev->next = (set->tail)->next;
		temp = (set->tail)->prev;
	}
	free(set->tail);
	set->tail = temp;
	return;
}

void line_insert(Set *set, unsigned int valid, unsigned long tag) {
	//construct new line
	Line *l = calloc(1, sizeof(Line));
	l->valid = valid;
	l->tag = tag;
	//edge case: list is empty
	if(set->head == NULL) {
		l->next = NULL;
		l->prev = NULL;
		set->head = l;
		set->tail = l;
	} 
	else {
		//standard case
		set->head->prev = l;
		l->next = set->head;
		set->head = l;
	}
}

