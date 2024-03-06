#include <stdlib.h>
#include <stdio.h>
#include "dataset.h"
#include "util.h"

extern void __attribute__((noinline)) test_xyz(int a[], long *accum) 
{
    for (int i=0; i<N; i++)
        *accum += a[i] ;
}

int main( int argc, char* argv[] )
{
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];
    long result = 0;
    long tmp = 0;

    // warmup
    for (int i=0; i<N; i++) tmp += A[i] ;
    printf("Tmp:  %ld \n",tmp);
    
    // ROI
    stats(test_xyz( A, &result );barrier(nc), N);
    printf("Result:  %ld \n",result);

    exit(0);
}
