#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "dataset.h"
#include "util.h"
#include "double_cmp.h"
   
 
extern void __attribute__((noinline)) matmul(const size_t coreid, const size_t ncores, const size_t lda,  const data_t *A, const data_t *B, data_t *C);

int main(int argc, char** argv) {
    int cid = argv[0][0];
    int nc = argv[0][1];
  
    if(cid==0) printf("\nWe are %d cores.\n",nc);
    barrier(nc);
    
    stats(matmul(cid, nc, DIM_SIZE, input1_data, input2_data, results_data); barrier(nc), DIM_SIZE/DIM_SIZE/DIM_SIZE);  
 
    int res = mt_verify(cid, nc, ARRAY_SIZE, results_data, verify_data);

    exit(res);
}

