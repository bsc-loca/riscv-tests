#include <sys/types.h>
#include <sys/times.h>
#include "util.h"


#define N 25

static int fib(int i) {return (i>1) ? fib(i-1) + fib(i-2) : i;}

int main() {
  int A[N];

  unsigned long cycle = read_csr(mcycle);
  unsigned long instr = read_csr(minstret); 
  
  //--------------------------------------------------
  // ROI
  for(int j=0; j<N; j++) {
      A[j] = fib(j);  
  }  
  //--------------------------------------------------
    
  printf("Cycles:  %d \n",read_csr(mcycle) - cycle);
  printf("Instructions:  %d \n\n",read_csr(minstret) - instr);
    
  printf("   Fibonacci sequence: \n   "); 
  for (int i=0;i<N;i++) { printf("%d ",A[i]);}
  printf("\n");

  return 0;
} 
