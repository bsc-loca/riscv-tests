/*
 * ---------------------------------------
 *        Bubblesort Benchmark 
 *---------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "dataset.h"

void __attribute__((noinline)) bsort (const size_t n, data_t *data);

/*
 *
 */

int main (int argc, char** argv){
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];
 
    printf("\nWe are %d cores.\n",nc);
    
#if PREALLOCATE 
    // Cache Warm up
    verify(DATA_SIZE,input_data,input_data);
#endif

    stats(bsort(DATA_SIZE,input_data), DATA_SIZE);
                    
    exit(verify(DATA_SIZE,input_data,verify_data));
}

void bsort (const size_t n, data_t *data){
    data_t aux;
    for (size_t i=0; i<n; i++){ 
        for (size_t j=0; j<n-1; j++){ 
            if (data[j] >= data[j+1]){ 
                aux = data[j]; 
			    data[j] = data[j+1]; 
			    data[j+1] = aux; 
            } 
        } 
    } 
}


