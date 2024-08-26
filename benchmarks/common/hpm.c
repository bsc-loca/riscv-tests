#include <stdio.h>
#include <stdint.h>
#include "encoding.h"
#include "util.h"
#include "hpm_config.h"
#include "hpm.h"

static uint64_t counters[HPM_COUNTERS];

void __hpm_config__(uint8_t id[]) {
#ifdef HPM_ENABLE
    __write_hpmevents(3,id[3]);
    for(size_t i=4; i<HPM_COUNTERS; i+=4) {
        __write_hpmevents(i,id[i]);
        __write_hpmevents(i+1,id[i+1]);
        __write_hpmevents(i+2,id[i+2]);
        __write_hpmevents(i+3,id[i+3]);
    }
#endif
}

void __hpm_start_read__(){
#ifdef HPM_ENABLE
    __read_hpmcounter(3,counters[3]);
    for(size_t i=4; i<HPM_COUNTERS; i+=4) {
        __read_hpmcounter(i,counters[i]);
        __read_hpmcounter(i+1,counters[i+1]);
        __read_hpmcounter(i+2,counters[i+2]);
        __read_hpmcounter(i+3,counters[i+3]);
    }
#endif
}

void __hpm_end_eval__(){
#ifdef HPM_ENABLE
    static uint64_t tmp[HPM_COUNTERS];
    __read_hpmcounter(3,tmp[3]);
    counters[3] = tmp[3] - counters[3];
    for (size_t i = 4; i < HPM_COUNTERS; i+=4) {
        __read_hpmcounter(i,tmp[i]);
        __read_hpmcounter(i+1,tmp[i+1]);
        __read_hpmcounter(i+2,tmp[i+2]);
        __read_hpmcounter(i+3,tmp[i+3]);
        counters[i] = tmp[i] - counters[i];
        counters[i+1] = tmp[i+1] - counters[i+1];
        counters[i+2] = tmp[i+2] - counters[i+2];
        counters[i+3] = tmp[i+3] - counters[i+3];
    }
#endif
}

void __hpm_print__(size_t cores, size_t coreid){
#ifdef HPM_ENABLE
    for(size_t i = 0; i < cores; i++){
        if(coreid == i){
            printf("\n--- Core %d: Performance Monitoring Counters --- \n", coreid);
            for (size_t i = 3; i < HPM_COUNTERS; i++) printf("mhpmcounter%d :  %d \n", i, counters[i]);
            printf("\n");
        }
        barrier(cores);
    }
#endif
}

