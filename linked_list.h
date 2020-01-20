#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"

/**
 * Inserts a new line into the implementation of the
 * linked list.
 * 
 * @param set an array of the struct Set
 * @param l new line to be inserted in the list
 * @param valid valid flag of line to be added
 * @param tag tag of line to be added
 */
void line_insert(Set *set, unsigned int valid, unsigned long tag);

/**
 * Removes the earliest inserted line in the linked list
 * (ie. the line at the bottom of the list).
 * 
 * @param set an array of the struct Set
 */
void line_remove(Set *set);

#endif
