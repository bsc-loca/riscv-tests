// See LICENSE for license details.

//**************************************************************************
// Multi-threaded axpy benchmark
//--------------------------------------------------------------------------
// 
//  
//
//
// This benchmark This benchmark runs several AXPY operations in parallle. AXPY is a Level 1 operation in the
// Basic Linear Algebra Subprograms (BLAS) package, and is a common operation in
//computations with vector processors. AXPY is a combination of scalar
//multiplication and vector addition. The input data (and reference data) should be generated
// using the axpy_gendata.pl perl script 

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
#include "double_cmp.h"

   
//--------------------------------------------------------------------------
// axpy function
 
extern void __attribute__((noinline)) histogram(const size_t coreid, const size_t ncores,const size_t lda , data_t A[], unsigned int R[] );

extern int   mt_verify(const size_t coreid, const size_t ncores,const size_t lda , data_t* test,   data_t* verify );

//==================================================

int main(int argc, char** argv) {
   
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];

   if(cid==0) {printf("We are %d cores.\n",nc);}  
   barrier(nc);        
   
   stats(histogram(cid,nc,ARRAY_SIZE,input_data,result_data); barrier(nc),ARRAY_SIZE);
   barrier(nc);        
   
   int res = mt_verify(cid,nc,HISTOGRAM_SIZE , result_data, verify_data);
   if(res){
       printf("Verrification failed!\n");
       exit(res);  
   } 
   barrier(nc);        
   
   exit(0);    
   
}
