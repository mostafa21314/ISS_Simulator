This is a RISC-V simulator written in C++ for educational purposes. It simulates the execution of basic RISC-V instructions for the RV32I instruction set architecture.

Features:

Supports integer instructions (add, sub, sll, srl, sra, xor, slt, sltu, andi, ori)
Supports immediate instructions (addi, slli, srli, srai, xori, ori, andi)
Supports load and store instructions (lb, lh, lw, lbu, lhu, sb, sh, sw)
Supports branch instructions (beq, bne, blt, bge, bltu)
Supports system calls (ecall) for printing integers, reading characters, and exiting the program
Requirements:

The simulator will read the assembly file, execute the instructions, and print the results.


The simulator supports the RV32I instruction set architecture. You can find the detailed instruction specification for RV32I online https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf.

Understanding the Output:

The simulator will output the following information:

Program Counter (PC): The address of the currently executing instruction.
Disassembled Instruction: The assembly code representation of the instruction being executed.
Memory Address: The memory address being accessed by load or store instructions (if applicable).
Register Values: The current values of the general-purpose registers (x0-x31).
Additional Information: Depending on the system call used (ecall), the simulator might print additional information like the value being printed or a character being read.
Challenges Faced:

During development, we encountered a few challenges:

Instruction Decoding: Accurately decoding different RISC-V instruction formats (R, I, S, J) proved to be a hurdle. We had to carefully analyze the instruction bitfields to determine the operation and operands.
Memory Management: Simulating memory access without interacting with actual hardware required careful design to ensure proper handling of memory addresses and data types.
Error Handling: Implementing robust error handling for invalid instructions or memory access exceptions was crucial to prevent unexpected behavior.
