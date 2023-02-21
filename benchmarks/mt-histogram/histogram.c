#include <sys/types.h>
#include <sys/times.h>
#include <stdio.h>

#include "util.h"
#include "metrics.h"
#include "dataset1.h"

int histogram[16] = {};

int cores_count;
int core_data_lenght;

int main(int argc, char** argv) {
    
    // get the number of hardware cores we have available in the system
    cores_count = argv[0][1];
    core_data_lenght = DATA_SIZE/cores_count;
    
    // get the local core hardware id
    int coreID = argv[0][0];

    // Printing some info
    if(coreID == 0) printf(" Executing with : %u Cores\n", cores_count);
    barrier(cores_count);

    // Calculate the cores begin and end of the data chunks
    int begining = coreID * core_data_lenght;
    int ending = (coreID + 1) * core_data_lenght;
    
    if(coreID == 0) roi_start();    
    
    //-------------------------
    // ROI
    for(int x=begining; x<ending; x++){
        histogram[data[x]] += 1;
    }
    //-------------------------
    barrier(cores_count);
    
    if(coreID == 0){
        roi_end();    
        print_metrics("histogram");
    
        //Verification
        int cnt = 0;
        for (int x=0; x<16; x++) cnt=cnt+histogram[x]; 
        if(cnt != DATA_SIZE) {
            printf("Error: Only %d were counted. \n", cnt);
            return 1;
        } else return 0;
    }

}
