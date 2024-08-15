// See LICENSE for license details.

//**************************************************************************
// Quicksort benchmark
//--------------------------------------------------------------------------
//
// This benchmark uses quicksort to sort an array of integers. The
// implementation is largely adapted from Numerical Recipes for C. The
// input data (and reference data) should be generated using the
// qsort_gendata.pl perl script and dumped to a file named
// dataset1.h

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include "util.h"

//--------------------------------------------------------------------------
// Input/Reference Data
#include "dataset.h"

#define LOG_BASE 8
#define BASE (1 << LOG_BASE)

#if 0
# define fetch_add(ptr, inc) __sync_fetch_and_add(ptr, inc)
#else
# define fetch_add(ptr, inc) ((*(ptr) += (inc)) - (inc))
#endif

void __attribute__((noinline)) sort(size_t n, data_t* arrIn, data_t* scratchIn);

/*
 *
 */

int main (int argc, char** argv){
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];
 
    printf("\nWe are %d cores.\n",nc);

#if PREALLOCATE
    verify_int(DATA_SIZE, input_data, input_data);
#endif
    
    stats(sort(DATA_SIZE, input_data, scratch), DATA_SIZE);

    // Check the results
    exit(verify_int(DATA_SIZE, input_data, verify_data));
}

void sort(size_t n, data_t* arrIn, data_t* scratchIn)
{
  size_t log_exp = 0;
  size_t buckets[BASE];
  size_t *bucket = buckets;
  asm("":"+r"(bucket));
  data_t *arr = arrIn, *scratch = scratchIn, *p;
  size_t *b;
 
  while (log_exp < CHAR_BIT * sizeof(data_t))
  {
    for (b = bucket; b < bucket + BASE; b++)
      *b = 0;

    for (p = arr; p < &arr[n-3]; p += 4)
    {
      data_t a0 = p[0];
      data_t a1 = p[1];
      data_t a2 = p[2];
      data_t a3 = p[3];
      fetch_add(&bucket[(a0 >> log_exp) % BASE], 1);
      fetch_add(&bucket[(a1 >> log_exp) % BASE], 1);
      fetch_add(&bucket[(a2 >> log_exp) % BASE], 1);
      fetch_add(&bucket[(a3 >> log_exp) % BASE], 1);
    }
    for ( ; p < &arr[n]; p++)
      bucket[(*p >> log_exp) % BASE]++;

    size_t prev = bucket[0];
    prev += fetch_add(&bucket[1], prev);
    for (b = &bucket[2]; b < bucket + BASE; b += 2)
    {
      prev += fetch_add(&b[0], prev);
      prev += fetch_add(&b[1], prev);
    }
    static_assert(BASE % 2 == 0);

    for (p = &arr[n-1]; p >= &arr[3]; p -= 4)
    {
      data_t a0 = p[-0];
      data_t a1 = p[-1];
      data_t a2 = p[-2];
      data_t a3 = p[-3];
      size_t* pb0 = &bucket[(a0 >> log_exp) % BASE];
      size_t* pb1 = &bucket[(a1 >> log_exp) % BASE];
      size_t* pb2 = &bucket[(a2 >> log_exp) % BASE];
      size_t* pb3 = &bucket[(a3 >> log_exp) % BASE];
      data_t* s0 = scratch + fetch_add(pb0, -1);
      data_t* s1 = scratch + fetch_add(pb1, -1);
      data_t* s2 = scratch + fetch_add(pb2, -1);
      data_t* s3 = scratch + fetch_add(pb3, -1);
      s0[-1] = a0;
      s1[-1] = a1;
      s2[-1] = a2;
      s3[-1] = a3;
    }
    for ( ; p >= &arr[0]; p--)
      scratch[--bucket[(*p >> log_exp) % BASE]] = *p;

    data_t* tmp = arr;
    arr = scratch;
    scratch = tmp;

    log_exp += LOG_BASE;
  }
  if (arr != arrIn)
    memcpy(arr, scratch, n*sizeof(data_t));
}
