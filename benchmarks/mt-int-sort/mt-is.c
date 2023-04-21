//**************************************************************************
// Multi-threaded int sort benchmark
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Includes 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

//--------------------------------------------------------------------------
// Input/Reference Data
#include "dataset.h"

//--------------------------------------------------------------------------
// Basic Utilities and Multi-thread Support
#include "util.h"

extern void __attribute__((noinline)) int_sort (int cid, int nc, int siz, data_t key_array[]);
extern int sort_verify (const size_t coreid, const size_t ncores, const size_t lda, data_t A[], data_t V[]);


//--------------------------------------------------------------------------
// Main
int main(int argc, char** argv) {
   
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];
     
    if(cid==0) printf("\nWe are %d cores.\n",nc);
    barrier(nc);        
   
    stats(int_sort(cid,nc,TOTAL_KEYS,key_array); barrier(nc);,TOTAL_KEYS);
    barrier(nc);        
   
    int res = sort_verify(cid,nc,TOTAL_KEYS,key_verify,key_array);
    barrier(nc);        
    
    if(res){
        printf("Core %d: Verification failed!\n",cid);
        exit(res);  
    }
   
   exit(0);      
}
