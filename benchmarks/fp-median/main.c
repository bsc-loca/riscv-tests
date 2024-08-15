// See LICENSE for license details.

//**************************************************************************
// Median filter bencmark
//--------------------------------------------------------------------------
//
// This benchmark performs a 1D three element median filter. The
// input data (and reference data) should be generated using the
// median_gendata.pl perl script and dumped to a file named
// dataset1.h.

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"

// Input/Reference Data
#include "dataset.h"

extern void __attribute__((noinline)) median(size_t n, data_t *input, data_t *results);

/*
 *
 */

int main (int argc, char** argv){
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];

#if PREALLOCATE
    stats(median( DATA_SIZE, input_data, results_data ),DATA_SIZE);
#endif
    stats(median( DATA_SIZE, input_data, results_data ),DATA_SIZE);
  
    // Check the results
    exit(verifyFloat( DATA_SIZE, results_data, verify_data ));
}
