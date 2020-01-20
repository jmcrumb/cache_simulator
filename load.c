
#include "load.h"

void load(Set *cache, Count *counter ,unsigned long addr, unsigned int size, int num_sets, int block_offset, char *printout){
    unsigned long set_mask, block_mask, tag_mask;
    get_masks(addr, num_sets, block_offset,&set_mask, &block_mask, &tag_mask);
    if(SET < (1 << num_sets)){
        Line *line = cache[SET].head;
        //iterate through each line of the relevant set
        int is_done = FALSE;
        while(line != NULL && !is_done){
            if(line->valid){
                //compare tags of addr with current set line's
                is_done = tag_check(cache, SET, counter, TAG, printout, line);
            }
            else{
                //if valid = 0, compulsory miss
                counter->miss_count++;
                strncat(printout,"miss ", MAXSIZE);
                //add addr's line values to the set                
                line_insert(&cache[SET], 1, TAG);
                line_remove(&cache[SET]);
                is_done = TRUE;
            }
            if(!is_done)
                line = line->next;
        }
        return;
    }
    else {
        counter->miss_count++;
        strncat(printout,"miss ", MAXSIZE);
    }
}


void get_masks(unsigned long addr, int num_sets, int block_offset, unsigned long *set_mask, unsigned long *block_mask, unsigned long *tag_mask){
    ////generate bitmasks
    *set_mask = ~1;
    *block_mask = ~1;
    *block_mask = ~(*block_mask << (block_offset - 1));
    *set_mask = ~((*set_mask << ((num_sets - 1) + block_offset))  ^ *block_mask);
    *tag_mask = (~0 << (num_sets + block_offset - 1));
}

int tag_check(Set *cache, unsigned long set_num, Count *counter, unsigned long tag, char *printout, Line *line){
    //if tag is in line: hit
    if(line->tag == tag) {
        counter->hit_count++;
        strncat(printout,"hit ", MAXSIZE);
        if(line == cache[set_num].tail){
            line_insert(&cache[set_num], 1, tag);
            line_remove(&cache[set_num]);
        }
        return TRUE;
    } 
    else if(line == cache[set_num].tail) {
        //if set is full and tag DNE: capacity miss
        counter->miss_count++;
        counter->eviction_count++;
        strncat(printout,"miss eviction ", MAXSIZE);
        //add the new line to the set
        line_insert(&cache[set_num], 1, tag);
        line_remove(&cache[set_num]);
        return TRUE;
    }
    else    
        return FALSE;
}
