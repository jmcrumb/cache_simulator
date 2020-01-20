
#include "save.h"
#include "init_cache.h"
#include "load.h"

void save(Set *cache, Count *counter ,unsigned long addr, unsigned int size, int num_sets, int block_offset, char *printout) {
    unsigned long set_mask, block_mask, tag_mask;
    //constructs masks for extracting set, block, and tag
    get_masks(addr, num_sets, block_offset,&set_mask, &block_mask, &tag_mask);
    if(SET < (1 << num_sets)){
        Line *line = cache[SET].head;
        int is_done = FALSE;
        //iterate through each line of the relevant set
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
