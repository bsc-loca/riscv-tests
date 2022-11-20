#include "util.h"

uint64_t _cycles ;
uint64_t _instructions ; 

uint32_t roi_start (void){
    _cycles = read_csr(mcycle);
    _instructions = read_csr(minstret);
    return 0; 
}

uint32_t roi_end (void){
    _cycles = read_csr(mcycle) - _cycles;
    _instructions = read_csr(minstret) - _instructions;
    return 0; 
}

uint32_t print_metrics (char test_name ){
    printf("\n");
    printf("--  %s  -- \n",test_name);
    printf("Cycles:  %d \n", _cycles);
    printf("Instructions:  %d \n\n",_instructions);
    return 0; 
}

