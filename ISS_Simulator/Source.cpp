
#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>
#include<string>

using namespace std;
unsigned int pc=0;
unsigned char memory[(16 + 64) * 1024] = { 65 };
unsigned int regMemory[32] = { 0 };

void emitError(string s)
{
	cout << s;
	exit(0);
}

void printPrefix(unsigned int instA, unsigned int instW) 
{
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
	int temp = regMemory[rs1] + offset;
	memory[temp] = regMemory[rs2];
	cout << "\n" << hex << (int)memory[temp] << "\n";
	cout << endl << (int)regMemory[rs2] << endl;

}

void sh(unsigned int rs1, unsigned int rs2, unsigned int offset)
{
	int temp = regMemory[rs1] + offset;
	memory[temp] =  regMemory[rs2];
	memory[temp + 1] = (regMemory[rs2] >> 8);
	cout << "\n" << hex << (int)memory[temp] <<(int)memory[temp+1]<< "\n";

}

void sw(unsigned int rs1, unsigned int rs2, unsigned int offset)
{
	int temp = regMemory[rs1] + offset;
	memory[temp] = regMemory[rs2];
	memory[temp+1] = (regMemory[rs2]>>8);
	memory[temp+2] = (regMemory[rs2]>>16);
	memory[temp+3] = (regMemory[rs2] >>24);
	cout << "\n" << hex << (int)memory[temp] << (int)memory[temp + 1]<< (int)memory[temp + 2] << (int)memory[temp + 3]<<"\n";

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
	S_imm = ((instWord >> 7) & 0x1F) | ((instWord >> 20) & 0xFE0) | (((instWord >> 31) ? 0xFFFFF000 : 0x0));
	B_imm = ((instWord >> 7) & 0x1F) | ((instWord >> 20) & 0xFE0) | (((instWord >> 31) ? 0xFFFFF000 : 0x0));
	B_imm=B_imm << 1;
	B_imm += 1;

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
				sub(rs1, rs2, rd);
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
			sll(rs1, rs2, rd);
			break;
		}

		case 2:
		{
			cout << "\tSLT\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			slt(rs1, rs2, rd);
			break;
		}

		case 3:
		{
			cout << "\tSLTU\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			sltu(rs1, rs2, rd);
			break;
		}

		case 4:
		{
			cout << "\tXOR\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			xorFn(rs1, rs2, rd);
			break;
		}

		case 5:
		{
			if (funct7 == 32)
			{
				cout << "\tSRA\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
				sra(rs1, rs2, rd);
			}
			else
			{
				cout << "\tSRL\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
				srl(rs1, rs2, rd);
			}
			break;
		}

		case 6:
		{
			cout << "\tOR\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			orFn(rs1, rs2, rd);
			break;
		}


		case 7:
		{
			cout << "\tAND\tx" << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			andFn(rs1, rs2, rd);
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
			cout << "\tSLLI\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			slli(rs1, rd, I_imm);

			break;
		}

		case 2:
		{
			cout << "\tSLTI\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			slti(rs1, rd, I_imm);

			break;
		}


		case 3:
		{
			cout << "\tSLTIU\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			sltiu(rs1, rd, I_imm);

			break;
		}

		case 4:
		{
			cout << "\tXORI\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			xori(rs1, rd, I_imm);

			break;
		}

		case 5:
		{
			if (funct7 == 32)
			{
				cout << "\tSRAI\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
				srai(rs1, rd, I_imm);

			}
			else
			{
				cout << "\tSRLI\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
				srli(rs1, rd, I_imm);

			}
			break;
		}

		case 6:
		{
			cout << "\tORI\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			ori(rs1, rd, I_imm);
			break;
		}
		case 7:
		{
			cout << "\tANDI\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			andi(rs1, rd, I_imm);
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
			cout << "\tSB\tx" << rs2 << "," << dec<<S_imm << "(x" << rs1 << ")" << "\n";
			sb(rs1, rs2, S_imm);
			break;
		}

		case 1:
		{
			cout << "\tSH\tx" << rs2 << "," << dec<<S_imm << "(x" << rs1 <<")"<< "\n";
			sh(rs1, rs2, S_imm);

			break;

		}

		case 2:
		{
			cout << "\tSW\tx" << rs2 << "," << dec << S_imm << "(x" << rs1 << ")" << "\n";
			sw(rs1, rs2, S_imm);
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
			beq(rs1, rs2, I_imm);
			break;
		}

		case 1:
		{
			cout << "\tBNE\tx" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)I_imm << "\n";
			bne(rs1, rs2, I_imm);
			break;

		}

		case 4:
		{
			cout << "\tBLT\tx" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)I_imm << "\n";
			blt(rs1, rs2, I_imm);
			break;
		}

		case 5:
		{
			cout << "\tBGE\tx" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)I_imm << "\n";
			bge(rs1, rs2, I_imm);
			break;
		}

		case 6:
		{
			cout << "\tBLTU\tx" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)I_imm << "\n";
			bltu(rs1, rs2, I_imm);
			break;
		}

		case 7:
		{
			cout << "\tBGEU\tx" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)I_imm << "\n";
			bgeu(rs1, rs2, I_imm);
			break;
		}


		}
	}
	else if (opcode == 0x37)   //LUI
	{
		cout << "\tLUI\tx" << rd << ", " << hex << "0x" << (int)I_imm << "\n";
		lui(rd, I_imm);

	}
	else if (opcode == 0x17)  //AUIPC
	{
		cout << "\tAUIBC\tx" << rd << ", " << hex << "0x" << (int)I_imm << "\n";
		auipc(rd, I_imm);


	}
	else if (opcode == 0x6F)   //   JAL
	{
		cout << "\tJAL\tx" << rd << ", " << hex << "0x" << (int)I_imm << "\n";
		jal(rd, I_imm);


	}
	else if (opcode == 0x67) // JALR
	{

		cout << "\tJALR\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
		jalr(rd, rs1, I_imm);

	}

	else if (opcode == 0x03) // load
	{

		switch (funct3)
		{
		case 0:
		{
			cout << "\tLB\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			lb(rs1, rd, I_imm);
			break;

		}

		case 1:
		{
			cout << "\tLH\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			lh(rs1, rd, I_imm);
			break;
		}

		case 2:
		{
			cout << "\tLW\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			lw(rs1, rd, I_imm);
			break;
		}


		case 4:
		{
			cout << "\tLBU\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			lbu(rs1, rd, I_imm);
			break;
		}

		case 5:
		{
			cout << "\tLHU\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			lhu(rs1, rd, I_imm);
			break;
		}

		default:
			cout << "\tUnkown I Instruction \n";
		}
	}


	else if (opcode == 0x73) // ecall
	{
		cout << "\tECALL\t\n";
		ecall();

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
			if (pc == 128) break;			// stop when PC reached address 32
			instDecExec(instWord);
		}
	}
	else emitError("Cannot access input file\n");

	cout << (int)memory[100] << (int)memory[101] << (int)memory[102] << (int)memory[103];


}
