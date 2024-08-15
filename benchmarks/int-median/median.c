// See LICENSE for license details.

#include <stddef.h>
#include "dataset.h"
//**************************************************************************
// Median filter (c version)
//--------------------------------------------------------------------------

void median(size_t n, data_t *input, data_t *results)
{
  data_t A, B, C;

  // Zero the ends
  results[0]   = 0;
  results[n-1] = 0;

  // Do the filter
  for (size_t i = 1; i < (n-1); i++ ) {

    A = input[i-1];
    B = input[i];
    C = input[i+1];

    if ( A < B ) {
      if ( B < C )
        results[i] = B;
      else if ( C < A )
        results[i] = A;
      else
        results[i] = C;
    }

    else {
      if ( A < C )
        results[i] = A;
      else if ( C < B )
        results[i] = B;
      else
        results[i] = C;
    }

  }

}
