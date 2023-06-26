#include <sys/types.h>
#include "util.h"

extern void asm_basic_loop(int);

int main(int argc, char* argv[]) {

    uint32_t Iterations = 10000;

    printf("\n   *** MAX MIPS BENCHMARK TEST ***\n\n");
    printf("N = %d \n", Iterations);

    setStats(1);

    asm_basic_loop(Iterations);

    setStats(0);

}
