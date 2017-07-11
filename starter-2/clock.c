#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

/* Page to evict is chosen using the clock algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int clock_pointer;

int clock_evict() {
	while(coremap[clock_pointer].frame&PG_REF_CLOCK)
    {
        coremap[clock_pointer].frame&=~PG_REF_CLOCK;
        clock_pointer=(clock_pointer+1)%memsize;
    }
    int rn= clock_pointer;
    clock_pointer=(clock_pointer+1)%memsize;
    return rn;
}

/* This function is called on each access to a page to update any information
 * needed by the clock algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pgtbl_entry_t *p) {

    p.frame|=PG_REF_CLOCK;
	return;
}

/* Initialize any data structures needed for this replacement
 * algorithm. 
 */
void clock_init() {
    clock_pointer=0;
}
