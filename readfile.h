#ifndef _READFILE_H_
#define _READFILE_H_
/*
 * This is a library for reading values of different types from a file.
 *
 * To use this library:
 *   (0) #include "readfile.h" at the top of your .c file
 *
 *   (1) call open_file() passing in the file name string to open
 *        open_file("input.txt");
 *     
 *   (2) make calls to read<type> (e.g. read_int) to read values from
 *       the file.  These functions return 0 when the read was successful
 *       and -1 when not (like the file could have nothing left to read)
 *       You need to be careful to call the right function here to
 *       correspond to the next value to be read in the file (if you
 *       want to read in an int, make sure to call read_int and not
 *       read_char, for example)  Examples:
 *
 *       int ret = open_file("input.txt");
 *       if(ret == -1) {
 *          printf("open file failed\n");
 *          exit(1);
 *       }
 *       
 *       int total = 0;
 *       int x = 0;
 *       ret = read_int(&x);
 *       while(ret != -1) {
 *         total += x;
 *         ret = read_int(&x);
 *       }
 *       
 *         
 *
 *   (3) call close_file() when you are all done reading values
 *       from the file
 */


/*
 * Open the file for reading
 *
 * @param filename: a string containing the name of the file to read
 * @return 0 on success, -1 if the file cannot be opened
 *
 */
int open_file(char *filename);

/*
 * Close the file.
 */
void close_file();

/*
 * Reads the next value in the file as a string.
 *
 * @param str a string to fill with the read in value
 * @return 0 on success, -1 if there is nothing left to
 *            read in the file
 */
int read_string(char str[], int size);
/*
 * Reads the next value in the file as an int.
 *
 * @param val the value to "return"
 * @return 0 on success, -1 if there is nothing left to
 *            read in the file
 */
int read_int(int *val);


/*
 * Reads the next value in the file as an unsigned long, unsigned
 * int (new line).
 *
 * @param val the value to "return"
 * @param val2 the second value to "return"
 * @return 0 on success, -1 if there is nothing left to
 *            read in the file
 */
unsigned long read_mem_string(unsigned long *val, unsigned int *val2);


/*
 * Reads the next value in the file as a double.
 *
 * @param val the value to "return"
 * @return 0 on success, -1 if there is nothing left to
 *            read in the file
 */
int read_double(double *val);

#endif
