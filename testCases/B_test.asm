   .text
    .globl main

main:
li t0, 1000
li t1 2000
bne t1, t2, branchBNE
li a7, 1
li a0, -1
ecall
branchBNE:
li t1,1000
li t2,1000
bne t1,t2, branchBNE
beq t1,t1, branchEQ
li a7, 1
li a0, -1
ecall
branchEQ:
li t1,1000
li t2,2000
blt t1,t2, branchLT
li a7, 1
li a0, -1
ecall
branchLT:
li t1,1000
li t2,2000
blt t2,t1,branchLT
bge t2,t1, branchGTE
li a7, 1
li a0, -1
ecall
branchGTE:
li t1, -100
li t2, 100
bltu t2,t1, branchLTU
li a7, 1
li a0, -1
ecall
 branchLTU:
 bltu t1,t2, branchLTU
 bgeu t1,t2, branchGTEU
 li a7, 1
li a0, -1
ecall
 branchGTEU:
  li a7, 1
li a0, 1
ecall





 


