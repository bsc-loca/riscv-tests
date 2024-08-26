#ifndef __HPM_H
#define __HPM_H

#include <stdint.h>
#include "encoding.h"

#define HPM_COUNTERS 32

#define __write_hpmevents(index, val) do { \
    switch (index) { \
        case 3:  write_csr(mhpmevent3,  val); break; \
        case 4:  write_csr(mhpmevent4,  val); break; \
        case 5:  write_csr(mhpmevent5,  val); break; \
        case 6:  write_csr(mhpmevent6,  val); break; \
        case 7:  write_csr(mhpmevent7,  val); break; \
        case 8:  write_csr(mhpmevent8,  val); break; \
        case 9:  write_csr(mhpmevent9,  val); break; \
        case 10: write_csr(mhpmevent10, val); break; \
        case 11: write_csr(mhpmevent11, val); break; \
        case 12: write_csr(mhpmevent12, val); break; \
        case 13: write_csr(mhpmevent13, val); break; \
        case 14: write_csr(mhpmevent14, val); break; \
        case 15: write_csr(mhpmevent15, val); break; \
        case 16: write_csr(mhpmevent16, val); break; \
        case 17: write_csr(mhpmevent17, val); break; \
        case 18: write_csr(mhpmevent18, val); break; \
        case 19: write_csr(mhpmevent19, val); break; \
        case 20: write_csr(mhpmevent20, val); break; \
        case 21: write_csr(mhpmevent21, val); break; \
        case 22: write_csr(mhpmevent22, val); break; \
        case 23: write_csr(mhpmevent23, val); break; \
        case 24: write_csr(mhpmevent24, val); break; \
        case 25: write_csr(mhpmevent25, val); break; \
        case 26: write_csr(mhpmevent26, val); break; \
        case 27: write_csr(mhpmevent27, val); break; \
        case 28: write_csr(mhpmevent28, val); break; \
        case 29: write_csr(mhpmevent29, val); break; \
        case 30: write_csr(mhpmevent30, val); break; \
        case 31: write_csr(mhpmevent31, val); break; \
    } \
} while (0)

#define __read_hpmcounter(index, r) do { \
    switch (index) { \
        case 3:  r = read_csr(mhpmcounter3 ); break; \
        case 4:  r = read_csr(mhpmcounter4 ); break; \
        case 5:  r = read_csr(mhpmcounter5 ); break; \
        case 6:  r = read_csr(mhpmcounter6 ); break; \
        case 7:  r = read_csr(mhpmcounter7 ); break; \
        case 8:  r = read_csr(mhpmcounter8 ); break; \
        case 9:  r = read_csr(mhpmcounter9 ); break; \
        case 10: r = read_csr(mhpmcounter10); break; \
        case 11: r = read_csr(mhpmcounter11); break; \
        case 12: r = read_csr(mhpmcounter12); break; \
        case 13: r = read_csr(mhpmcounter13); break; \
        case 14: r = read_csr(mhpmcounter14); break; \
        case 15: r = read_csr(mhpmcounter15); break; \
        case 16: r = read_csr(mhpmcounter16); break; \
        case 17: r = read_csr(mhpmcounter17); break; \
        case 18: r = read_csr(mhpmcounter18); break; \
        case 19: r = read_csr(mhpmcounter19); break; \
        case 20: r = read_csr(mhpmcounter20); break; \
        case 21: r = read_csr(mhpmcounter21); break; \
        case 22: r = read_csr(mhpmcounter22); break; \
        case 23: r = read_csr(mhpmcounter23); break; \
        case 24: r = read_csr(mhpmcounter24); break; \
        case 25: r = read_csr(mhpmcounter25); break; \
        case 26: r = read_csr(mhpmcounter26); break; \
        case 27: r = read_csr(mhpmcounter27); break; \
        case 28: r = read_csr(mhpmcounter28); break; \
        case 29: r = read_csr(mhpmcounter29); break; \
        case 30: r = read_csr(mhpmcounter30); break; \
        case 31: r = read_csr(mhpmcounter31); break; \
    } \
} while (0)

void __hpm_config__(uint8_t id[]);
void __hpm_start_read__();
void __hpm_end_eval__();
void __hpm_print__();
unsigned long __read_mhpcounter(int i);

#endif

