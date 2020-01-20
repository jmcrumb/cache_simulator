#include "fileio.h"


Command *parse_file(char *trace_file, unsigned long *c_size) {
	//Open file
	FILE *file = NULL;
	Command *c_arr = calloc(MAXSIZE, sizeof(Command));
	file = fopen(trace_file, "r");
	if(file == NULL) {
		printf("%s failed to open\n", trace_file);
		exit(1);
	}
	int cont = 0, itr = 0;
	*c_size = MAXSIZE;
	//Parse each line of the file
	while(cont != -1){
		char* raw_op = malloc(MAXSIZE *sizeof(char));
		if(fgets(raw_op, MAXSIZE, file) == NULL){
			cont = -1;
		}
		else{
			if(itr == *c_size -1)
				c_arr = expand_array(c_arr, c_size);
			if(strcmp(&raw_op[0], "I") < 0) {
				c_arr[itr].op = raw_op[1];
				int size = 0;
				c_arr[itr].addr = get_address(raw_op, &size);
				c_arr[itr].size = size;
				++itr;
			}

		}
		free(raw_op);
	}
	fclose(file);
	*c_size = itr + 1;
	return c_arr;	
}

int get_address(char *str, int *size){
	char* address = calloc(MAXSIZE ,sizeof(char));
	int i = 3;
	while(str[i] - 44 != 0){
		address[i - 3] = str[i];
		i++;
	}
	*size = str[i + 1] - '0';
	long int ret = strtol(address, NULL, 16);
	free(address);
	return ret;
}


Command *expand_array(Command *c_arr, unsigned long *c_size){
	*c_size = *c_size * 2;
	return realloc(c_arr, *c_size * sizeof(Command));

}
