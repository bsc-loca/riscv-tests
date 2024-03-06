#!/bin/bash

SIZES='
 512      
 1024     
 2048     
 3072     
 4096     
 6144     
 8192     
 12288    
 16384    
 24576    
 32768    
 49152    
 65536    
 131072   
 262144   
 524288   
 1048576  
    '

 ##512      // 2     KB
 ##1024     // 4     KB
 ##2048     // 8     KB
 ##3072     // 12    KB
 ##4096     // 16    KB
 ##6144     // 24    KB
 ##8192     // 32    KB
 ##12288    // 48    KB
 ##16384    // 64    KB
 ##24576    // 96    KB
 ##32768    // 128   KB
 ##49152    // 192   KB
 ##65536    // 256   KB
 ##131072   // 512   KB
 ##262144   // 1     MB
 ##524288   // 2     MB
 ##1048576  // 4     MB

for size in $SIZES
do
    ./test/gendata.pl --size $size > test/dataset.h
    make 
    mv test.riscv test_$size.riscv
    mv test.riscv.dump test_$size.riscv.dump
done
