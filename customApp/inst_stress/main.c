#include <stdlib.h>
#include <stdio.h>
#include "dataset.h"
#include "spmv.h"
#include "inst_stress.h"
#include "util.h"
#include "metrics.h"

int main( int argc, char* argv[] )
{
    
    roi_start();
    
    stream_copy(ARRAY_SIZE,dataA,dataB);
    
    stream_copy_inv(ARRAY_SIZE,dataA,dataC);

    spmv(R, val, idx, x, ptr,verify_data);
    
    atomic_add(ARRAY_SIZE,dataA,dataB);
    
    atomic_and(ARRAY_SIZE,dataA,dataC);

    median(MEDIAN_DATA_SIZE, median_input_data, median_verify_data);
    
    atomic_xor(ARRAY_SIZE,dataB,dataA);
    
    atomic_mix(ARRAY_SIZE,dataA,dataB,dataC);

    jacobi_2d(DIM_SIZE,input2_data,input1_data,verify_data1);
    
    scalar_mix(ARRAY_SIZE,dataA,dataB,dataC);

    roi_end();
    print_metrics("inst_stress");
    
    exit(0);
}

//**********************************************************************
void stream_copy(const size_t size , data_t A[], data_t B[]) 
{
    for (size_t j = 0; j < size ; j++) B[j] = A[j];
    
    // verification
    for (size_t j = 0; j < size ; j++) 
    {
        if (B[j] != A[j])
        {
            printf("Error stream_copy %d \n",j); 
            exit(1);
        }
    }
}

//**********************************************************************
void stream_copy_inv(const size_t size , data_t A[], data_t B[]) 
{
    for (size_t j = 0; j < size ; j++) A[j] = B[(size-1)-j];  

    // verification
    for (size_t j = 0; j < size ; j++) 
    {
        if (B[j] != A[(size-1)-j]) 
        {
            printf("Error stream_copy_inv %d \n",j);
            exit(1);
        }
    }
}

//**********************************************************************
void spmv(int r, const long* val, const int* idx, const long* x, const int* ptr, const long* verify)
{
    long y[r];
    for (int i = 0; i < r; i++)
    {
        int k;
        long yi0 = 0, yi1 = 0, yi2 = 0, yi3 = 0;
        for (k = ptr[i]; k < ptr[i+1]-3; k+=4)
        {
            yi0 += val[k+0]*x[idx[k+0]];
            yi1 += val[k+1]*x[idx[k+1]];
            yi2 += val[k+2]*x[idx[k+2]];
            yi3 += val[k+3]*x[idx[k+3]];
        }
        for ( ; k < ptr[i+1]; k++)
        {
            yi0 += val[k]*x[idx[k]];
        }
        y[i] = (yi0+yi1)+(yi2+yi3);
    }

    // verification
    for (int i = 0; i < r/2*2; i+=2)
    {
        long t0 = y[i], t1 = y[i+1];
        long v0 = verify[i], v1 = verify[i+1];
        if (t0 != v0) exit(1);
        if (t1 != v1) exit(1);
    }
    if (r % 2 != 0 && y[r-1] != verify[r-1]) exit(1);
}

//**********************************************************************
void atomic_add(const size_t size , data_t A[], data_t B[]) 
{
    long long int x = 0;
    long long int y = 0;
    long long int z = 0;
    
    for (size_t j = 0; j < size ; j++) 
    {
       x = A[j];
       ATOMIC_OP(A[j], 1, add, w);
       y = A[j];
       if ( (x+1) != y ) 
       {
           printf("Error: S1 atomic add %d \n",j);
           exit(1);
       }
       
       x = B[j];
       ATOMIC_OP(B[j], 1, add, w);
       y = B[j];
       if ( (x+1) != y ) 
       {
           printf("Error: S2 atomic add %d \n",j);
           exit(1);
       }
       
       x = A[j];
       z = B[j];
       ATOMIC_OP(A[j],B[j], add, w);
       y = A[j];
       if ( (x+z) != y ) 
       {
           printf("Error: S3 atomic add %d \n",j);
           exit(1);
       }
    }

}

//**********************************************************************
void atomic_and(const size_t size , data_t A[], data_t B[]) 
{
    long long int x = 0;
    long long int y = 0;
    long long int z = 0;
    
    for (size_t j = 0; j < size ; j++) 
    {
       x = A[j];
       ATOMIC_OP(A[j], 1, and, w);
       y = A[j];
       if ( (x&1) != y ) 
       {
           printf("Error: S1 atomic and %d \n",j);
           exit(1);
       }
       
       x = B[j];
       ATOMIC_OP(B[j], 1, and, w);
       y = B[j];
       if ( (x&1) != y ) 
       {
           printf("Error: S2 atomic and %d \n",j);
           exit(1);
       }
       
       x = A[j];
       z = B[j];
       ATOMIC_OP(A[j],B[j], and, w);
       y = A[j];
       if ( (x&z) != y ) 
       {
           printf("Error: S3 atomic and %d \n",j);
           exit(1);
       }
    }
}

