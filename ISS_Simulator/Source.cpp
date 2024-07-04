/*
	This is just a skeleton. It DOES NOT implement all the requirements.
	It only recognizes the RV32I "ADD", "SUB" and "ADDI" instructions only.
	It prints "Unkown Instruction" for all other instructions!

	References:
	(1) The risc-v ISA Manual ver. 2.1 @ https://riscv.org/specifications/
	(2) https://github.com/michaeljclark/riscv-meta/blob/master/meta/opcodes
*/

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

	cout << "\n" <<hex<< regMemory[rd]<<"\n";
}
void addi(unsigned int rs1, unsigned int rd, unsigned int immediate)
{
	regMemory[rd] = regMemory[rs1] + immediate;
	cout << "\n" << hex<<regMemory[rd] << "\n";
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