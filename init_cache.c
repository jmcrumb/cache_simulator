#include "init_cache.h"

Set *init_cache(int num_sets, int blocks_size, int lines_per_set) {
	Set *cache = calloc(num_sets, sizeof(Set));
	for(int i = 0; i < num_sets; ++i) {
		Set s;
		s.head = NULL;
		s.tail = NULL;
		for(int j = 0; j < lines_per_set; ++j) {
			line_insert(&s, 0, 0);
		}
		cache[i] = s;
	}


	return cache;
}

void cache_state(const Set *cache, int num_sets, int lines_per_set) {
	for(int i = 0; i < num_sets; ++i) {
		printf("\t\tSet %d:\n", i);
		Line *l = cache[i].head;
		while(l != NULL) {
			printf("\t\t\tValid: %u\t Tag: %lx\t\n", l->valid, l->tag);
			l = l->next;
		}
	}
}

void cache_deconstruct(Set *cache, int num_sets) {
	for(int i = 0; i < num_sets; ++i) {
		Line *l = cache[i].head;
		while(l != NULL) {
			Line *temp = l;
			l = l->next;
			free(temp);
		}
	}
	free(cache);
}
