
#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>
#include<string>

using namespace std;
unsigned int pc;
unsigned char memory[(16 + 64) * 1024];
unsigned int regMemory[32];

void emitError(string s)
{
	cout << s;
	exit(0);
}

void printPrefix(unsigned int instA, unsigned int instW) {
	cout << "0x" << hex << std::setfill('0') << std::setw(8) << instA << "\t0x" << std::setw(8) << instW;
}



void add(unsigned int rs1, unsigned int rs2, unsigned int rd)
{
	regMemory[rd] = regMemory[rs1] + regMemory[rs2];
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void sub(unsigned int rs1, unsigned int rs2, unsigned int rd)
{
	regMemory[rd] = regMemory[rs1] - regMemory[rs2];
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void sll(unsigned int rs1, unsigned int rs2, unsigned int rd)
{
	regMemory[rd] = regMemory[rs1] << (regMemory[rs2] & 0x1F);
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void slt(unsigned int rs1, unsigned int rs2, unsigned int rd)
{
	regMemory[rd] = (static_cast<int>(regMemory[rs1]) < static_cast<int>(regMemory[rs2])) ? 1 : 0;
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void sltu(unsigned int rs1, unsigned int rs2, unsigned int rd)
{
	regMemory[rd] = (regMemory[rs1] < regMemory[rs2]) ? 1 : 0;
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void xorFn(unsigned int rs1, unsigned int rs2, unsigned int rd)
{
	regMemory[rd] = regMemory[rs1] ^ regMemory[rs2];
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void srl(unsigned int rs1, unsigned int rs2, unsigned int rd)
{
	regMemory[rd] = regMemory[rs1] >> (regMemory[rs2] & 0x1F);
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void sra(unsigned int rs1, unsigned int rs2, unsigned int rd)
{
	regMemory[rd] = static_cast<int>(regMemory[rs1]) >> (regMemory[rs2] & 0x1F);
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void orFn(unsigned int rs1, unsigned int rs2, unsigned int rd)
{
	regMemory[rd] = regMemory[rs1] | regMemory[rs2];
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void andFn(unsigned int rs1, unsigned int rs2, unsigned int rd)
{
	regMemory[rd] = regMemory[rs1] & regMemory[rs2];
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void addi(unsigned int rs1, unsigned int rd, unsigned int immediate)
{
	regMemory[rd] = regMemory[rs1] + immediate;
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void slli(unsigned int rs1, unsigned int rd, unsigned int shamt)
{
	regMemory[rd] = regMemory[rs1] << (shamt & 0x1F);
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void slti(unsigned int rs1, unsigned int rd, unsigned int immediate)
{
	regMemory[rd] = (static_cast<int>(regMemory[rs1]) < static_cast<int>(immediate)) ? 1 : 0;
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void sltiu(unsigned int rs1, unsigned int rd, unsigned int immediate)
{
	regMemory[rd] = (regMemory[rs1] < immediate) ? 1 : 0;
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void xori(unsigned int rs1, unsigned int rd, unsigned int immediate)
{
	regMemory[rd] = regMemory[rs1] ^ immediate;
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void srli(unsigned int rs1, unsigned int rd, unsigned int shamt)
{
	regMemory[rd] = regMemory[rs1] >> (shamt & 0x1F);
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void srai(unsigned int rs1, unsigned int rd, unsigned int shamt)
{
	regMemory[rd] = static_cast<int>(regMemory[rs1]) >> (shamt & 0x1F);
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void ori(unsigned int rs1, unsigned int rd, unsigned int immediate)
{
	regMemory[rd] = regMemory[rs1] | immediate;
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void andi(unsigned int rs1, unsigned int rd, unsigned int immediate)
{
	regMemory[rd] = regMemory[rs1] & immediate;
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void sb(unsigned int rs1, unsigned int rs2, unsigned int offset)
{
	memory[regMemory[rs1] + offset] = regMemory[rs2] & 0xFF;
	cout << "\n" << hex << memory[regMemory[rs1] + offset] << "\n";
}

void sh(unsigned int rs1, unsigned int rs2, unsigned int offset)
{
	memory[regMemory[rs1] + offset] = regMemory[rs2] & 0xFFFF;
	cout << "\n" << hex << memory[regMemory[rs1] + offset] << "\n";
}

void sw(unsigned int rs1, unsigned int rs2, unsigned int offset)
{
	memory[regMemory[rs1] + offset] = regMemory[rs2];
	cout << "\n" << hex << memory[regMemory[rs1] + offset] << "\n";
}

void beq(unsigned int rs1, unsigned int rs2, unsigned int offset)
{
	if (regMemory[rs1] == regMemory[rs2])
	{
		pc += offset;
	}
}

void bne(unsigned int rs1, unsigned int rs2, unsigned int offset)
{
	if (regMemory[rs1] != regMemory[rs2])
	{
		pc += offset;
	}
}

void blt(unsigned int rs1, unsigned int rs2, unsigned int offset)
{
	if (static_cast<int>(regMemory[rs1]) < static_cast<int>(regMemory[rs2]))
	{
		pc += offset;
	}
}

void bge(unsigned int rs1, unsigned int rs2, unsigned int offset)
{
	if (static_cast<int>(regMemory[rs1]) >= static_cast<int>(regMemory[rs2]))
	{
		pc += offset;
	}
}

void bltu(unsigned int rs1, unsigned int rs2, unsigned int offset)
{
	if (regMemory[rs1] < regMemory[rs2])
	{
		pc += offset;
	}
}

void bgeu(unsigned int rs1, unsigned int rs2, unsigned int offset)
{
	if (regMemory[rs1] >= regMemory[rs2])
	{
		pc += offset;
	}
}

void lui(unsigned int rd, unsigned int immediate)
{
	regMemory[rd] = immediate << 12;
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void auipc(unsigned int rd, unsigned int immediate)
{
	regMemory[rd] = pc + (immediate << 12);
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void jal(unsigned int rd, unsigned int immediate)
{
	regMemory[rd] = pc + 4;
	pc += immediate;
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void jalr(unsigned int rd, unsigned int rs1, unsigned int immediate)
{
	regMemory[rd] = pc + 4;
	pc = (regMemory[rs1] + immediate) & ~1;
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void lb(unsigned int rs1, unsigned int rd, unsigned int offset)
{
	int address = regMemory[rs1] + offset;
	regMemory[rd] = static_cast<int>(memory[address]);
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void lh(unsigned int rs1, unsigned int rd, unsigned int offset)
{
	int address = regMemory[rs1] + offset;
	regMemory[rd] = static_cast<int>(memory[address] | (memory[address + 1] << 8));
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void lw(unsigned int rs1, unsigned int rd, unsigned int offset)
{
	int address = regMemory[rs1] + offset;
	regMemory[rd] = static_cast<int>(memory[address] | (memory[address + 1] << 8) | (memory[address + 2] << 16) | (memory[address + 3] << 24));
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void lbu(unsigned int rs1, unsigned int rd, unsigned int offset)
{
	int address = regMemory[rs1] + offset;
	regMemory[rd] = memory[address];
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void lhu(unsigned int rs1, unsigned int rd, unsigned int offset)
{
	int address = regMemory[rs1] + offset;
	regMemory[rd] = memory[address] | (memory[address + 1] << 8);
	cout << "\n" << hex << regMemory[rd] << "\n";
}

void ecall()
{
	cout << "\n" << hex << "0x" << regMemory[17] << "\n";

}
void instDecExec(unsigned int instWord)
{
	unsigned int rd, rs1, rs2, funct3, funct7, opcode;
	unsigned int I_imm, S_imm, B_imm, U_imm, J_imm;
	unsigned int address;

	unsigned int instPC = pc - 4;

	opcode = instWord & 0x0000007F;
	rd = (instWord >> 7) & 0x0000001F;
	funct3 = (instWord >> 12) & 0x00000007;
	rs1 = (instWord >> 15) & 0x0000001F;
	rs2 = (instWord >> 20) & 0x0000001F;
	funct7 = (instWord >> 25) & 0x0000007F;

	// — inst[31] — inst[30:25] inst[24:21] inst[20]
	I_imm = ((instWord >> 20) & 0x7FF) | (((instWord >> 31) ? 0xFFFFF800 : 0x0));

	printPrefix(instPC, instWord);

	if (opcode == 0x33)    	// R Instructions
	{
		switch (funct3)
		{
		case 0:
		{
			if (funct7 == 32)
			{
				cout << "\tSUB\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			}
			else
			{
				cout << "\tADD\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
				add(rs1, rs2, rd);
			}
			break;
		}

		case 1:
		{
			cout << "\tSLL\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			break;
		}

		case 2:
		{
			cout << "\tSLT\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			break;
		}

		case 3:
		{
			cout << "\tSLTU\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			break;
		}

		case 4:
		{
			cout << "\tXOR\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			break;
		}

		case 5:
		{
			if (funct7 == 32)
			{
				cout << "\tSRA\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			}
			else
			{
				cout << "\tSRL\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			}
			break;
		}

		case 6:
		{
			cout << "\tOR\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			break;
		}


		case 7:
		{
			cout << "\tAND\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			break;
		}

		default:
			cout << "\tUnkown R Instruction \n";
		}
	}
	else if (opcode == 0x13)   // I instructions
	{
		switch (funct3)

		{
		case 0:
		{
			cout << "\tADDI\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			addi(rs1, rd, I_imm);
			break;
		}

		case 1:
		{
			cout << "\tSLLI\tx" << rd << ", x" << rs1 << "\n";
			break;
		}

		case 2:
		{
			cout << "\tSLTI\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;
		}


		case 3:
		{
			cout << "\tSLTIU\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;
		}

		case 4:
		{
			cout << "\tXORI\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;
		}

		case 5:
		{
			if (funct7 == 32)
			{
				cout << "\tSRAI\tx" << rd << ", x" << rs1 << "\n";
			}
			else
			{
				cout << "\tSRLI\tx" << rd << ", x" << rs1 << "\n";
			}
			break;
		}

		case 6:
		{
			cout << "\tORI\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;
		}
		case 7:
		{
			cout << "\tANDI\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;
		}
		default:
			cout << "\tUnkown I Instruction \n";
		}
	}
	else if (opcode == 0x23)  // S innstruction
	{
		switch (funct3)
		{
		case 0:
		{
			cout << "\tSB\tx" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;
		}

		case 1:
		{
			cout << "\tSH\tx" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;

		}

		case 2:
		{
			cout << "\tSW\tx" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;
		}
		}


	}
	else if (opcode == 0x63)  // B instruction
	{
		switch (funct3)
		{
		case 0:
		{
			cout << "\tBEQ\tx" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;
		}

		case 1:
		{
			cout << "\tBNE\tx" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;

		}

		case 4:
		{
			cout << "\tBLT\tx" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;
		}

		case 5:
		{
			cout << "\tBGE\tx" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;
		}

		case 6:
		{
			cout << "\tBLTU\tx" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;
		}

		case 7:
		{
			cout << "\tBGEU\tx" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;
		}


		}
	}
	else if (opcode == 0x37)   //LUI
	{
		cout << "\tLUI\tx" << rd << ", " << hex << "0x" << (int)I_imm << "\n";

	}
	else if (opcode == 0x17)  //AUIPC
	{
		cout << "\tAUIBC\tx" << rd << ", " << hex << "0x" << (int)I_imm << "\n";


	}
	else if (opcode == 0x6F)   //   JAL
	{
		cout << "\tJAL\tx" << rd << ", " << hex << "0x" << (int)I_imm << "\n";


	}
	else if (opcode == 0x67) // JALR
	{

		cout << "\tJALR\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";

	}

	else if (opcode == 0x03) // load
	{

		switch (funct3)
		{
		case 0:
		{
			cout << "\tLB\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;

		}

		case 1:
		{
			cout << "\tLH\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;
		}

		case 2:
		{
			cout << "\tLU\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;
		}


		case 4:
		{
			cout << "\tLBU\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;
		}

		case 5:
		{
			cout << "\tLHU\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;
		}

		default:
			cout << "\tUnkown I Instruction \n";
		}
	}


	else if (opcode == 0x73) // ecall
	{
		cout << "\tECALL\t\n";

	}
	else
	{
		cout << "\tUnkown Instruction \n";
	}

}



int main()
{

	int argc = 2;
	unsigned int instWord = 0;
	ifstream inFile;
	ofstream outFile;

	if (argc < 1) emitError("use: rvcdiss <machine_code_file_name>\n");

	inFile.open("C:/Users/mosta/Desktop/badawy.bin", ios::in | ios::binary | ios::ate);

	if (inFile.is_open())
	{
		int fsize = inFile.tellg();

		inFile.seekg(0, inFile.beg);
		if (!inFile.read((char*)memory, fsize)) emitError("Cannot read from input file\n");

		while (true) {
			instWord = (unsigned char)memory[pc] |
				(((unsigned char)memory[pc + 1]) << 8) |
				(((unsigned char)memory[pc + 2]) << 16) |
				(((unsigned char)memory[pc + 3]) << 24);
			pc += 4;
			// remove the following line once you have a complete simulator
			if (pc == 32) break;			// stop when PC reached address 32
			instDecExec(instWord);
		}
	}
	else emitError("Cannot access input file\n");
}
