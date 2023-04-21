#include <stdio.h>
#include <stdlib.h>


#define ATOMIC_OP(mem, i, asm_op, asm_type)  mem = mem + i
#define ATOMIC_FETCH_OP(ret, mem, i, asm_op, asm_type) ret = mem; mem= mem +i; 
void BARRIER(){} 
void barrier (int x){};

#include "../is.c"

#define ncores 4

void int_sort_scalar ( int nc) {    
   for(int i = 0; i <nc ; i++) offset[i] =0;
   for(int cid=0;cid<ncores;cid++)  histogram ( cid, nc, TOTAL_KEYS, key_array, key_buff, key_histogram );	
   for(int i = 0; i <MAX_KEY ; i++) printf (" %d,",key_histogram[i]);
   for(int cid=0;cid<ncores;cid++)  cumulative_sum_1( cid, nc, MAX_KEY, key_histogram,offset );
   for(int cid=0;cid<ncores;cid++)  cumulative_sum_2( cid, nc, MAX_KEY, key_histogram,offset );
   //for(int i = 0; i <MAX_KEY ; i++) printf (" %d,",key_histogram[i]);

  
   for(int cid=0;cid<ncores;cid++)  sort_keys (cid, nc, TOTAL_KEYS, key_array, key_buff, key_histogram,offset );
}





int main (){
    
    int_sort_scalar(ncores);  
    /*
    for(int cid=0;cid<ncores;cid++) {
	    int res = sort_verify(cid,ncores,TOTAL_KEYS , key_verify, key_array);
	   if(res ){
			printf("Verrification failed!\n");
			exit(res);  
	   }
    }  
   */
    for (int i=0; i < TOTAL_KEYS; i++){
   	if (key_verify [i] != key_array [i]){
   		printf("failed! i=%u : key_verify (%u) != key_array [%u] \n",i, key_verify [i] , key_array [i]);
   		return 1;
   	}else{
   	//printf("passed! i=%u : key_verify (%u) != key_array [%u] \n",i, key_verify [i] , key_array [i]);
   	}
    }	
    printf("passed!\n");
    return 0;
}
