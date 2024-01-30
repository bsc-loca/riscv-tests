.global asm_basic_loop
asm_basic_loop:
  li t0, 0x4010000000000000
  li t1, 0x4000000000000000
  li t2, 0x4020000000000000
  fmv.d.x f18, t0
  fmv.d.x f19, t1
  fmv.d.x f20, t2
  xor t0, t0, t0
  blez a0, fin_loop
ini_loop:
  fsqrt.d f0, f18
  fsqrt.d f1, f18
  fsqrt.d f2, f18
  fsqrt.d f3, f19
  fsqrt.d f4, f19
  fsqrt.d f5, f19
  fdiv.d  f6, f18, f20
  fdiv.d  f7, f18, f20
  fdiv.d  f8, f18, f20
  fdiv.d  f9, f18, f20
  fdiv.d  f10, f19, f20
  fdiv.d  f11, f19, f20
  fsqrt.d f12, f19
  fsqrt.d f13, f19
  fsqrt.d f14, f19
  fsqrt.d f15, f19
  fsqrt.d f16, f19
  fsqrt.d f17, f19
  addi t0,t0,1
  bne  t0,a0, ini_loop
fin_loop:
  ret
