#ifndef _INIT_CACHE_H_
#define _INIT_CACHE_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "linked_list.h"
#include "fileio.h"
#include "load.h"

/**
 * Initializes the cache based on the parameters passed in.
 * 
 * @param num_sets The number of sets the cache will contain
 * @param block_size The size of the block section of the line
 * @param lines_per_set The number of lines to be contained in each
 * cache line
 * 
 * @return an array of struct Set which represents a cache
 */
Set *init_cache(int num_sets, int block_size, int lines_per_set);

/**
 * Prints a representaton of the cache state in the format:
 *      Set s: Valid: v    Tag: t
 * 
 * This function is primarily used for debugging purposes.
 * 
 * @param cache an array representation of a cache
 * @param num_set the number of sets within the cache (ie. the size
 * of cache)
 * @param lines_per_set the number of lines in each set
 */
void cache_state(const Set *cache, int num_sets, int lines_per_set);

/**
 * Deconstructs an array of sets representing a cache.  Deallocates all
 * the memory within the structure that has been allocated to the heap.
 *
 * @param cache an array representation of a cache
 * @param num_sets the number of sets the cache contains
 */
void cache_deconstruct(Set *cache, int num_sets);

#endif
