/* -----------------------------------------------
 * Project Name   : OpenPiton + Lagarto
 * File           : hello_world_lagarto.c
 * Organization   : Barcelona Supercomputing Center
 * Author(s)      : Neiel I. Leyva Santes. 
 * Email(s)       : neiel.leyva@bsc.es
 * -----------------------------------------------*/

#include <stdio.h>
#include "uart.h"
#include "util.h"

int main(int argc, char ** argv) {

    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];

    if(cid==0) 
    {
        printf("\nWe are %d Lagarto Ka cores.\n\n",nc);
        printf("+----------------------------------------------------+  \n");
        printf("     .-.--_                                             \n");    
        printf("  ,´,´.´   `.  BSC-CNS Barcelona Supercomputing Center  \n");   
        printf("  | | | BSC |  ---------------------------------------  \n");      
        printf("  `.`.`. _ .´                                           \n");  
        printf("    `·`··                                               \n");     
        printf("+----------------------------------------------------+  \n\n");
    }
    barrier(nc);

    for(int i=0; i<nc; i++)
    {
        if(cid==i) printf("I am the Lagarto Ka No. %d: hello world!. \n",cid);
        barrier(nc);
    }
    
    
    return 0;
}




