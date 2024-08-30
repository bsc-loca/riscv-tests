// See LICENSE for license details.

//**************************************************************************
// Multi-threaded axpy benchmark
//--------------------------------------------------------------------------
// This benchmark This benchmark runs several AXPY operations in parallle. AXPY is a Level 1 operation in the
// Basic Linear Algebra Subprograms (BLAS) package, and is a common operation in
// computations with vector processors. AXPY is a combination of scalar
// multiplication and vector addition. The input data (and reference data) should be generated
// using the axpy_gendata.pl perl script 

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "util.h"
#include "double_cmp.h"

#include "dataset.h"
   
extern void __attribute__((noinline)) axpy(const size_t coreid, const size_t ncores, const size_t lda, data_t *A, data_t *B, data_t alpha);
extern int mt_verify(const size_t coreid, const size_t ncores, const size_t lda, data_t* test, data_t* verify);

/*
 *
 */

int main(int argc, char** argv) {
   
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];
     
    if(cid==0) printf("\nWe are %d cores.\n",nc);
    barrier(nc);

#if PREALLOCATE
    mt_verify(cid,nc,ARRAY_SIZE,input1_data,input1_data);
    barrier(nc);
#endif
    stats(axpy(cid,nc,ARRAY_SIZE,input1_data,input2_data,Alfa); barrier(nc), ARRAY_SIZE); // ROI
  
    int res = mt_verify(cid,nc,ARRAY_SIZE,input1_data,verify_data);
   
    exit(res);  
}
