#include <stdint.h>
#include <stddef.h>
#include "util.h"
#include "dataset.h"

static unsigned int offset [1024] ={0};

void histogram (const size_t coreid, const size_t ncores,const size_t lda , data_t A[], data_t B[], unsigned int R[] ){

    size_t i, k, block, start, end;
    block = lda / ncores;
    if ((block*ncores) != lda) block++;
    start = block * coreid;
    end   = start + block;
    if (end > lda) end = lda;
      
    for (i = start; i < end; i++) {
      ATOMIC_OP(R[A[i]], 1, add, w);      // R[A[i]] +=1;
      B[i] = A[i];                       //duplicate A: B = A
    }
}

void cumulative_sum_1  (const size_t coreid, const size_t ncores,const size_t ldr ,  int R[] , int offset [] ){
    
    size_t i, k, block, start, end;
          
    block = ldr / ncores;
    if ((block*ncores) != ldr) block++;
    start = block * coreid;
    end   = start + block;
    if (end > ldr) end = ldr;
      
    for (i = start; i < end-1; i++) {
		  R[i+1] += R[i];  
    }
   
    offset [coreid] = R[end-1]; // save the last sum
}

void cumulative_sum_2  (const size_t coreid, const size_t ncores,const size_t ldr ,  int R[] , int offset [] ){
    
    size_t i, k, block, start, end;
    int d=0;
    if(coreid == 0) return;

    for (i = 0; i < coreid; i++) {
		  d += offset[i];  
    }
    //printf ("i=%ld, o= %d\n",  coreid   ,d); 
    
    block = ldr / ncores;
    if ((block*ncores) != ldr) block++;
    start = block * coreid;
    end   = start + block;
    if (end > ldr) end = ldr;
      
    for (i = start; i < end; i++) {
		  R[i] += d;  
    }   
}



void sort_keys (const size_t coreid, const size_t ncores,const size_t lda , data_t A[], data_t B[],  int R[], int offset [] ){

    size_t i, k, block, start, end;
    block = lda / ncores;
    if ((block*ncores) != lda) block++;
    start = block * coreid;
    end   = start + block;
    if (end > lda) end = lda;

    int d;  
    for (i = start; i < end; i++) {
       //printf ("\tR[B[i]]=%d\n",R[B[i]]);
       ATOMIC_FETCH_OP(d,R[B[i]], -1, add, w);   //d=--R[B[i]];
       // printf ("\td=%d\n",d);
       A[d-1] = B[i];  // d is the old value in AMO operand. Its needed to be -1
    }
}


int sort_verify (const size_t coreid, const size_t ncores,const size_t lda , data_t A[] , data_t V[] ){

    size_t i, k, block, start, end;   
    block = lda / ncores;
    if ((block*ncores) != lda) block++;
    start = block * coreid;
    end   = start + block;
    if (end > lda) end = lda;
      
    for (i = start; i < end; i++) {
        if( A[i] != V[i] ) return i+1;
    }
    return 0;
}



void int_sort (int cid, int nc, int siz, data_t *key_array) {
	histogram ( cid, nc, siz, key_array, key_buff, key_histogram );	
    barrier(nc);        
	cumulative_sum_1( cid, nc, MAX_KEY, key_histogram ,offset);
    barrier(nc);        
	cumulative_sum_2( cid, nc, MAX_KEY, key_histogram ,offset);	
    barrier(nc);        
	sort_keys (cid, nc, siz, key_array, key_buff, key_histogram,offset );
}
