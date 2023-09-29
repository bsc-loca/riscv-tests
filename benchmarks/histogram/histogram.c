#include <sys/types.h>
#include <sys/times.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "metrics.h"

#include "dataset.h"

uint32_t histogram[HISTOGRAM_SIZE] = {};

int cores_count;
int core_data_lenght;

int main(int argc, char** argv) {

    // get the number of hardware cores we have available in the system
    cores_count = 1;
    core_data_lenght = DATA_SIZE/cores_count;

    int coreID = 0;

    // Calculate the cores begin and end of the data chunks
    int begining = coreID * core_data_lenght;
    int ending = (coreID + 1) * core_data_lenght;

    roi_start();    
    //-------------------------
    // ROI
	for(int x=begining; x<ending; x++){
		histogram[data[x]] += 1;
	}
    //-------------------------
    roi_end();    
    print_metrics("histogram");

    for (int k=0; k<HISTOGRAM_SIZE; k++){
        if(verify_data[k] != histogram[k]) exit(1); 
    }  
    exit(0) ;

}
