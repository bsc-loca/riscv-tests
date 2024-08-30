RISC-V ISA tests and Benchmarks
================

RISC-V ISA tests and Benchmarks compatibles with OpenPiton.

### Set RISC-V environment

    export RISCV=/path/to/installation/directory
    export PATH=$RISCV/bin:$PATH
    export LD_LIBRARY_PATH=$RISCV/lib:$LD_LIBRARY_PATH
    export C_INCLUDE_PATH=$RISCV/include:$C_INCLUDE_PATH
    export CPLUS_INCLUDE_PATH=$RISCV/include:$CPLUS_INCLUDE_PATH

### Build RISC-V C and C++ cross-compiler
    
    git clone https://github.com/riscv/riscv-gnu-toolchain
    ./configure --prefix=$RISCV --with-arch=rv64imafd --with-cmodel=medany
    make -j$(nproc) 

### Build ISA tests

    cd isa
    make -j$(nproc)

### Build Benchmarks (single-thread)

    cd benchmarks
    make -j$(nproc)

### Build Benchmarks (multi-thread)

    make -j$(nproc) GCC_OPT=-DNUMTILES=4

### Build Benchmarks to use in FPGA (single-thread)

    make -j$(nproc) fpga

### Build Benchmarks to use in FPGA (multi-thread)

    make -j$(nproc) GCC_OPT=-DNUMTILES=4 fpga

### Build Benchmarks with the Cache Warm-up enabled (single-thread - multi-thread - FPGA)

    make -j$(nproc) GCC_OPT=-DPREALLOCATE
    make -j$(nproc) GCC_OPT="-DPREALLOCATE -DNUMTILES=4"
    make -j$(nproc) GCC_OPT=-DPREALLOCATE fpga
    make -j$(nproc) GCC_OPT="-DPREALLOCATE -DNUMTILES=4" fpga



Available Benchmarks
=============================

### Integer operations (single-thread)

| No  | Benchmark      |Data Type | Problem Size | 
|-----|----------------|----------|--------------|
| 1   |dhrystone       | int      | 1k runs      | 
| 2   |fibonacci       | int      | 16 numbers   |
| 3   |towers          | int      | 10 Discs     |
| 4   |binmultiply     | int      | 24 KB        |
| 5   |histogram       | uint32\_t | 64 KB        |
| 6   |rsort           | uint32\_t | 32 KB        |
| 7   |int-bsort       | long     | 4 KB         |
| 8   |int-qsort       | long     | 32 KB        |
| 9   |int-matmult     | int      | 12 KB        |
| 10  |int-median      | int      | 32 KB        |
| 11  |int-multiply    | int      | 24 KB        |
| 12  |int-spmv        | long     | 135 KB       |
| 13  |int-vvadd       | int      | 24 KB        |

### Floating-point operations (single-thread)

| No | Benchmark      |Data Type | Problem Size | 
|----|----------------|----------|--------------|
| 1  |fp-bsort        | double   | 4 KB         |
| 2  |fp-qsort        | double   | 32 KB        |
| 3  |fp-matmult      | float    | 12 KB        |
| 4  |fp-median       | float    | 32 KB        |
| 5  |fp-multiply     | float    | 24 KB        |
| 6  |fd-spmv         | double   | 135 KB       |
| 7  |fd-vvadd        | float    | 24 KB        |

### Multi-thread Benchmarks 

| No  | Benchmark      |Data Type | Problem Size | 
|-----|----------------|----------|--------------|
| 1   |mt-axpy         | double   | 256 KB       |
| 2   |mt-stream-copy  | double   | 256 KB       |
| 3   |mt-stream-triad | double   | 192 KB       |
| 4   |mt-vvadd        | double   | 96 KB        |
| 5   |mt-blackscholes | float    | 64 KB        |
| 6   |mt-jacobi\_2d   | double   | 64 KB        |
| 7   |mt-matmul       | double   | 96 KB        |
| 8   |mt-somier       | double   | 93 KB        |
| 9   |mt-histogram    | int      | 64 KB        |
| 10  |mt-int-sort     | int      | 64 KB        |
| 11  |mt-spmv         | double   | 57 KB        |
| 12  |mm              | double   | 13 KB        |


