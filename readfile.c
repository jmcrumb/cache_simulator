/*
 * This is a library for reading values of different types from a file.

 * See the associated header (readfile.h) for instructions on how to use this
 * library.

 * WARNING: It is not a particularly safe version of reading functions...
 * but neither is fscanf...
 *
 */
#include <stdio.h>      // the C standard I/O library
#include <stdlib.h>     // the C standard library
#include <string.h>     // the C string library
#include "readfile.h"   

// These are global variables. You are not allowed to use
// global variables in your program, so do not mimick this style.
static FILE *infile = 0;
static int  is_inited = 0; 

// Note: header comments are given with the prototypes in the .h file
int read_string(char str[], int size) {
	if (!is_inited) {
		return -1;
	}
	if(fgets(str, size, infile) == NULL){
		return -1;
	}
	return 0;
}

int read_int(int *val) {
	if (!is_inited) {
		return -1;
	}
	int ret = fscanf(infile, "%d", val);
	if (ret != 1) { 
		return -1;
	}
	return 0;
}

unsigned long read_mem_string(unsigned long *val, unsigned int *val2) {
	if (!is_inited) {
		return -1;
	}
	int ret = fscanf(infile, "%lu,%u", val, val2);
	if (ret != 1) { 
		return -1;
	}
	return 0;
}

int read_double(double *val) {
	if (!is_inited) {
		return -1;
	}
	int ret = fscanf(infile, "%lf", val);
	if (ret != 1) { 
		return -1;
	}
	return 0;
}

int open_file(char *filename) {
	
	if (!infile) {
		return -1;
	}
	is_inited = 1;
	return 0;
}

void close_file() {
	if (infile) {
		fclose(infile);
	}
	is_inited = 0;
}
