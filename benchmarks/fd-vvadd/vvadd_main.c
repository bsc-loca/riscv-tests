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
#include "util.h"
#include "metrics.h"

//--------------------------------------------------------------------------
// Input/Reference Data

#include "dataset1.h"

//--------------------------------------------------------------------------
// vvadd function

void vvadd( int n, double a[], double b[], double c[] )
{
  int i;
  for ( i = 0; i < n; i++ )
    c[i] = a[i] + b[i];
}

//--------------------------------------------------------------------------
// Main

int main( int argc, char* argv[] )
{
  double results_data[DATA_SIZE];

#if PREALLOCATE
  // If needed we preallocate everything in the caches
  vvadd( DATA_SIZE, input1_data, input2_data, results_data );
#endif

  roi_start(); 
  vvadd( DATA_SIZE, input1_data, input2_data, results_data );
  roi_end(); 
  print_metrics("fd-vvadd");

  // Check the results
  exit (verifyDouble( DATA_SIZE, results_data, verify_data ));
}