### SPMV Avalilable Datasets 

|    Name    | Rows   |  Cols  |   NNZ   | Source | Size  |
|------------|--------|--------|---------|--------|-------|
| spm0       | 16     | 5300   | 1020    |   -    | 57 KB |
| nv1        | 75468  | 75468  | 2449194 | [Link](https://sparse.tamu.edu/VLSI/nv1) | 39 MB |
| poisson3Db | 85623  | 85623  | 2374949 | [Link](https://www.cise.ufl.edu/research/sparse/matrices/FEMLAB/poisson3Db.html) | 38 MB |
| bcsstk39   | 46772  | 46772  | 1068033 | [Link](https://www.cise.ufl.edu/research/sparse/matrices/Boeing/bcsstk39.html) | 17 MB |
| Lin        | 256000 | 256000 | 1011200 | [Link](https://www.cise.ufl.edu/research/sparse/matrices/Lin/Lin.html) | 21 MB |

  
   
   



=========================       ========================= 

**ooooooooooooooooooooooooooooooooooooooooooooooooooooo**

=========================       ========================= 




riscv-tests
================

About
-----------

This repository hosts unit tests for RISC-V processors.

Building from repository
-----------------------------

We assume that the RISCV environment variable is set to the RISC-V tools
install path, and that the riscv-gnu-toolchain package is installed.

    $ git clone https://github.com/riscv/riscv-tests
    $ cd riscv-tests
    $ git submodule update --init --recursive
    $ autoconf
    $ ./configure --prefix=$RISCV/target
    $ make
    $ make install

The rest of this document describes the format of test programs for the RISC-V
architecture.

Test Virtual Machines
-------------------------

To allow maximum reuse of a given test, each test program is constrained to
only use features of a given *test virtual machine* or TVM. A TVM hides
differences between alternative implementations by defining:

* The set of registers and instructions that can be used. 
* Which portions of memory can be accessed.
* The way the test program starts and ends execution. 
* The way that test data is input.
* The way that test results are output.

The following table shows the TVMs currently defined for RISC-V. All of these
TVMs only support a single hardware thread.

TVM Name | Description
--- | ---
`rv32ui` | RV32 user-level, integer only
`rv32si` | RV32 supervisor-level, integer only
`rv64ui` | RV64 user-level, integer only
`rv64uf` | RV64 user-level, integer and floating-point
`rv64uv` | RV64 user-level, integer, floating-point, and vector
`rv64si` | RV64 supervisor-level, integer only
`rv64sv` | RV64 supervisor-level, integer and vector

A test program for RISC-V is written within a single assembly language file,
which is passed through the C preprocessor, and all regular assembly
directives can be used. An example test program is shown below. Each test
program should first include the `riscv test.h` header file, which defines the
macros used by the TVM. The header file will have different contents depending
on the target environment for which the test will be built.  One of the goals
of the various TVMs is to allow the same test program to be compiled and run
on very different target environments yet still produce the same results. The
following table shows the target environment currently defined.

Target Environment Name | Description
--- | ---
`p` | virtual memory is disabled, only core 0 boots up
`pm` | virtual memory is disabled, all cores boot up
`pt` | virtual memory is disabled, timer interrupt fires every 100 cycles
`v` | virtual memory is enabled

Each test program must next specify for which TVM it is designed by including
the appropriate TVM macro, `RVTEST_RV64U` in this example. This specification
can change the way in which subsequent macros are interpreted, and supports
a static check of the TVM functionality used by the program.

The test program will begin execution at the first instruction after
`RVTEST_CODE_BEGIN`, and continue until execution reaches an `RVTEST_PASS`
macro or the `RVTEST_CODE_END` macro, which is implicitly a success. A test
can explicitly fail by invoking the `RVTEST_FAIL` macro.

The example program contains self-checking code to test the result of the add.
However, self-checks rely on correct functioning of the processor instructions
used to implement the self check (e.g., the branch) and so cannot be the only
testing strategy.

All tests should also contain a test data section, delimited by
`RVTEST_DATA_BEGIN` and `RVTEST_DATA_END`. There is no alignment guarantee for
the start of the test data section, so regular assembler alignment
instructions should be used to ensure desired alignment of data values. This
region of memory will be captured at the end of the test to act as a signature
from the test. The signature can be compared with that from a run on the
golden model.

Any given test environment for running tests should also include a timeout
facility, which will class a test as failing if it does not successfully
complete a test within a reasonable time bound.

    #include "riscv_test.h"

    RVTEST_RV64U        # Define TVM used by program.

    # Test code region.
    RVTEST_CODE_BEGIN   # Start of test code.
            lw      x2, testdata
            addi    x2, 1         # Should be 42 into $2.
            sw      x2, result    # Store result into memory overwriting 1s.
            li      x3, 42        # Desired result.
            bne     x2, x3, fail  # Fail out if doesn't match.
            RVTEST_PASS           # Signal success.
    fail:
            RVTEST_FAIL
    RVTEST_CODE_END     # End of test code.

    # Input data section.
    # This section is optional, and this data is NOT saved in the output.
    .data
            .align 3
    testdata:
            .dword 41

    # Output data section.
    RVTEST_DATA_BEGIN   # Start of test output data region.
            .align 3
    result:
            .dword -1
    RVTEST_DATA_END     # End of test output data region.

User-Level TVMs
--------------------

Test programs for the `rv32u*` and `rv64u*` TVMs can contain all instructions
from the respective base user-level ISA (RV32 or RV64), except for those with
the SYSTEM major opcode (syscall, break, rdcycle, rdtime, rdinstret). All user
registers (pc, x0-x31, f0-f31, fsr) can be accessed.

The `rv32ui` and `rv64ui` TVMs are integer-only subsets of `rv32u` and `rv64u`
respectively. These subsets can not use any floating-point instructions (major
opcodes: LOAD-FP, STORE-FP, MADD, MSUB, NMSUB, NMADD, OP-FP), and hence cannot
access the floating-point register state (f0-f31 and fsr). The integer-only
TVMs are useful for initial processor bringup and to test simpler
implementations that lack a hardware FPU.

Note that any `rv32ui` test program is also valid for the `rv32u` TVM, and
similarly `rv64ui` is a strict subset of `rv64u`. To allow a given test to run
on the widest possible set of implementations, it is desirable to write any
given test to run on the smallest or least capable TVM possible. For example,
any simple tests of integer functionality should be written for the `rv64ui`
TVM, as the same test can then be run on RV64 implementations with or without a
hardware FPU. As another example, all tests for these base user-level TVMs will
also be valid for more advanced processors with instruction-set extensions.

At the start of execution, the values of all registers are undefined. All
branch and jump destinations must be to labels within the test code region of
the assembler source file. The code and data sections will be relocated
differently for the various implementations of the test environment, and so
test program results shall not depend on absolute addresses of instructions or
data memory. The test build environment should support randomization of the
section relocation to provide better coverage and to ensure test signatures do
not contain absolute addresses.

Supervisor-Level TVMs
--------------------------

The supervisor-level TVMs allow testing of supervisor-level state and
instructions.  As with the user-level TVMs, we provide integer-only
supervisor-level TVMs indicated with a trailing `i`.

History and Acknowledgements
---------------------------------

This style of test virtual machine originated with the T0 (Torrent-0) vector
microprocessor project at UC Berkeley and ICSI, begun in 1992. The main
developers of this test strategy were Krste Asanovic and David Johnson. A
precursor to `torture` was `rantor` developed by Phil Kohn at ICSI.

A variant of this testing approach was also used for the Scale vector-thread
processor at MIT, begun in 2000. Ronny Krashinsky and Christopher Batten were
the principal architects of the Scale chip. Jeffrey Cohen and Mark Hampton
developed a version of torture capable of generating vector-thread code.
