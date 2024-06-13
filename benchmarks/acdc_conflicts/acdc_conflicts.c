// See LICENSE for license details.

//**************************************************************************
// acdc_conflicts benchmark
//--------------------------------------------------------------------------
//
// This benchmark implements a code with aliased accesses in cache
// in order to illustrate the benefits of an ACDC.

#include "util.h"
#include <string.h>
#include <limits.h>

#define NITERS		1000 /* Default number of runs */
#define L1_STRIDE 8192
#define NSTRIDES 6
#define INT_STRIDE L1_STRIDE/sizeof(int)
#define SIZE INT_STRIDE * NSTRIDES

void init_vector(int *pv, long n, int value)
{
   for (int i=0; i<n; i++){ 
     pv[i]= value;
   }
}

int v [SIZE];

//--------------------------------------------------------------------------
// Main
//--------------------------------------------------------------------------

int main( int argc, char* argv[] ){

   printf("\n   *** ACDC COLISIONS BENCHMARK TEST ***\n\n");
   printf("Number of iterations:%d\n",NITERS);

   int* v1;
   int* v2;
   int* v3;
   int* v4;

   /* Allocate the example vectors */
   //v = (int*) malloc(8192*10);
   v1 = v + INT_STRIDE;
   v2 = v + 2*INT_STRIDE;
   v3 = v + 3*INT_STRIDE;
   v4 = v + 4*INT_STRIDE;


   int a,b,c,d,e,f;
   
   setStats(1);
   for (int i = 0; i < NITERS; i++) {
      a = v[i];
      b = v1[i];
      c = v2[i];
      d = v3[i];
      e = v4[i];
      f = a + b + c + d + e + f;
   }
   setStats(0);

   //free(v);

   return f;
}
