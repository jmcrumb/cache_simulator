#ifndef _LOAD_H_
#define _LOAD_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fileio.h"
#include "linked_list.h"

//Calculation for extracting a set number from an address
#define SET ((addr&set_mask) >> (block_offset))
//Calculation for extracting a tag from an address
#define TAG (addr >> (num_sets+block_offset))
//Calculation for extracting a block from an address
#define BLOCK (addr&block_mask)
//boolean stand-ins for clarity
#define TRUE 1
#define FALSE 0

/**
 * Performs the cache memory access operation of load.  Increments the 
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
void load(Set *cache, Count *counter ,unsigned long addr, unsigned int size, int num_sets, int block_offset, char *printout);

/**
 * Constructs masks based on the cache parameters.
 * 
 * @param addr the memory address currently being accessed
 * @param num_sets the number of sets in the cache
 * @param block_offset the block offset of the cache
 * @param set_mask location to put the resulting set mask
 * @param block_mask location to put the resulting set mask
 * @param tag_mask location to put the resulting tag mask
 */
void get_masks(unsigned long addr, int num_sets, int block_offset, unsigned long *set_mask, unsigned long *block_mask, unsigned long *tag_mask);

/**
 * Checks the tag of the address against the tags currently stored in the cache.  Registers
 * the cache access as a hit, miss, or miss eviction.
 * 
 * @param cache an array of Sets, representing a cache
 * @param set_num the number of sets in the cache
 * @param counter a counter containing fields tracking cache statistics
 * @param tag tag of a set line
 * @param printout a concatenated string printing the cache action in the verbose mode
 * @param line a line within a set of a cache
 * 
 * @return 1 upon conclusive hit or miss. 0 if not.
 */
int tag_check(Set *cache, unsigned long set_num, Count *counter, unsigned long tag, char *printout, Line *line);

#endif