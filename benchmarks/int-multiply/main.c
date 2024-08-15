// See LICENSE for license details.

// *************************************************************************
// multiply filter bencmark
// -------------------------------------------------------------------------
//
// This benchmark tests the software multiply implemenation. The
// input data (and reference data) should be generated using the
// multiply_gendata.pl perl script and dumped to a file named
// dataset1.h

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

// Input/Reference Data
#include "dataset.h"

extern void __attribute__((noinline)) multiply (size_t n, data_t *a, data_t *b, data_t *result);

/*
 *
 */

int main(int argc, char** argv) {
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];

#if PREALLOCATE
    stats(multiply(DATA_SIZE,input_data1,input_data2,results_data),DATA_SIZE);
#endif
    stats(multiply(DATA_SIZE,input_data1,input_data2,results_data),DATA_SIZE);
  
    // Check the results
    exit (verify_int( DATA_SIZE, results_data, verify_data ));
}
