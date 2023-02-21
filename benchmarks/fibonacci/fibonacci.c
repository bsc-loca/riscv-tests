#include <sys/types.h>
#include <sys/times.h>
#include "util.h"
#include "metrics.h"


#define N 25

int fib_check[N] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368};

static int fib(int i) {return (i>1) ? fib(i-1) + fib(i-2) : i;}

int main() {
  int A[N];
    
  roi_start(); 
  //--------------------------------------------------
  // ROI
  for(int j=0; j<N; j++) {
      A[j] = fib(j);  
  }  
  //--------------------------------------------------
  roi_end(); 
  print_metrics("fibonacci");
    
  int errors = 0;
  for (int i=0;i<N;i++) {
      if (A[i] != fib_check[i]) ++errors;
  }

  return errors;
} 
