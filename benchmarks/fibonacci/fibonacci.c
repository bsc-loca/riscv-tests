#include <sys/types.h>
#include <sys/times.h>
#include "util.h"

static int fib(int i) {return (i>1) ? fib(i-1) + fib(i-2) : i;}

int main() {
    unsigned long cycles1, cycles2, instr2, instr1;
    int aux,i,j;
    int result; 
    
    int n=25;
    int A[25];

    printf("\n   *** FIBONACCI BENCHMARK TEST ***\n\n");
    printf("RESULTS OF THE TEST:\n");
    printf("N = %d \n", n);

    setStats(1);

    //--------------------------------------------------
    for(j=0; j<n; j++) {
        result=fib(j);
        A[j] = result;
    }
    //--------------------------------------------------
    
    setStats(0);

    printf("\nFibonacci sequence: \n");
	
    for (i=0;i<n;i++) { 
	    printf("%d ",A[i]);
	}
	printf("\n");

} 
