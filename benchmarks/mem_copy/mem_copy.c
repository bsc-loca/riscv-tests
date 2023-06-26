#include <sys/types.h>
#include "util.h"


#define NumI 10000
uint32_t a[NumI], b[NumI];


int main(int argc, char* argv[]) {

    printf("\n   *** Mem Copy  BENCHMARK TEST ***\n\n");
    printf("N = %d \n", NumI);

    for(uint32_t i = 0; i < NumI; i++){ a[i] = 5; }

    setStats(1);

    for(uint32_t i = 0; i < NumI; i++){ b[i] = a[i]; }

    setStats(0);

}

