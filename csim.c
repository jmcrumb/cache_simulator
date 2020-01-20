/*
 * csim.c
 * 
 * This program contains a simulation for the state of a cache.
 * It takes traces files from valgrind, processes each memory 
 * access, and records the number of hits, misses, and 
 * evictions in the trace file.
 * 
 * Authors: Jarvis Lu and Maxon Crumbs
 * All cache simulator files last modified: 11/08/2019
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cachelab.h"
#include "fileio.h"
#include "init_cache.h"
#include "load.h"
#include "save.h"

// forward declaration
void simulateCache(char *trace_file, int num_sets, int block_size, int lines_per_set, int verbose);

/**
 * Prints out a reminder of how to run the program.
 *
 * @param executable_name Strign containing the name of the executable.
 */
void usage(char *executable_name)
{
	printf("Usage: %s [-hv] -s <s> -E <E> -b <b> -t <tracefile>", executable_name);
}

int main(int argc, char *argv[])
{
	//initialize variables 
	int verbose_mode = FALSE;
	int num_sets = -1;
	char *trace_filename = argv[1];
	opterr = 0;
	int c = -1;
	int block_offset = -1;
	int lines_per_set = -1;

	//read in command line arguments and assign to relevant variables
	//valid commands:
	//	-h: Optional help flag that prints usage info
	//	-v: Optional verbose flag that displays trace info
	//	-s <s>: Number of set index bits (S = 2^s is the number of sets)
	//	-E <E>: Associativity (number of lines per set)
	//	-b <b>: Number of block bits (B = 2^b is the block size)
	//	-t <tracefile>: Name of the Valgrind trace to replay
	while ((c = getopt(argc, argv, "vs:b:E:t:")) != -1)
	{
		switch (c)
		{
		case 'v':
			// enable verbose mode
			verbose_mode = TRUE;
			break;
		case 's':
			// specify the number of sets
			// Note: optarg is set by getopt to the string that follows
			// this option (e.g. "-s 2" would assign optarg to the string "2")
			num_sets = strtol(optarg, NULL, 10);
			break;
		case 'b':
			// establish block offset
			block_offset = strtol(optarg, NULL, 10);
			break;
		case 'E':
			// establish lines in each cache set
			lines_per_set = strtol(optarg, NULL, 10);
			break;
		case 't':
			// specify the trace filename
			trace_filename = optarg;
			break;
		case '?':
			break;
		default:
			usage(argv[0]);
			exit(1);
		}
	}

	if (verbose_mode)
	{
		//Shows user relevant cache parameters
		printf("Verbose mode enabled.\n");
		printf("Trace filename: %s\n", trace_filename);
		printf("Number of sets: %d\n", 1 << num_sets);
		printf("Lines per set: %d\n", lines_per_set);
		printf("Block size: %d\n", 1 << block_offset);
	}

	simulateCache(trace_filename, num_sets, block_offset, lines_per_set, verbose_mode);

	return 0;
}

/**
 * Simulates cache with the specified organization (S, E, B) on the given
 * trace file.
 *
 * @param trace_file Name of the file with the memory addresses.
 * @param num_sets Number of sets in the simulator.
 * @param block_size Number of bytes in each cache block.
 * @param lines_per_set Number of lines in each cache set.
 * @param verbose Whether to print out extra information about what the
 *   simulator is doing (1 = yes, 0 = no).
 */
void simulateCache(char *trace_file, int num_sets, int block_size,
				   int lines_per_set, int verbose)
{
	// Variables to track how many hits, misses, and evictions we've had so
	// far during simulation.
	unsigned long c_size = 0;
	Command *c_arr = parse_file(trace_file, &c_size);
	//constructing a cache based on user settings
	Set *cache = init_cache(1 << num_sets, block_size, lines_per_set);
	Count *counter = calloc(1, sizeof(Command));
	char *printout = calloc(100 * MAXSIZE, sizeof(char));

	//iterate through the series of commands in the tracefile, excluding the instruction access
	for (int i = 0; i < c_size - 1; ++i){			
		switch (c_arr[i].op)
		{
		//Modify memory access
		case 'M':
			sprintf(printout, "%4c %lx,%d ", c_arr[i].op, c_arr[i].addr, c_arr[i].size);
			load(cache, counter, c_arr[i].addr, c_arr[i].size, num_sets, block_size, printout);
			save(cache, counter, c_arr[i].addr, c_arr[i].size, num_sets, block_size, printout);
			break;
		//Safe memory access
		case 'S':
			sprintf(printout, "%4c %lx,%d ", c_arr[i].op, c_arr[i].addr, c_arr[i].size);
			save(cache, counter, c_arr[i].addr, c_arr[i].size, num_sets, block_size, printout);
			break;
		//Load memory access
		case 'L':
			sprintf(printout, "%4c %lx,%d ", c_arr[i].op, c_arr[i].addr, c_arr[i].size);
			load(cache, counter, c_arr[i].addr, c_arr[i].size, num_sets, block_size, printout);
			break;
		//Instruction memory access (ie. do nothing)
		case ' ':
			break;
		}
		//Current cache action
		if (verbose)
			printf("%s\n", printout);
	}
	//print a final summary of the cache behavior
	printSummary(counter->hit_count, counter->miss_count, counter->eviction_count);
	//free memory allocated to the heap
	free(printout);
	free(counter);
	free(c_arr);
	cache_deconstruct(cache, 1 << num_sets);
}
