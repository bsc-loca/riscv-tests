# Directed test: reserved rs2 encoding under
# F7_64_ROLW_RORW_CLZW_CTZW_CPOPW must raise illegal instruction.
#include "riscv_test.h"
#include "test_macros.h"

RVTEST_RV64M
RVTEST_CODE_BEGIN

  .align 2
  .option norvc

  li TESTNUM, 2

bad_rs2:
  .word 0x6030909B     # reserved rs2=3 under CLZW/CTZW/CPOPW group
  j fail                # safety net if trap doesn't fire

  TEST_PASSFAIL

  .align 8
  .global mtvec_handler
mtvec_handler:
  li t1, CAUSE_ILLEGAL_INSTRUCTION
  csrr t0, mcause
  bne t0, t1, fail

  csrr t0, mepc
  la t1, bad_rs2
  bne t0, t1, fail

  j pass

RVTEST_CODE_END
  .data
RVTEST_DATA_BEGIN
  TEST_DATA
RVTEST_DATA_END
