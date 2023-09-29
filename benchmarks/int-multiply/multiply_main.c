// See LICENSE for license details.

// *************************************************************************
// multiply filter bencmark
// -------------------------------------------------------------------------
//
// This benchmark tests the software multiply implemenation. The
// input data (and reference data) should be generated using the
// multiply_gendata.pl perl script and dumped to a file named
// dataset1.h

#include <stdlib.h>
#include "util.h"

#include "multiply.h"
#include "metrics.h"

//--------------------------------------------------------------------------
// Input/Reference Data

#include "dataset.h"

//--------------------------------------------------------------------------
// Main

int main( int argc, char* argv[] )
{
  int i;
  int results_data[DATA_SIZE];

#if PREALLOCATE
  for (i = 0; i < DATA_SIZE; i++)
  {
    results_data[i] = multiply( input_data1[i], input_data2[i] );
  }
#endif
  
  roi_start();  
  for (i = 0; i < DATA_SIZE; i++)
  {
    results_data[i] = multiply( input_data1[i], input_data2[i] );
  }
  roi_end(); 
  print_metrics("int-multiply");

  
  // Check the results
  exit (verify_int( DATA_SIZE, results_data, verify_data ));
}
