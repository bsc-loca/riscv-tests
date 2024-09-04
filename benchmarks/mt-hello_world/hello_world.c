/* -----------------------------------------------
 * Project Name   : OpenPiton + Lagarto
 * File           : hello_world_lagarto.c
 * Organization   : Barcelona Supercomputing Center
 * Author(s)      : Neiel I. Leyva Santes. 
 * Email(s)       : neiel.leyva@bsc.es
 * -----------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "util.h"

int main(int argc, char ** argv) {

    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];

    volatile static uint32_t core_sync = 0;

    if(cid==0) 
    {
        printf("\nWe are %d cores.\n\n",nc);
        printf("+----------------------------------------------------+  \n");
        printf("     .-.--_                                             \n");    
        printf("  ,´,´.´   `.  BSC-CNS Barcelona Supercomputing Center  \n");   
        printf("  | | | BSC |  ---------------------------------------  \n");      
        printf("  `.`.`. _ .´                                           \n");  
        printf("    `·`··                                               \n");     
        printf("+----------------------------------------------------+  \n\n");
    }
    barrier(nc);

    while(cid != core_sync);    
    
    printf("I am the core No. %d: hello world!. \n",cid);
    
    ATOMIC_OP(core_sync, 1, add, w);
    
    exit (0);
}




