// See LICENSE for license details.

//**************************************************************************
// Vector-vector add benchmark
//--------------------------------------------------------------------------
// Author  : Andrew Waterman
// TA      : Christopher Celio
// Student : 
//
// This benchmark adds two vectors and writes the results to a
// third vector. The input data (and reference data) should be
// generated using the vvadd_gendata.pl perl script and dumped
// to a file named dataset.h 

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "double_cmp.h"
   
#include "dataset.h"

extern void __attribute__((noinline)) vvadd(int coreid, int ncores, size_t lda, const data_t* x, const data_t* y, data_t* z);

/*
 *
 */

int main (int argc, char** argv){
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];
   
    if(cid==0) printf("\nWe are %d cores.\n",nc);
    barrier(nc);

#if PREALLOCATE
   stats(vvadd(cid, nc, DATA_SIZE, input1_data, input2_data, results_data); barrier(nc), DATA_SIZE);
#endif
   stats(vvadd(cid, nc, DATA_SIZE, input1_data, input2_data, results_data); barrier(nc), DATA_SIZE);
 
   int res = mt_verify(cid, nc, DATA_SIZE, results_data, verify_data);

   exit(res);
}
