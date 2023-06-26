#include <sys/types.h>
#include "util.h"

#define SETS 128 
#define WAYS 8 
#define WORDS_PER_BLOCK 8

#define WORDS_PER_WAY WORDS_PER_BLOCK*SETS

int main(int argc, char* argv[]) {
    
    long long int *pointer_0;
    pointer_0 =(long long int*)(0x81000000);
    long long int *pointer_1;
    pointer_1 = pointer_0 + WORDS_PER_WAY;
    long long int *pointer_2;
    pointer_2 = pointer_1 + WORDS_PER_WAY;
    long long int *pointer_3;
    pointer_3 = pointer_2 + WORDS_PER_WAY;
    long long int *pointer_4;
    pointer_4 = pointer_3 + WORDS_PER_WAY;
    long long int *pointer_5;
    pointer_5 = pointer_4 + WORDS_PER_WAY;
    long long int *pointer_6;
    pointer_6 = pointer_5 + WORDS_PER_WAY;
    long long int *pointer_7;
    pointer_7 = pointer_6 + WORDS_PER_WAY;

    printf("\n   *** Mem Flush Test ***\n\n");
    printf("sets = %d \n", SETS);
    printf("ways = %d \n", WAYS);
    printf("WORDS_PER_WAY = %d \n", WORDS_PER_WAY);

    setStats(1);
    for(long long int i = 0; i < SETS; i++){ 
        *pointer_0 = 0x1010101010101010;
        pointer_0 = pointer_0 + 8;
        *pointer_1 = 0x1010101010101010;
        pointer_1 = pointer_1 + 8;
        *pointer_2 = 0x1010101010101010;
        pointer_2 = pointer_2 + 8;
        *pointer_3 = 0x1010101010101010;
        pointer_3 = pointer_3 + 8;
        *pointer_4 = 0x1010101010101010;
        pointer_4 = pointer_4 + 8;
        *pointer_5 = 0x1010101010101010;
        pointer_5 = pointer_5 + 8;
        *pointer_6 = 0x1010101010101010;
        pointer_6 = pointer_6 + 8;
        *pointer_7 = 0x1010101010101010;
        pointer_7 = pointer_7 + 8;
    }


    pointer_0 =(long long int*)(0x82000000);
    pointer_1 = pointer_0 + WORDS_PER_WAY;
    pointer_2 = pointer_1 + WORDS_PER_WAY;
    pointer_3 = pointer_2 + WORDS_PER_WAY;
    pointer_4 = pointer_3 + WORDS_PER_WAY;
    pointer_5 = pointer_4 + WORDS_PER_WAY;
    pointer_6 = pointer_5 + WORDS_PER_WAY;
    pointer_7 = pointer_6 + WORDS_PER_WAY;

    for(long long int i = 0; i < SETS; i++){ 
        *pointer_0 = 0xffffffffffffffff;
        pointer_0 = pointer_0 + 8;
        *pointer_1 = 0xffffffffffffffff;
        pointer_1 = pointer_1 + 8;
        *pointer_2 = 0xffffffffffffffff;
        pointer_2 = pointer_2 + 8;
        *pointer_3 = 0xffffffffffffffff;
        pointer_3 = pointer_3 + 8;
        *pointer_4 = 0xffffffffffffffff;
        pointer_4 = pointer_4 + 8;
        *pointer_5 = 0xffffffffffffffff;
        pointer_5 = pointer_5 + 8;
        *pointer_6 = 0xffffffffffffffff;
        pointer_6 = pointer_6 + 8;
        *pointer_7 = 0xffffffffffffffff;
        pointer_7 = pointer_7 + 8;
    }
    setStats(0);
}

