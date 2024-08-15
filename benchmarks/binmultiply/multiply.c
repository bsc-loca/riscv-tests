// See LICENSE for license details.

#include <stddef.h>
#include "dataset.h"
// *************************************************************************
// multiply function (c version)
// -------------------------------------------------------------------------

int BinaryMultiply( int x, int y ){
    int result = 0;
    for (size_t i = 0; i < 32; i++) {
        if ((x & 0x1) == 1) result = result + y;
        x = x >> 1;
        y = y << 1;
    } 
    return result;
}

void multiply (size_t n, data_t *a, data_t *b, data_t *result){
    for (size_t i = 0; i < n; i++) result[i] = BinaryMultiply(a[i], b[i]);
} 
