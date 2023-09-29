
#include "dataset.h"
#include "util.h"
#include <stddef.h>



/*
void histogram_block(double *x, double *y, long N) {
     for (long i=0; i < N; ++i) {
             y[x[i]]+=1;
     }
}
*/


void histogram(const size_t coreid, const size_t ncores,const size_t lda , data_t A[], unsigned int R[] ){

    size_t i, k, block, start, end;
       
    block = lda / ncores;
    if ((block*ncores) != lda) block++;
    start = block * coreid;
    end   = start + block;
    if (end > lda) end = lda;
      
    for (i = start; i < end; i++) {
      ATOMIC_OP(R[A[i]], 1, add, w);
     // R[A[i]] +=1;
    }
}





