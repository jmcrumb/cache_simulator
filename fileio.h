#ifndef _FILEIO_H_
#define _FILEIO_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//define maximum size
#define MAXSIZE 30

/**
 * Structural representation of a single line of a 
 * cache. 
 *  
 * @param valid if the line is currently in use
 * @param tag identifying tag of the line
 * @param next next line in the linked list implementation of
 * a cache set
 * @param tail previous line in the linked list implementation of
 * a cache set
 */
typedef struct Line {
	unsigned int valid;
	unsigned long tag;
	struct Line *next;
	struct Line *prev;
} Line;

/**
 * Structural representation of a set within a 
 * cache
 * 
 * @param head first line in the linked list implementation of
 * the cache set
 * @param tail last line in hte linked list implementation of 
 * the cache set
 */
typedef struct Set {
	Line *head;
	Line *tail;
} Set;

/**
 * Structure for a single command action derived from the 
 * valgrind trace file.
 * 
 * @param op Memory Operation of the set {M,S,L}
 * @param addr Memory address of the access
 * @param size Size of Mem[addr]
 */
typedef struct Command {
	char op;
	unsigned long addr;
	unsigned int size;
} Command;

//size type for memory addresses
typedef unsigned long int mem_addr;

/**
 * Counter keeping track of the number of different cache
 * metrics.
 * 
 * @param hit_count number of cache hits
 * @param miss_count number of cache misses
 * @param eviction_count number of cache evictions
 */
typedef struct Count{
    int hit_count;
    int miss_count;
    int eviction_count;
}Count;

/**
 * Safely opens, reads, parses, and closes the file
 * trace_file.  
 * 
 * @param c_arr an array of commands to store the parsed
 * file data in
 * @param trace_file name of the trace file to be read
 * @return the size of c_arr
 */
Command *parse_file(char *trace_file, unsigned long *c_size);

/**
 * Takes a string and parses into an address.
 * 
 * @param str String containing valid address
 * @return address in the form of an integer
 */
int get_address(char *str, int *size);

/**
 * Expands the array.  Used to make the array functionally dynamic by resizing
 * and transferring data when called.
 * 
 * @param c_arr current array of struct Command
 * @param c_size current size of c_arr
 * @return A new array containing the content of c_arr and additional
 * space
 */
Command *expand_array(Command *c_arr, unsigned long *c_size);

#endif