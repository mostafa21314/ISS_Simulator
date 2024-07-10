   .text
    .globl main

main:
addi t0, x0, 2
addi t1, t0, -382
xori t2, t1, 0xFF
ori  t3, t1, 0xFF
andi t4, t1, 0xFF
slli t2, t1, 2
srli t2, t1, 2
srai t2, t2, 2
slti t2, t1, 0
sltiu  t2, t1, 0

addi x1, x0, 1
addi x2, x0, 2
addi x3, x0, 3
addi x4, x0, 4
addi x5, x0, 5
addi x6, x0, 6
addi x12, x0, -12

add x7, x1, x6
sub x8, x1, x6
xor x9 x2,x4
or x10 x3,x5
and x11 x6, x4
sll x7, x6, x2
srl x7, x12, x1
sra  x7, x12, x1
slt x7, x12, x6
slt x7, x6, x12
sltu x7, x12,x6
 


