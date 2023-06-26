#include <sys/types.h>
#include "util.h"

extern void asm_basic_loop_arith(int);

int main(int argc, char* argv[]) {

    uint32_t Iterations = 1000;

    printf("\n   *** MAX FLOPS BENCHMARK TEST ***\n\n");
    printf("N = %d \n", Iterations);

    setStats(1);

    asm_basic_loop_arith(Iterations);

    setStats(0);

}
