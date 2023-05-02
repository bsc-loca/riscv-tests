#ifndef __DATASET_H
#define __DATASET_H
#define ARRAY_SIZE 8 
#define NUM_RUNS  100

typedef float data_t;

static int otype[ARRAY_SIZE]=
{
0,1,1,0,0,0,0,0
};

static data_t sptprice[ARRAY_SIZE]=
{
42, 42, 100, 100, 60, 100, 100, 100
};

static data_t strike[ARRAY_SIZE]= 
{
40, 40, 100, 100, 65, 90, 90, 90
};

static data_t rate[ARRAY_SIZE]=
{
0.1, 0.1, 0.05, 0.05, 0.08, 0.1, 0.1, 0.1
};

static data_t volatility[ARRAY_SIZE]=
{
0.20, 0.20, 0.15, 0.15, 0.30, 0.10, 0.10, 0.10
};
 
static data_t otime[ARRAY_SIZE]=
{
0.50,0.50,1.00,1.00,0.25,0.10,0.50,1.00
};

static data_t DGrefval[ARRAY_SIZE]=
{
4.759423036851750055,0.808600016880314021,3.714602051381290071,8.591659601309890704,2.133371966735750025,
10.895610714793999563,14.421570828843300660,18.630859120667498274
};

static data_t priceDelta[ARRAY_SIZE]=
{
0,0,0,0,0,0,0,0
};

#endif //__DATASET_H
