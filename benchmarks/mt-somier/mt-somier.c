// See LICENSE for license details.

//**************************************************************************
// Multi-threaded somier benchmark
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// Includes 
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "dataset.h"
#include "somier.h"

#include "util.h"
#include "double_cmp.h"

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
/*
 *
 */

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
    
    int res=0; 
	if(cid == 0) res = verify_Double(3,Xcenter,Xcenter_ref);
    
    exit(res);    
}
