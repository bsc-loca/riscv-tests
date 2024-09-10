#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "inputs/spm0.h"

#include "util.h"
#include "double_cmp.h"

void __attribute__((noinline)) spmv(const size_t coreid, const size_t ncores, const size_t lda, uint64_t *ptr, uint64_t *col, data_t *val, data_t *x, data_t *y);
extern int mt_verify(const size_t coreid, const size_t ncores, const size_t lda, data_t* test, data_t* verify);

/* 
 * 
 */

int main(int argc, char** argv) 
{
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];

    if(cid==0) printf("\nWe are %d cores.\n",nc);
    barrier(nc);        

    stats(spmv(cid,nc,NROW,ptr,col,val,x,y);barrier(nc),NNZ); // ROI
  
    int res = mt_verify(cid,nc,NROW,y,ref);
       
    exit(res);
}

/*   
 *
 */

void spmv(const size_t coreid, const size_t ncores, const size_t lda, uint64_t *ptr, uint64_t *col, data_t *val, data_t *x, data_t *y){
    
    size_t i, k, block, start, end;
    
    block = lda / ncores; 
    
    if ((block*ncores) != lda) block++;
    
    start = block * coreid;
    end   = start + block;
    
    if (end > lda) end = lda;
    
    //for (int row=0; row<NROW; row++) {
    for (int row = start; row < end; row++) {
        double sum = 0;
        for (int idx=ptr[row]; idx<ptr[row+1]; idx++) 
            sum += val[idx] * x[col[idx]] ;
        y[row] = sum;
    }

}
