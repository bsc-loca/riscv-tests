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

#include "dataset.h"

static void jacobi_2d(int ncores, int coreid, int lda, data_t A[], data_t B[])
{
    int t, i, j, k;
    size_t  block, start, end;

    block = lda / ncores;
    if ((block*ncores) != lda) block++;
    start = block * coreid;
    end   = start + block;
    if (end > lda) end = lda;
    
    // We avoid the first and last lines.
    if (start == 0) start++;
    if (end == lda) end--; 

    for ( k = start; k < end ; k++ ) 
            for ( i = 1; i < lda - 1 ; i++ ) 
                A[i+k*lda] = (0.2) * (B[i+k*lda] + B[(i+k*lda)-1] + B[(i+k*lda)+1] + B[(i+k*lda)-lda] + B[(i+k*lda)+lda]);

}

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
void kernel_jacobi_2d(int ncores, int coreid, int lda, data_t A[], data_t B[])
{
    jacobi_2d(ncores, coreid, lda, B, A);
    barrier(ncores);
    jacobi_2d(ncores, coreid, lda, A, B);
}

