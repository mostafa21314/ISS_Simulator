This is a RISC-V simulator written in C++ for educational purposes. It simulates the execution of basic RISC-V instructions for the RV32I instruction set architecture. It was created by AUC comp engineering students Mostafa Gaafar, and Youssef Badawy alongsie electronics engineering student Youssef Abbas.

Features:

Supports integer instructions (add, sub, sll, srl, sra, xor, slt, sltu, andi, ori)
Supports immediate instructions (addi, slli, srli, srai, xori, ori, andi)
Supports load and store instructions (lb, lh, lw, lbu, lhu, sb, sh, sw)
Supports branch instructions (beq, bne, blt, bge, bltu)
Supports system calls (ecall) for printing integers, reading characters, and exiting the program
Requirements:

The simulator will read the assembly file, execute the instructions, and print the results.


IMPORTANT: To use the simulator you have to input the data and text binary files in binary format as well as input the location where .data sections starts to store in the memory to ensure the program runs smoothly.


Understanding the Output:

The simulator will output the following information:

Program Counter (PC): The address of the currently executing instruction.
Disassembled Instruction: The assembly code representation of the instruction being executed.
Memory Address: The memory address being accessed by load or store instructions (if applicable).
Register Values: The current values of the general-purpose registers (x0-x31).
Additional Information: Depending on the system call used (ecall), the simulator might print additional information like the value being printed or a character being read.
Challenges Faced:

During development, we encountered a few challenges:

Firstly alligning memory storage with .data proved to be a challenge as it required tuning load instructions as well as save instructions
Secondly, Compressed instructions had there immediates scattered around and needed a lot of bitwise operation and careful observation
Furthermore, figuring out how to assemble words as little endian format for both saves and loads so they work concurrently without producing errors.
