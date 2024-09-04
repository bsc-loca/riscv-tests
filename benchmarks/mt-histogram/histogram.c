#include <stddef.h>
#include "util.h"
#include "dataset.h"

void histogram(const size_t coreid, const size_t ncores, const size_t lda , data_t *A, data_t *R){

    size_t i, k, block, start, end;
       
    block = lda / ncores;
    if ((block*ncores) != lda) block++;
    start = block * coreid;
    end   = start + block;
    if (end > lda) end = lda;
      
    for (i = start; i < end; i++) {
      ATOMIC_OP(R[A[i]], 1, add, w);
    }
}

void clear (const size_t coreid, const size_t ncores, size_t lda, data_t *data){
    size_t i, k, block, start, end;
       
    block = lda / ncores;
    if ((block*ncores) != lda) block++;
    start = block * coreid;
    end   = start + block;
    if (end > lda) end = lda;
    
    for (i= start; i<end; i++) data[i] = 0;
}




