#ifndef _SAVE_H_
#define _SAVE_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fileio.h"
#include "load.h"
#include "linked_list.h"


/**
 * Performs the cache memory access operation of save.  Increments the 
 * fields of counter appropriately based on the current state of the cache
 * and the current address.
 * 
 * @param cache an array of Sets, representing a cache
 * @param counter a counter containing fields tracking cache statistics
 * @param addr the memory address currently being accessed
 * @param size size of Mem[addr]
 * @param num_sets the number of sets in the cache
 * @param block_offset the block offset of the cache
 * @param printout a concatenated string printing the cache action in the verbose mode
 */
void save(Set *cache, Count *counter ,unsigned long addr, unsigned int size, int num_sets, int block_offset, char *printout);

#endif