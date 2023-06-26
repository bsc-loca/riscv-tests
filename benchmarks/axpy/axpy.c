// See LICENSE for license details.

//**************************************************************************
// Quicksort benchmark
//--------------------------------------------------------------------------
//
// This benchmark uses quicksort to sort an array of integers. The
// implementation is largely adapted from Numerical Recipes for C. The
// input data (and reference data) should be generated using the
// qsort_gendata.pl perl script and dumped to a file named
// dataset1.h The smips-gcc toolchain does not support system calls
// so printf's can only be used on a host system, not on the smips
// processor simulator itself. You should not change anything except
// the HOST_DEBUG and PREALLOCATE macros for your timing run.

#include "util.h"
#include <string.h>
#include <limits.h>

#define N_TIMES		10 /* Default number of runs */
#define DATA_SIZE 512

double dx[DATA_SIZE];
double dy_opt[DATA_SIZE];


void axpy(double a, double *dx, double *dy, int n) {
   int i;
   for (i=0; i<n; i++) {
      dy[i] += a*dx[i];
   }
}

void axpy_unroll(double a, double *dx, double *dy, int n) {
   int i;
   for (i=0; i<n-6; i+=6) {
      double a0 = dx[i];
      double b0 = dy[i];
      double a1 = dx[i+1];
      double b1 = dy[i+1];
      double a2 = dx[i+2];
      double b2 = dy[i+2];
      double a3 = dx[i+3];
      double b3 = dy[i+3];
      double a4 = dx[i+4];
      double b4 = dy[i+4];
      double a5 = dx[i+5];
      double b5 = dy[i+5];
      double r0 = a*a0 + b0;
      double r1 = a*a1 + b1;
      double r2 = a*a2 + b2;
      double r3 = a*a3 + b3;
      double r4 = a*a4 + b4;
      double r5 = a*a5 + b5;
      dy[i] = r0;
      dy[i+1] = r1;
      dy[i+2] = r2;
      dy[i+3] = r3;
      dy[i+4] = r4;
      dy[i+5] = r5;
   }
   for (i; i<n; i++) {
      dy[i] += a*dx[i];
   }
}

void init_vector(double *pv, long n, double value)
{
   for (int i=0; i<n; i++){ 
     pv[i]= value;
   }
}


//--------------------------------------------------------------------------
// Main
//--------------------------------------------------------------------------

int main( int argc, char* argv[] ){

   printf("\n   *** AXPY BENCHMARK TEST ***\n\n");
   printf("Size of the vector:%d\n",DATA_SIZE);
   printf("Number of iterations:%d\n",N_TIMES);

   double a=1.0;

   /* Allocate the source and result vectors */

   init_vector(dx, DATA_SIZE, 1.0);
   init_vector(dy_opt, DATA_SIZE, 2.0);
   
   setStats(1);
   for(int i = 0; i < N_TIMES; i++){
      axpy_unroll(a, dx, dy_opt, DATA_SIZE);
   }
   setStats(0);

   for (int i = 0; i < DATA_SIZE; i++){
      printf("v[%d]= %d\n", i, (long long)dy_opt[i]);
   }

   return 0;
}
