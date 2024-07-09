.section .data
    msg1: .asciz "LUI Value: "
    msg2: .asciz "\nAUIPC Value: "
    msg3: .asciz "\nStored Value: "
    msg4: .asciz "\nLoaded Value: "

.section .bss
    .align 4
    .skip 4             # Reserve 4 bytes for testing load and store

.section .text
.global _start

_start:
    # Test LUI (Load Upper Immediate)
    lui t0, 0x12345     # Load upper immediate 0x12345000 into t0

    # Print LUI value
    la a0, msg1
    li a7, 4            # syscall number for print_string
    ecall
    mv a0, t0
    li a7, 1            # syscall number for print_integer
    ecall

    # Test AUIPC (Add Upper Immediate to PC)
    auipc t1, 0x12345   # t1 = PC + 0x12345000

    # Print AUIPC value
    la a0, msg2
    li a7, 4            # syscall number for print_string
    ecall
    mv a0, t1
    li a7, 1            # syscall number for print_integer
    ecall

    # Test store (SW) and load (LW) instructions
    la t2, 0x2000       # Load address of reserved memory into t2 (adjust address as needed)
    li t3, 12345        # Load value 12345 into t3
    sw t3, 0(t2)        # Store t3 into memory at address in t2

    # Print Stored value
    la a0, msg3
    li a7, 4            # syscall number for print_string
    ecall
    mv a0, t3
    li a7, 1            # syscall number for print_integer
    ecall

    # Load value from memory into t4
    lw t4, 0(t2)        # Load word from address in t2 into t4

    # Print Loaded value
    la a0, msg4
    li a7, 4            # syscall number for print_string
    ecall
    mv a0, t4
    li a7, 1            # syscall number for print_integer
    ecall

    # Exit the program
    li a7, 10           # syscall number for exit
    li a0, 0            # exit code 0
    ecall
