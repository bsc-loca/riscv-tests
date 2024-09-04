// See LICENSE for license details.

//**************************************************************************
// Multi-threaded my-stram-copy benchmark
//--------------------------------------------------------------------------
// This benchmark This benchmark runs several stream operations in parallle. 
// stream is a combination of scalar
// multiplication and vector addition. The input data (and reference data) should be generated
// using the gendata.pl perl script 

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "dataset.h"

#include "util.h"
#include "double_cmp.h"
   
extern void __attribute__((noinline)) tuned_STREAM_Triad(const size_t coreid, const size_t ncores,const size_t lda, data_t *A, data_t *C, data_t *B, data_t alpha);
extern int mt_verify(const size_t coreid, const size_t ncores,const size_t lda , data_t* test, data_t* verify);
 
/*
 *
 */

int main(int argc, char** argv) {
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];
     
    if(cid==0) printf("\nWe are %d cores.\n",nc);
    barrier(nc);        
  
    stats(tuned_STREAM_Triad(cid,nc,ARRAY_SIZE,input3_data,input2_data,input1_data,Alfa);barrier(nc),ARRAY_SIZE);
   
    int res = mt_verify(cid,nc,ARRAY_SIZE,input3_data,verify_data);
      
    exit(res);     
}
