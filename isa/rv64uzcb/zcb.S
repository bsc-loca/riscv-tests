#Test for c.lbu, c.lhu, c.lh, c.sb
#c.sh, c.zext.b, c.sext.b, c.zext.h
#c.sext.h, c.zext.w, c.not, c.mul instructions

#include "riscv_test.h"
#include "test_macros.h"

RVTEST_RV64U
RVTEST_CODE_BEGIN

    #----------c.lbu and c.sb section----------

    la a0, zcbData
    la a1, zcbBuffer
    addi s0, a0, 124 

loadStoreByteLoop:
    #Loading each byte for each word in the dataset with some dependencies tests and pipeline stress
    c.lbu a2, 0(a0)
    c.sb a2, 0(a1)
    c.sb a2, 0(a1)

    c.lbu a3, 1(a0)
    c.sb a3, 1(a1)
    c.lbu a2, 0(a1)
    c.sb a3, 1(a1)
    c.lbu a3, 1(a1)

    c.lbu a2, 2(a0)
    c.sb a2, 2(a1)
    c.sb a3, 2(a1)
    c.lbu a3, 1(a1)
    c.lbu a2, 2(a0)
    c.sb a2, 2(a1)
    c.sb a3, 2(a1)

    c.lbu a2, 3(a0)
    c.sb a2, 3(a1)
    c.lbu a3, 3(a1)      
    c.lbu a2, 0(a0)
    c.sb a2, 3(a1)

    addi a0, a0, 4
    addi a1, a1, 4

    bltu a0, s0, loadStoreByteLoop

    #----------c.lh, c.lhu and c.sh section----------

    la a0, zcbData
    la a1, zcbBuffer
    addi s0, a0, 124 

loadStoreHalfwordLoop:
    #Loading each halfword for each word in the dataset with some dependencies tests and pipeline stress
    c.lhu a2, 0(a0)
    c.sh a2, 0(a1)
    c.lhu a2, 0(a1)
    c.lh a3, 0(a1)
    c.lh a2, 2(a0)
    c.sh a2, 0(a1)

    c.lhu a2, 2(a0)
    c.sh a2, 2(a1)
    c.lhu a3, 2(a1)
    c.lhu a2, 0(a0)
    c.sh a2, 2(a1)
    c.lh a2, 2(a0)
    c.sh a2, 2(a1)

    addi a0, a0, 4
    addi a1, a1, 4

    bltu a0, s0, loadStoreHalfwordLoop

    #----------c.zext.b and c.sext.b section----------

    la a0, zcbData
    la a1, zcbBuffer
    addi s0, a0, 124 

extensionsByteLoop:
    #Extending each byte for each word in the dataset with some dependencies tests and pipeline stress
    c.lbu a2, 0(a0)
    c.zext.b a2
    c.lbu a2, 0(a0)
    c.sext.b a2
    c.sb a2, 0(a1)

    addi a0, a0, 1
    c.lbu a2, 0(a0)
    addi a0, a0, -1
    c.zext.b a2
    c.lbu a2, 1(a0)
    c.sext.b a2
    addi a1, a1, 1
    c.sb a2, 0(a1)
    addi a1, a1, -1

    c.lbu a2, 2(a0)
    c.zext.b a2
    c.lbu a2, 2(a0)
    c.sext.b a2
    c.sb a2, 2(a1)

    c.lbu a2, 3(a0)
    c.zext.b a2
    c.lbu a2, 3(a0)
    c.sext.b a2
    c.sb a2, 3(a1)

    addi a0, a0, 4
    addi a1, a1, 4

    bltu a0, s0, extensionsByteLoop

    #----------c.zext.h and c.sext.h section----------

    la a0, zcbData
    la a1, zcbBuffer
    addi s0, a0, 124 

extensionsHalfLoop:
    #Extending each halfword for each word in the dataset with some dependencies tests and pipeline stress
    c.lhu a2, 0(a0)
    c.zext.h a2
    c.lhu a2, 0(a0)
    c.sext.h a2
    c.sh a2, 0(a1)

    addi a0, a0, 2
    c.lhu a2, 0(a0)
    addi a0, a0, -2
    c.zext.h a2
    c.lhu a2, 2(a0)
    c.sext.h a2
    addi a1, a1, 2
    c.sh a2, 0(a1)
    addi a1, a1, -2

    c.lh a2, 0(a0)
    c.zext.h a2
    c.lh a2, 0(a0)
    c.sext.h a2
    c.sh a2, 0(a1)

    c.lh a2, 2(a0)
    c.zext.h a2
    c.lh a2, 2(a0)
    c.sext.h a2
    c.sh a2, 2(a1)
    c.lhu a3, 2(a1)
    c.sext.h a3

    addi a0, a0, 4
    addi a1, a1, 4

    bltu a0, s0, extensionsHalfLoop

    #----------c.zext.w section----------

    la a0, zcbData
    la a1, zcbBuffer
    addi s0, a0, 124 

