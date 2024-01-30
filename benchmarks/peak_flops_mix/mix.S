.global asm_basic_loop
asm_basic_loop:
  li t0, 0x4010000000000000
  li t1, 0x4000000000000000
  li t2, 0x4020000000000000
  fmv.d.x f18, t0
  fmv.d.x f19, t1
  fmv.d.x f20, t2
  xor t3, t3, t3
  blez a0, fin_loop
ini_loop:
  fsqrt.d f0, f18
  fadd.d f21, f21, f21
  fsqrt.d f1, f18
  fadd.d f22, f22, f22
  fsqrt.d f2, f18
  fadd.d f23, f23, f23
  fsqrt.d f3, f19
  fadd.d f24, f24, f24
  fsqrt.d f4, f19
  fadd.d f25, f25, f25
  fsqrt.d f5, f19
  fdiv.d  f6, f18, f20
  fsub.d f24, f24, f24
  fdiv.d  f7, f18, f20
  fsub.d f25, f25, f25
  fdiv.d  f8, f18, f20
  fsub.d f26, f26, f26
  fdiv.d  f9, f18, f20
  fsub.d f27, f27, f27
  fdiv.d  f10, f19, f20
  fsub.d f28, f28, f28
  fdiv.d  f11, f19, f20
  fsub.d f29, f29, f29
  addi t3,t3,1
  bne  t3,a0, ini_loop
fin_loop:
  ret