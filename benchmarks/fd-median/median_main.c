// See LICENSE for license details.

//**************************************************************************
// Median filter bencmark
//--------------------------------------------------------------------------
//
// This benchmark performs a 1D three element median filter. The
// input data (and reference data) should be generated using the
// median_gendata.pl perl script and dumped to a file named
// dataset1.h.

#include "util.h"
#include "median.h"
#include "metrics.h"

//--------------------------------------------------------------------------
// Input/Reference Data

#include "dataset1.h"

//--------------------------------------------------------------------------
// Main

int main( int argc, char* argv[] )
{
  double results_data[DATA_SIZE];

#if PREALLOCATE
  // If needed we preallocate everything in the caches
  median( DATA_SIZE, input_data, results_data );
#endif

  // Do the filter
  
  roi_start();
  median( DATA_SIZE, input_data, results_data );
  roi_end();
  print_metrics("fd-median");
   
  
  // Check the results
  return verifyDouble( DATA_SIZE, results_data, verify_data );
}
