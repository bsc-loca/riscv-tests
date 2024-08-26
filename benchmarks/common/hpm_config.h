#ifndef __CONFIG_HPM_H
#define __CONFIG_HPM_H

#include "hpm.h"

/*-
  --------------------- 
      LAGARTO KA
  --------------------- 

|0               |10  not_supported    |20 rob_full     |30 dcache_stall_refill   |40 not_supported     |50 VPU_lane_active_9     |60 l15_access   
|1 branch_miss   |11  not_supported    |21 frl_empty    |31 dcache_rtab_rollback  |41 VPU_lane_active_0 |51 VPU_lane_active_10    |61 noc1_flit_val 
|2 is_branch     |12  not_supported    |22 itlb_access  |32 dcache_req_onhold     |42 VPU_lane_active_1 |52 VPU_lane_active_11    |62 noc2_flit_val 
|3 branch_taken  |13  icache_miss      |23 itlb_miss    |33 dcache_prefetch_req   |43 VPU_lane_active_2 |53 VPU_lane_active_12    |63 noc3_flit_val 
|4 execute_store |14  icache_miss_kill |24 dtlb_access  |34 dcache_read_req       |44 VPU_lane_active_3 |54 VPU_lane_active_13    |64 noc1_stall 
|5 execute_load  |15  icache_busy      |25 dtlb_miss    |35 dcache_write_req      |45 VPU_lane_active_4 |55 VPU_lane_active_14    |65 noc2_stall 
|6 icache_req    |16  icache_miss_time |26 ptw_hit      |36 dcache_cmo_req        |46 VPU_lane_active_5 |56 VPU_lane_active_15    |66 noc3_stall 
|7 icache_kill   |17  is_load_store    |27 ptw_miss     |37 dcache_uncached_req   |47 VPU_lane_active_6 |57 l2_miss
|8 stall_fetch   |18  not_supported    |28 itlb_stall   |38 dcache_miss_read_req  |48 VPU_lane_active_7 |58 l2_access
|9 stall_decode  |19  not_supported    |29 dcache_stall |39 dcache_miss_write_req |49 VPU_lane_active_8 |59 l15_miss
                                                                                      
  --------------------- 
      SARGANTANA
  --------------------- 

|0               |10  stall_rr         |20 grad_list_full  |30 dcache_stall_refill   |40 stall_ir          |50 noc3_stall   |60    -     
|1 branch_miss   |11  stall_exe        |21 free_list_empty |31 dcache_rtab_rollback  |41 l2_miss           |51    -         |61    -    
|2 is_branch     |12  stall_wb         |22 itlb_access     |32 dcache_req_onhold     |42 l2_access         |52    -         |62    -    
|3 branch_taken  |13  icache_miss      |23 itlb_miss       |33 dcache_prefetch_req   |43 l15_miss          |53    -         |63    -    
|4 execute_store |14  icache_miss_kill |24 dtlb_access     |34 dcache_read_req       |44 l15_access        |54    -         |64    -    
|5 execute_load  |15  icache_busy      |25 dtlb_miss       |35 dcache_write_req      |45 noc1_flit_val     |55    -         |65    -    
|6 icache_req    |16  icache_miss_time |26 ptw_hit         |36 dcache_cmo_req        |46 noc2_flit_val     |56    -         |66    -    
|7 icache_kill   |17  is_load_store    |27 ptw_miss        |37 dcache_uncached_req   |47 noc3_flit_val     |57    -      
|8 stall_fetch   |18  data_depend      |28 itlb_stall      |38 dcache_miss_read_req  |48 noc1_stall        |58    -      
|9 stall_decode  |19  struct_depend    |29 dcache_stall    |39 dcache_miss_write_req |49 noc2_stall        |59    -      

-*/

 static uint8_t hpm_config[HPM_COUNTERS] = {
 /*  - unused - */
     0,    0,    0,
 /*  3     4     5     6     7     8     9    10  */
     1,    2,    3,   34,   35,   37,   38,   39,
 /* 11    12    13    14    15    16    17    18    19    20 */
    41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
 /* 21    22    23    24    25    26    27    28    29    30    31*/
    51,   52,   53,   54,   55,   56,    6,   13,   15,   30,   29   
 };


//static uint8_t hpm_config[HPM_COUNTERS] = { //sargantana
///*  - unused - */
//    0,    0,    0,
///*  3     4     5     6     7     8     9    10  */
//    1,    2,    3,   34,   35,   37,   38,   39,
///* 11    12    13    14    15    16    17    18    19    20 */
//    4,    5,   36,   27,   28,   17,   41,   42,   43,   44,
///* 21    22    23    24    25    26    27    28    29    30    31*/
//   30,   22,   23,   24,   25,   26,    6,   13,   15,   30,   47   
//};

#endif
