#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "fibonacci.h"

#define N 16

void __attribute__((noinline)) fibonacci (data_t *a);

int main (int argc, char** argv){
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];
    data_t A[N];

    stats(fibonacci(A),N);

    exit (verify_int(N, A, verify_data));
}

static data_t fib(data_t i) {return (i>1) ? fib(i-1) + fib(i-2) : i;}

void fibonacci (data_t *a){
  for(size_t j=0; j<N; j++) a[j] = fib(j);  
}
