#ifndef __INST_H
#define __INST_H

extern void __attribute__((noinline)) stream_copy     (const size_t size , data_t A[], data_t B[]); 
extern void __attribute__((noinline)) stream_copy_inv (const size_t size , data_t A[], data_t B[]); 
extern void __attribute__((noinline)) spmv            (int r, const long* val, const int* idx, const long* x, const int* ptr, const long* verify);
extern void __attribute__((noinline)) atomic_add      (const size_t size , data_t A[], data_t B[]); 
extern void __attribute__((noinline)) atomic_and      (const size_t size , data_t A[], data_t B[]); 
extern void __attribute__((noinline)) atomic_xor      (const size_t size , data_t A[], data_t B[]); 
extern void __attribute__((noinline)) atomic_mix      (const size_t size , data_t A[], data_t B[], data_t AB[]); 
extern void __attribute__((noinline)) scalar_mix      (const size_t size , data_t A[], data_t B[], data_t AB[]); 
extern void __attribute__((noinline)) median          (int n, int input[], int verify[]);
extern void __attribute__((noinline)) jacobi_2d       (int lda, double A[], double B[], double verify[]);

#endif //__INST_H
