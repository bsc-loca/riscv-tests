#include <sys/types.h>
#include <sys/times.h>

#include "util.h"

#include "dataset1.h"

int histogram[16] = {};

int cores_count;
int core_data_lenght;

int main(int argc, char** argv) {

    //printf("\n   *** HISTOGRAM BENCHMARK TEST ***\n");
    //printf("   N = %d \n", DATA_SIZE);

    // get the number of hardware cores we have available in the system
    //cores_count = get_core_count();
    cores_count = 1;
    core_data_lenght = DATA_SIZE/cores_count;

    // Printing some info
    //printf("   Executing with : %u Cores\n", cores_count);

    // wakeup all the cores
    //_cores_fork_(cores_count);

    // get the local core hardware id
    //int coreID = get_core_id();
    int coreID = 0;

    // Calculate the cores begin and end of the data chunks
    int begining = coreID * core_data_lenght;
    int ending = (coreID + 1) * core_data_lenght;


    unsigned long cycle = read_csr(mcycle);
    unsigned long instr = read_csr(minstret); 

    //-------------------------
    // ROI
	for(int x=begining; x<ending; x++){
		histogram[data[x]] += 1;
	}
    //-------------------------


    printf("Cycles:  %d \n",read_csr(mcycle) - cycle);
    printf("Instructions:  %d \n\n",read_csr(minstret) - instr);
    
    // synchronize the cores execution
    //barrier(cores_count);

    // put the core except the 0 to idle mode
    //_core_idle_(coreID);

    printf("Output : ");

    for (int x=0; x<16; x++) printf("%u:%u,", x, histogram[x]);
    printf("\n");

    return 0;
}