czextwLoop:
    #Trying c.zext.w with some dependencies checks
    lw a2, 0(a0)
    c.zext.w a2
    sw a2, 0(a1)
    lw a3, 0(a1)
    c.zext.w a3

    addi a0, a0, 4
    addi a1, a1, 4

    bltu a0, s0, czextwLoop

    #----------c.not section----------

    la a0, zcbData
    la a1, zcbBuffer
    addi s0, a0, 124 

cnotLoop:
    #Trying c.not with some dependencies checks
    lw a2, 0(a0)
    c.not a2
    sw a2, 0(a1)
    lw a2, 0(a1)
    c.not a2
    c.not a2
    sw a2, 0(a1)

    addi a0, a0, 4
    addi a1, a1, 4

    bltu a0, s0, cnotLoop

    #----------c.mul section----------

    la a0, zcbData
    la a1, zcbBuffer
    addi s0, a0, 124 

cmulOuterLoop:
    lw a2, 0(a0)

    la a3, zcbData
    add a4, a1, zero
cmulInnerLoop:
    #Just testing all the values among them (NxN, even if there's redundancy) with a little dependencies check
    lw a5, 0(a3)
    c.mul a5, a2
    sw a5, 0(a4)
    lw a5, 0(a4)
    c.mul a5, a2

    addi a4, a4, 4
    addi a3, a3, 4
    bltu a3, s0, cmulInnerLoop

    addi a0, a0, 4
    bltu a0, s0, cmulOuterLoop


    j pass

    TEST_PASSFAIL

RVTEST_CODE_END

    .data
RVTEST_DATA_BEGIN

    TEST_DATA

zcbData:
    .word 0x00000000 #Interesting value for all the instructions
    .word 0xffffffff #Interesting value for all the instructions, especially for c.not
    .word 0x80000001 #Interesting value for all the instructions
    .word 0x0000007f #Boundary value for c.sext.b (max positive) 
    .word 0x00000080 #Boundary value for c.sext.b (min negative)
    .word 0x000000ff #Interesting value for all the byte extension instructions
    .word 0x00007fff #Boundary value for c.sext.h (max positive) 
    .word 0x00008000 #Boundary value for c.sext.h (min negative)
    .word 0x0000ffff #Interesting value for all the haflword extension instructions
    .word 0x80000000 #Interesting value for c.zext.w
    .word 0x7fffffff #Interesting value for c.zext.w
    .word 0x55555555 #Bit toggling value for c.not
    .word 0xaaaaaaaa #Bit toggling value for c.not
    .word 0xff00ff00 #Pattern tot test c.not
    .word 0x00ff00ff #Pattern tot test c.not
    .word 0x12345678 #Value to detect possible offset or endianess bugs
    .word 0x87654321 #Value to detect possible offset or endianess bugs
    .word 0xdeadbeef #Useful value to debug adressing
    .word 0x7fff7fff #Two consecutive boundary values for c.sext.h (max positive)
    .word 0x80008000 #Two consecutive boundary values for c.sext.h (min negative)
    .word 0x7f7f7f7f #Four consecutive boundary values for c.sext.b (max positive)
    .word 0x80808080 #Four consecutive boundary values for c.sext.b (min negative)
    .word 0xffff8000 #Sign-extended min negative halfword
    .word 0x0000ff80 #Random negative halfword
    .word 0x00001534 #Random positive halfword
    .word 0x00000001 #Interesting value for c.mul
    .word 0x00000002 #Interesting value for c.mul, especially to test it with 0x40000000 or 0x7fffffff
    .word 0x40000000 #Interesting value for c.mul, especially to test it with 0x00000002
    .word 0x00010001 #Interesting value for c.mul, especially to test truncated overflow with 0x0000ffff
    .word 0xfffffffe #Interesting value for c.mul
    .word 0x00010000 #Interesting value for c.mul

zcbBuffer:           #31 words -> .space 124
    .space 124 

RVTEST_DATA_END