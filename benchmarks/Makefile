#=======================================================================
# UCB VLSI FLOW: Makefile for riscv-bmarks
#-----------------------------------------------------------------------
# Yunsup Lee (yunsup@cs.berkeley.edu)
#

XLEN ?= 64
default: all
src_dir = .

#--------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------

# Original lista for references	
bmarks = 			\
	hello_world  	\
	dhrystone 		\
	fibonacci  		\
	rsort 			\
	binmultiply 	\
	histogram   	\
	towers 			\
	int-bsort  		\
	int-qsort 		\
	int-matmult 	\
	int-median 		\
	int-multiply 	\
	int-spmv 		\
	int-vvadd 		\
	fp-bsort  		\
	fp-qsort 		\
	fp-matmult 		\
	fp-median 		\
	fp-multiply 	\
	fp-spmv 		\
	fp-vvadd 		\
	mm 				\
	mt-hello_world  \
	mt-histogram   	\
	mt-vvadd 		\
	mt-matmul 		\
	mt-axpy   		\
	mt-somier   	\
	mt-stream-copy  \
	mt-stream-triad \
	mt-int-sort   	\
	mt-blackscholes \
	mt-jacobi_2d   	\
	mt-spmv      	\
	#pmp \
#--------------------------------------------------------------------
# Build rules
#--------------------------------------------------------------------

RISCV_PREFIX ?= riscv$(XLEN)-unknown-elf-
RISCV_GCC ?= $(RISCV_PREFIX)gcc

RISCV_GCC_OPTS ?= -mcmodel=medany -static -std=gnu99 -O2 -ffast-math -fno-common -fno-builtin-printf -march=rv64imafd -mabi=lp64d -Wno-implicit-int -Wno-implicit-function-declaration -Wno-incompatible-pointer-types
RISCV_GCC_OPTS += $(GCC_OPT) $(TARGET) 
RISCV_LINK ?= $(RISCV_GCC) -T $(src_dir)/common/test.ld $(incs)
RISCV_LINK_OPTS ?= -static -nostdlib -nostartfiles -lm -lc -lgcc -specs=nano.specs -specs=nosys.specs -T $(src_dir)/common/test.ld
RISCV_OBJDUMP ?= $(RISCV_PREFIX)objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.data
RISCV_OBJCOPY ?= $(RISCV_PREFIX)objcopy -O binary

incs  += -I$(src_dir)/../env -I$(src_dir)/common 
objs  :=

define compile_template
$(1).riscv: $(wildcard $(src_dir)/$(1)/*) $(wildcard $(src_dir)/common/*)
	$$(RISCV_GCC) $$(incs) -I/$(1) $$(RISCV_GCC_OPTS) -o $$@ $(wildcard $(src_dir)/$(1)/*.c) $(wildcard $(src_dir)/common/*.c) $(wildcard $(src_dir)/common/*.S) $$(RISCV_LINK_OPTS)
endef

$(foreach bmark,$(bmarks),$(eval $(call compile_template,$(bmark))))

#------------------------------------------------------------
# Build and run benchmarks on riscv simulator

bmarks_riscv_bin  = $(addsuffix .riscv,  $(bmarks))
bmarks_riscv_dump = $(addsuffix .riscv.dump, $(bmarks))
bmarks_riscv_fpga = $(addsuffix .bin, $(bmarks))

$(bmarks_riscv_dump): %.riscv.dump: %.riscv
	$(RISCV_OBJDUMP) $< > $@

$(bmarks_riscv_fpga): %.bin: %.riscv
	$(RISCV_OBJCOPY) $< $@

riscv: $(bmarks_riscv_dump)

fpga: TARGET=-DFPGA 	
fpga: $(bmarks_riscv_fpga)

junk += $(bmarks_riscv_bin) $(bmarks_riscv_dump) $(bmarks_riscv_fpga) 

#------------------------------------------------------------
# Default

all: riscv

#------------------------------------------------------------
# Clean up

clean:
	rm -rf $(objs) $(junk)
