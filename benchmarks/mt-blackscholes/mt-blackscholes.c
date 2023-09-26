// Copyright (c) 2007 Intel Corp.

// Black-Scholes
// Analytical method for calculating European Options
//
// 
// Reference Source: Options, Futures, and Other Derivatives, 3rd Edition, Prentice 
// Hall, John C. Hull,

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//--------------------------------------------------------------------------
// Input/Reference Data
#include "dataset.h"

//--------------------------------------------------------------------------
// Basic Utilities and Multi-thread Support
#include "util.h"

//////////////////////////////////////////////////////////////////////////////
/*
        otype      = Option type.  "P"=PUT, "C"=CALL
        sptprice   = spot price
        strike     = strike price
        rate       = risk-free interest rate
        volatility = volatility
        otime      = time to maturity or option expiration in years
                     (1yr = 1.0, 6mos = 0.5, 3mos = 0.25, ..., etc)
        DGrefval   = DerivaGem Reference Value
*/


void _blackscholes_(int nc, int cid, data_t priceDelta[]);
int verify_blackscholes(int nc, int cid, data_t priceDelta[]);

//-----------------------------------------------------
// MAIN

int main(int argc, char** argv) {
   
    uint32_t cid = argv[0][0];
    uint32_t nc  = argv[0][1];
     
    if(cid==0) printf("\nWe are %d cores.\n",nc); 
    barrier(nc);        

//--------------------------------------------------------
//ROI
    stats(_blackscholes_(nc,cid,priceDelta);barrier(nc), ARRAY_SIZE);
    barrier(nc);
//--------------------------------------------------------
    int res = verify_blackscholes(nc,cid,priceDelta);
    barrier(nc);        
    
    if(res){
        printf("Core %d: Verification failed!\n",cid);
        exit(1);  
    }
    exit(0);
}

