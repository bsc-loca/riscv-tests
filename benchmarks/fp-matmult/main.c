/*----------------------------------------------------------------------*
 * To make this program compile under our assumed embedded environment,
 * we had to make several changes:
 * - Declare all functions in ANSI style, not K&R.
 *   this includes adding return types in all cases!
 * - Declare function prototypes
 * - Disable all output
 * - Disable all UNIX-style includes
 *
 * This is a program that was developed from mm.c to matmult.c by
 * Thomas Lundqvist at Chalmers.
 *----------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "dataset.h"

/*
 * MATRIX MULTIPLICATION BENCHMARK PROGRAM:
 * This program multiplies 2 square matrices resulting in a 3rd
 * matrix. It tests a compiler's speed in handling multidimensional
 * arrays and simple arithmetic.
 */

void __attribute__((noinline)) matmul(const size_t n,  const data_t *A, const data_t *B, data_t *C);

/*
 *
 */

int main (int argc, char** argv){
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];
   
#if PREALLOCATE
    stats(matmul(DIM_SIZE, input1_data, input2_data, results_data), DIM_SIZE/DIM_SIZE/DIM_SIZE);
#endif
    stats(matmul(DIM_SIZE, input1_data, input2_data, results_data), DIM_SIZE/DIM_SIZE/DIM_SIZE);

    exit(verifyFloat(ARRAY_SIZE, results_data, verify_data)); 
}


void matmul(const size_t n,  const data_t *A, const data_t *B, data_t *C)
{
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      data_t sum = 0;
      for (size_t k = 0; k < n; k++) sum += A[j*n + k] * B[k*n + i];
      C[i + j*n] = sum;
    }
  }
}
