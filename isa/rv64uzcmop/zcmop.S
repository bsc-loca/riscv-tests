#Test for c.mop.1, c.mop.3, c.mop.5, c.mop.7
#c.mop.9, c.mop.11, c.mop.13, c.mop.15 instructions

#include "riscv_test.h"
#include "test_macros.h"

RVTEST_RV64U
RVTEST_CODE_BEGIN

    #----------c.mop.n behaviour section----------

    #trivial test trying all the instructions as there's nothing more to check
    .irp n,1,3,5,7,9,11,13,15
    li x\n, 0xdeadbeefdeadbeef
    c.mop.\n
    .endr

    j pass

    TEST_PASSFAIL

RVTEST_CODE_END

    .data
RVTEST_DATA_BEGIN

    TEST_DATA

RVTEST_DATA_END