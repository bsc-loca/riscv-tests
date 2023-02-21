#include <sys/types.h>
#include <sys/times.h>
#include <stdio.h>

#include "metrics.h"
#include "util.h"
#include "dataset.h"

int main (void)  {
    int i, j;          
    double aux;
    
    roi_start(); 
    //----------------------------------------------------------
    // ROI
    for (i=0;i<DATA_SIZE;i++) { 
        for (j=0;j<DATA_SIZE-1;j++) { 
            if (input_data[j]>=input_data[j+1]) { 
                aux=input_data[j]; 
			    input_data[j]=input_data[j+1]; 
			    input_data[j+1]=aux; 
            } 
        } 
    } 
    //----------------------------------------------------------
    roi_end(); 
    print_metrics("fd-bubblesort");

                    
	int error=0;                
	for (i=0;i<DATA_SIZE;i++) { 
        if (input_data[i] != verify_data[i]){
            error = 1;
            printf("The program failed in element %d ,input_data %d , verify_data %d \n", 
                    i,input_data[i] ,verify_data[i]);
			return error;
		}
	}
    
    return error; 
} 
