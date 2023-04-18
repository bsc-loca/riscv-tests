// See LICENSE for license details.

//**************************************************************************
// Multi-threaded somier benchmark
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
#include "somier.h"

//--------------------------------------------------------------------------
// Basic Utilities and Multi-thread Support
#include "util.h"
#include "double_cmp.h"
 
//--------------------------------------------------------------------------
// Verification function
extern int  __attribute__((noinline)) mt_verify(const size_t coreid, const size_t ncores,const size_t lda , data_t* test,   data_t* verify );

//--------------------------------------------------------------------------
// somier function
void somier_scalar (int cid, int nc) {
    compute_forces(cid, nc, N, X, F);
    barrier(nc);   
    acceleration(cid, nc, N, A, F, M);
    barrier(nc);   
    velocities(cid, nc, N, V, A, dt);
    barrier(nc);   
    positions(cid, nc, N, X, V, dt);
    barrier(nc);   
    compute_stats_pre(cid, nc, N, X);
    barrier(nc);   
    compute_stats(cid, nc, N, X, Xcenter);
    barrier(nc);   
}

//--------------------------------------------------------------------------
// main function
  
int main(int argc, char** argv) {
   
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];
   
    if(cid<nc) init_forloop_boundries (cid,nc, N);   
    barrier(nc);   
   
    if(cid==0) {
       printf("\nWe are %d cores.\n",nc);
       Xcenter[0]=0, Xcenter[1]=0; Xcenter[2]=0;      
    }
    barrier(nc);   
     
    stats(somier_scalar(cid,nc); barrier(nc), N); // ROI
    barrier(nc); // ROI sync   
 
	if(cid==0) { 
		int res = verify_Double(3,Xcenter,Xcenter_ref);
		if(res){
		    printf("Verification failed!\n");
    		exit(res);  
    	}	
	}
    barrier(nc);   
    
   exit(0);    
}
