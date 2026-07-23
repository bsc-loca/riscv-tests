#Test for mop.r.0-31 and mop.rr.0-7 instructions

#include "riscv_test.h"
#include "test_macros.h"

RVTEST_RV64U
RVTEST_CODE_BEGIN

    #----------mop.r.n register combinations section----------
    
    #rd starts already at zero (trivial but cheap sanity check)
    .irp n,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    li x1, 0
    mop.r.\n x1, x1
    add x1, x1, x1          #Dependencies check
    .endr

    #rd field sweep (rs1 fixed = x1)
    .irp n,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    li x1, 0xdeadbeefdeadbeef
    .irp rd,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31
    li \rd, 0xffffffffffffffff
    mop.r.\n \rd, x1
    add \rd, \rd, \rd       #Dependencies check
    .endr
    .endr

    #rd == x0
    .irp n,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    li x1, 0x0123456789abcdef
    mop.r.\n x0, x1
    .endr

    #rs1 field sweep (rd fixed = x1)
    .irp n,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    .irp rs1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31
    li x1, 0x0000000000000001
    li \rs1, 0x8000000000000000
    mop.r.\n x1, \rs1
    li x1, 0x0000000000000001       #Dependencies check
    add x1, x1, x1
    .endr
    .endr

    #rs1 == x0
    .irp n,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    li x1, 0xaaaaaaaaaaaaaaaa
    mop.r.\n x1, x0
    add x1, x1, x1          #Dependencies check
    .endr

    #rd == rs1
    .irp n,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    .irp reg,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31
    li \reg, 0x5555555555555555
    mop.r.\n \reg, \reg
    add \reg, \reg, \reg    #Dependencies check
    .endr
    .endr

    #----------mop.rr.n register combinations section----------

    #rd field sweep (rs1 fixed = x1, rs2 fixed = x2)
    .irp n,0,1,2,3,4,5,6,7
    li x1, 0xdeadbeefdeadbeef
    li x2, 0x5555555555555555
    .irp rd,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31
    li \rd, 0xffffffffffffffff
    mop.rr.\n \rd, x1, x2
    add \rd, \rd, \rd       #Dependencies check
    .endr
    .endr

    #rs1 field sweep (rd fixed = x1, rs2 fixed = x2)
    .irp n,0,1,2,3,4,5,6,7
    .irp rs1,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31
    li x1, 0x0123456789abcdef
    li x2, 0xfedcba9876543210 
    li \rs1, 0xffffffff
    mop.rr.\n x1, \rs1, x2
    li x1, 0x0000000000000001       #Dependencies check
    add x1, x1, x1
    .endr
    .endr

    #rs2 field sweep (rd fixed = x1, rs1 fixed = x2)
    .irp n,0,1,2,3,4,5,6,7
    .irp rs2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31
    li x1, 0xffffffffffffffff
    li x2, 0xdeadbeefdeadbeef
    li \rs2, 0x5555555555555555
    mop.rr.\n x1, x2, \rs2
    add x1, x1, x1          #Dependencies check
    .endr
    .endr

    #rd == rs1
    .irp n,0,1,2,3,4,5,6,7
    .irp reg,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31
    li \reg, 0xaaaaaaaaaaaaaaaa
    li x1, 0x5555555555555555
    mop.rr.\n \reg, \reg, x1
    add \reg, \reg, \reg    #Dependencies check
    .endr
    .endr

    #rd == rs2
    .irp n,0,1,2,3,4,5,6,7
    .irp reg,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31
    li \reg, 0xdeadbeefdeadbeef
    li x1, 0x5555555555555555
    mop.rr.\n \reg, x1, \reg
    add \reg, \reg, \reg    #Dependencies check
    .endr
    .endr

    #rs1 == rs2
    .irp n,0,1,2,3,4,5,6,7
    .irp reg,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31
    li x1, 0x1111111111111111
    li \reg, 0xeeeeeeeeeeeeeeee
    mop.rr.\n x1, \reg, \reg
    add x1, x1, x1          #Dependencies check
    .endr
    .endr
    
    #rd == rs1 == rs2
    .irp n,0,1,2,3,4,5,6,7
    .irp reg,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31
    li \reg, 0xbedbedbedbedbed1
    mop.rr.\n \reg, \reg, \reg
    add \reg, \reg, \reg    #Dependencies check
    .endr
    .endr

    #x0 in each field position
    .irp n,0,1,2,3,4,5,6,7
    li x1, 0x1010101010101010
    li x2, 0x0101010101010101
    mop.rr.\n x0, x1, x2              #rd == x0
    mop.rr.\n x1, x0, x2              #rs1 == x0
    mop.rr.\n x1, x2, x0              #rs2 == x0
    .endr

    j pass

    TEST_PASSFAIL

RVTEST_CODE_END

    .data
RVTEST_DATA_BEGIN

    TEST_DATA

RVTEST_DATA_END