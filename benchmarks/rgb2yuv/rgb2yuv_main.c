// See LICENSE for license details.

//**************************************************************************
// Vector-vector add benchmark
//--------------------------------------------------------------------------
//
// This benchmark uses adds to vectors and writes the results to a
// third vector. The input data (and reference data) should be
// generated using the vvadd_gendata.pl perl script and dumped
// to a file named dataset1.h.
 
#include "util.h"

//--------------------------------------------------------------------------
// Input/Reference Data

#include "dataset1-large.h"

//--------------------------------------------------------------------------
// vvadd function

void rgb2yuv( int n, int a[], int c[] )
{
  int i;
  for ( i = 0; i < n; i++ ) {
    // Extract RGB values from rs1
    uint8_t B = a[i] & 0xFF;               // Bits [7:0]
    uint8_t G = (a[i] >> 8) & 0xFF;        // Bits [15:8]
    uint8_t R = (a[i] >> 16) & 0xFF;       // Bits [23:16]

    // Perform RGB to YUV conversion
    uint8_t Y = (uint8_t)(0.299 * R + 0.587 * G + 0.114 * B);
    uint8_t U = (uint8_t)(0.492 * (B - Y) /*+ 128*/); // Add 128 for unsigned range
    uint8_t V = (uint8_t)(0.877 * (R - Y) /*+ 128*/); // Add 128 for unsigned range

    // Pack YUV back into a 32-bit word
    c[i] = (Y<<16) | (U << 8) | (V); 
  }
}

//--------------------------------------------------------------------------
// Main

int main( int argc, char* argv[] )
{
  int results_data[DATA_SIZE];

#if PREALLOCATE
  // If needed we preallocate everything in the caches
  rgb2yuv( DATA_SIZE, input1_data, results_data );
#endif

  // Do the rgb2yuv
  setStats(1);
  rgb2yuv( DATA_SIZE, input1_data, results_data );
  setStats(0);

  // Check the results
  // if (verify( DATA_SIZE, results_data, verify_data )) printf("Verification failed!\n");

  // Print the results
  // for (int i = 0; i < DATA_SIZE; i++) printf("%d\n", results_data[i]);

  return 0;
}
