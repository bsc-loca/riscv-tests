#include "util.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

#include "dataset.h"

void tuned_STREAM_Copy(const size_t coreid, const size_t ncores,const size_t lda , data_t A[], data_t C[]){

    size_t i, k, block, start, end;
       
    block = lda / ncores;
    if ((block*ncores) != lda) block++;
    start = block * coreid;
    end   = start + block;
    if (end > lda) return; //should assert error instead
       
    size_t j;
    for (j=start; j<end; j++)
        C[j] = A[j];  
}


void tuned_STREAM_Scale(const size_t coreid, const size_t ncores,const size_t lda , data_t B[], data_t C[], data_t alpha)
{
    size_t i, k, block, start, end;
       
    block = lda / ncores;
    if ((block*ncores) != lda) block++;
    start = block * coreid;
    end   = start + block;
    if (end > lda) return; //should assert error instead
       
    size_t j;
	for (j=start; j<end; j++)
	    B[j] = alpha*C[j];
}

void tuned_STREAM_Add(const size_t coreid, const size_t ncores,const size_t lda , data_t A[], data_t C[], data_t B[])
{
    size_t i, k, block, start, end;
       
    block = lda / ncores;
    if ((block*ncores) != lda) block++;
    start = block * coreid;
    end   = start + block;
    if (end > lda) return; //should assert error instead
       
    size_t j;
	for (j=start; j<end; j++)
	    C[j] = A[j]+B[j];
}

void tuned_STREAM_Triad(const size_t coreid, const size_t ncores,const size_t lda ,data_t *A, data_t *C, data_t *B, data_t alpha)
{
    size_t i, k, block, start, end;
       
    block = lda / ncores;
    if ((block*ncores) != lda) block++;
    start = block * coreid;
    end   = start + block;
    if (end > lda) return; //should assert error instead
       
    size_t j;
	for (j=start; j<end; j++)
	    A[j] = B[j]+alpha*C[j];
}


