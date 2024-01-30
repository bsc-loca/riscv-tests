#!/usr/bin/env python3
import sys
import random

m = int(sys.argv[1])
n = int(sys.argv[2])
approx_nnz = int(sys.argv[3])

pnnz = approx_nnz / (m * n)
idx = []
p = [0]

for i in range(m):
    for j in range(n):
        if random.random() < pnnz:
            idx.append(j)
    p.append(len(idx))

nnz = len(idx)
v = [random.randint(0, 1000) for _ in range(n)]
d = [random.randint(0, 1000) for _ in range(nnz)]


def print_vec(t, name, data):
    print("const", t, name + "[" + str(len(data)) + "] = {")
    print("  " + ",\n  ".join(map(str, data)))
    print("};")


def spmv(p, d, idx, v):
    y = []
    for i in range(len(p) - 1):
        yi = 0
        for k in range(p[i], p[i + 1]):
            yi += d[k] * v[idx[k]]
        y.append(yi)
    return y


print("#define R", m)
print("#define C", n)
print("#define NNZ", nnz)
print_vec("double", "val", d)
print_vec("int", "idx", idx)
print_vec("double", "x", v)
print_vec("int", "ptr", p)
print_vec("double", "verify_data", spmv(p, d, idx, v))