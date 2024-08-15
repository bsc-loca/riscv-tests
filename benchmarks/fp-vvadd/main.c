// See LICENSE for license details.

//**************************************************************************
// Vector-vector add benchmark
//--------------------------------------------------------------------------
//
// This benchmark uses adds to vectors and writes the results to a
// third vector. The input data (and reference data) should be
// generated using the vvadd_gendata.pl perl script and dumped
// to a file named dataset1.h.
 
#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "dataset.h"

void __attribute__((noinline)) vvadd( size_t n, data_t *a, data_t *b, data_t *c );

/*
 *
 */

int main (int argc, char** argv){
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];

#if PREALLOCATE
    stats(vvadd( DATA_SIZE, input1_data, input2_data, results_data ),DATA_SIZE);
#endif
    stats(vvadd( DATA_SIZE, input1_data, input2_data, results_data ),DATA_SIZE);

    // Check the results
    exit (verifyFloat( DATA_SIZE, results_data, verify_data ));
}

void vvadd( size_t n, data_t *a, data_t *b, data_t *c )
{
  for (size_t i = 0; i < n; i++ ) c[i] = a[i] + b[i];
}
