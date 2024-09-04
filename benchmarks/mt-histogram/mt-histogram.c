// See LICENSE for license details.

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "dataset.h"
#include "util.h"
#include "double_cmp.h"
 
extern void __attribute__((noinline)) histogram(const size_t coreid, const size_t ncores, const size_t lda , data_t *A, data_t *R);
extern void clear (const size_t coreid, const size_t ncores, size_t lda, data_t *data);
extern int mt_verify(const size_t coreid, const size_t ncores,const size_t lda , data_t* test, data_t* verify );

/*
 *
 */

int main(int argc, char** argv) {
   
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];

    if(cid==0) {printf("We are %d cores.\n",nc);}  
    barrier(nc);        
   
#if PREALLOCATE
   stats(histogram(cid,nc,ARRAY_SIZE,input_data,result_data); barrier(nc),ARRAY_SIZE);
   clear(cid,nc,HISTOGRAM_SIZE,result_data);
   barrier(nc);        
#endif
   stats(histogram(cid,nc,ARRAY_SIZE,input_data,result_data); barrier(nc),ARRAY_SIZE);
   
   int res = mt_verify(cid,nc,HISTOGRAM_SIZE , result_data, verify_data);
   
   exit(res);    
}
