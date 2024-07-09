
.global _main
_main:
 
jal ra, jaltest
li a0,-1
li a7,1
ecall
li a7,10
ecall

jaltest:
li t0,1
li t0,1
li t0,1
li t0,1
li t0,1
li a0,2
li a7,1
ecall
jalr x0, 0(ra)


