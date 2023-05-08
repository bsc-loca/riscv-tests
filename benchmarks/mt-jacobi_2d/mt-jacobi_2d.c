/**
 * This version is stamped on May 10, 2016
 *
 * Contact:
 *   Louis-Noel Pouchet <pouchet.ohio-state.edu>
 *   Tomofumi Yuki <tomofumi.yuki.fr>
 *
 * Web address: http://polybench.sourceforge.net
 */
/* jacobi-2d.c: this file is part of PolyBench/C */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "double_cmp.h"

#include "dataset.h"

extern void __attribute__((noinline)) kernel_jacobi_2d(int ncores, int coreid, int lda, data_t A[], data_t B[]);
extern int mt_verify(const size_t coreid, const size_t ncores, const size_t lda, data_t* test, data_t* verify);

//------------------------------------------------
// Main Function

int main(int argc, char** argv) {
   
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];
     
    if(cid==0) printf("\nWe are %d cores.\n",nc); 
    barrier(nc);        

    stats(kernel_jacobi_2d(nc,cid, DIM_SIZE, input1_data, input2_data); barrier(nc), ARRAY_SIZE);
    barrier(nc);

    int res = mt_verify(cid,nc,ARRAY_SIZE,input1_data,verify_data1);
    if(res){
        printf("Core %d: Verification failed!\n",cid);
        exit(res);  
    }       
    
    res = mt_verify(cid,nc,ARRAY_SIZE,input2_data,verify_data2);
    if(res){
        printf("Core %d: Verification failed!\n",cid);
        exit(res);  
    } 
    barrier(nc);        
        
    exit(0);  
}
