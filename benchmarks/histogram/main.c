#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "dataset.h"

void __attribute__((noinline)) histogram (size_t n, data_t *data, uint32_t *r);
void clear (size_t n, uint32_t *data);

/*
 *
 */

int main (int argc, char** argv){
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];

#if PREALLOCATE
    stats(histogram(ARRAY_SIZE,input_data,results_data),ARRAY_SIZE);
    clear(HISTOGRAM_SIZE,results_data);
#endif
    stats(histogram(ARRAY_SIZE,input_data,results_data),ARRAY_SIZE);
    
    exit(verify_int(HISTOGRAM_SIZE, results_data, verify_data)) ;
}

void histogram (size_t n, data_t *data, uint32_t *r){
	for(size_t i=0; i<n; i++)
        r[data[i]] += 1;
}

void clear (size_t n, uint32_t *data){
    for (size_t i=0; i<n; i++) data[i] = 0;
}
