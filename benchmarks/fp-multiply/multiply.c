// See LICENSE for license details.

#include <stddef.h>
#include "dataset.h"
// *************************************************************************
// multiply function (c version)
// -------------------------------------------------------------------------

void multiply (size_t n, data_t *a, data_t *b, data_t *result){
    for (size_t i = 0; i < n; i++) result[i] = a[i] * b[i];
} 