//**********************************************************************
void atomic_xor(const size_t size , data_t A[], data_t B[]) 
{
    long long int x = 0;
    long long int y = 0;
    long long int z = 0;
    
    for (size_t j = 0; j < size ; j++) 
    {
       x = A[j];
       ATOMIC_OP(A[j], 1, xor, w);
       y = A[j];
       if ( (x^1) != y ) 
       {
           printf("Error: S1 atomic xor %d \n",j);
           exit(1);
       }
       
       x = B[j];
       ATOMIC_OP(B[j], 1, xor, w);
       y = B[j];
       if ( (x^1) != y ) 
       {
           printf("Error: S2 atomic xor %d \n",j);
           exit(1);
       }
       
       x = A[j];
       z = B[j];
       ATOMIC_OP(A[j],B[j], xor, w);
       y = A[j];
       if ( (x^z) != y ) 
       {
           printf("Error: S3 atomic xor %d \n",j);
           exit(1);
       }
    }
}

//**********************************************************************
void atomic_mix(const size_t size , data_t A[], data_t B[], data_t AB[]) 
{
    long long int x = 0;
    long long int y = 0;
    
    for (size_t j = 0; j < size ; j++) 
    {
       x = A[j];
       ATOMIC_OP(A[j], AB[j], add, w);
       y = A[j];
       if ( (AB[j]+x) != y ) 
       {
           printf("Error: S1 atomic add %d \n",j);
           exit(1);
       }
       
       x = B[j];
       ATOMIC_OP(B[j], A[j], xor, w);
       y = B[j];
       if ( (x^A[j]) != y ) 
       {
           printf("Error: S2 atomic xor %d \n",j);
           exit(1);
       }
       
       x = AB[j];
       ATOMIC_OP(AB[j],B[j], and, w);
       y = AB[j];
       if ( (x&B[j]) != y ) 
       {
           printf("Error: S3 atomic and %d \n",j);
           exit(1);
       }
    }
}

//**********************************************************************
void scalar_mix(const size_t size , data_t A[], data_t B[], data_t AB[]) 
{
    long long int x = 0;
    long long int y = 0;
    long long int z = 0;
    
    for (size_t j = 0; j < size-1 ; j++) 
    {
       x = A[j];
       y = B[j];
       AB[j] = A[j]+B[j];
       if ( (x+y) != AB[j] ) 
       {
           printf("Error: S1 scalar add %d \n",j);
           exit(1);
       }
       
       x = AB[j];
       y = B[j];
       A[j] = AB[j]-B[j];
       if ( (x-y) != A[j] ) 
       {
           printf("Error: S2 scalar sub %d \n",j);
           exit(1);
       }
       
       x = AB[j];
       y = A[j];
       B[j] = AB[j]&A[j];
       if ( (x&y) != B[j] ) 
       {
           printf("Error: S3 scalar and %d \n",j);
           exit(1);
       }
       
       x = AB[j];
       y = AB[j+1];
       A[j] = AB[j]^AB[j+1];
       if ( (x^y) != A[j] ) 
       {
           printf("Error: S4 scalar xor %d \n",j);
           exit(1);
       }
    }
}

//**********************************************************************
void median(int n, int input[], int verify[])
{
    int A, B, X, i;
    int results[n];

    // Zero the ends
    results[0]   = 0;
    results[n-1] = 0;

    // Do the filter
    for ( i = 1; i < (n-1); i++ ) {

        A = input[i-1];
        B = input[i];
        X = input[i+1];

        if ( A < B ) {
            if ( B < X )
                results[i] = B;
            else if ( X < A )
                results[i] = A;
            else
                results[i] = X;
        }
        else {
            if ( A < X )
                results[i] = A;
            else if ( X < B )
                results[i] = B;
            else
                results[i] = X;
        }   
    }

    // verification
    for (int j = 0; j < n ; j++) 
    {
        if (results[j] != verify[j]) 
        {
            printf("Error median %d \n",j);
            exit(1);
        }
    }
}

//**********************************************************************
void jacobi_2d(int lda, double A[], double B[], double verify[])
{

    for (int k = 1; k < lda - 1 ; k++ ) 
            for (int i = 1; i < lda - 1 ; i++ ) 
                A[i+k*lda] = (0.2) * (B[i+k*lda] + B[(i+k*lda)-1] + B[(i+k*lda)+1] + B[(i+k*lda)-lda] + B[(i+k*lda)+lda]);

    // verification
    for (int j = 0; j < lda*lda ; j++) 
    {
        if (A[j] != verify[j]) 
        {
            printf("Error jacobi_2d %d \n",j);
            exit(1);
        }
    }

}
