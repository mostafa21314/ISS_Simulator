#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>
#include<string>
#include <cstdint>

using namespace std;
unsigned int pc = 0;
unsigned char memory[(16 * 64) * 1024] = { 65 };
unsigned int regMemory[32] = { 0 };


void printRegisters()
{
	cout << endl;
	for (int i = 0; i < 32; i++)
	{
		if (regMemory[i] != 0)
			cout << dec << "x" << i << "  =  " << regMemory[i] << "        ";
	}
	cout << endl;
}



void emitError(string s)
{
	cout << s;
	exit(0);
}

void printPrefix(unsigned int instA, unsigned int instW)
{
	cout << "0x" << hex << std::setfill('0') << std::setw(8) << instA << "\t0x" << std::setw(8) << instW;
}



void add(unsigned int rs1, unsigned int rs2, unsigned int rd, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = regMemory[rs1] + regMemory[rs2];
	//cout << "\n" << hex << regMemory[rd] << "\n";
}

void sub(unsigned int rs1, unsigned int rs2, unsigned int rd, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = regMemory[rs1] - regMemory[rs2];
	//	cout << "\n" << hex << regMemory[rd] << "\n";
}

void sll(unsigned int rs1, unsigned int rs2, unsigned int rd, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = regMemory[rs1] << (regMemory[rs2] & 0x1F);
	//	cout << "\n" << hex << regMemory[rd] << "\n";
}

void slt(unsigned int rs1, unsigned int rs2, unsigned int rd, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = (static_cast<int>(regMemory[rs1]) < static_cast<int>(regMemory[rs2])) ? 1 : 0;
	//	cout << "\n" << hex << regMemory[rd] << "\n";
}

void sltu(unsigned int rs1, unsigned int rs2, unsigned int rd, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = (regMemory[rs1] < regMemory[rs2]) ? 1 : 0;
	//cout << "\n" << hex << regMemory[rd] << "\n";
}

void xorFn(unsigned int rs1, unsigned int rs2, unsigned int rd, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = regMemory[rs1] ^ regMemory[rs2];
	//cout << "\n" << hex << regMemory[rd] << "\n";
}

void srl(unsigned int rs1, unsigned int rs2, unsigned int rd, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = regMemory[rs1] >> (regMemory[rs2] & 0x1F);
	//cout << "\n" << hex << regMemory[rd] << "\n";
}

void sra(unsigned int rs1, unsigned int rs2, unsigned int rd, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = static_cast<int>(regMemory[rs1]) >> (regMemory[rs2] & 0x1F);
	//cout << "\n" << hex << regMemory[rd] << "\n";
}

void orFn(unsigned int rs1, unsigned int rs2, unsigned int rd, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = regMemory[rs1] | regMemory[rs2];
	//	cout << "\n" << hex << regMemory[rd] << "\n";
}

void andFn(unsigned int rs1, unsigned int rs2, unsigned int rd, bool compressed)
{
	regMemory[rd] = regMemory[rs1] & regMemory[rs2];
	//cout << "\n" << hex << regMemory[rd] << "\n";
}

void addi(unsigned int rs1, unsigned int rd, unsigned int immediate, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = regMemory[rs1] + (int)immediate;
	//	cout << "\n" << hex << regMemory[rd] << "\n";
}

void slli(unsigned int rs1, unsigned int rd, unsigned int shamt, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = regMemory[rs1] << (shamt & 0x1F);
	//cout << "\n" << hex << regMemory[rd] << "\n";
}

void slti(unsigned int rs1, unsigned int rd, unsigned int immediate, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = (static_cast<int>(regMemory[rs1]) < static_cast<int>(immediate)) ? 1 : 0;
	//cout << "\n" << hex << regMemory[rd] << "\n";
}

void sltiu(unsigned int rs1, unsigned int rd, unsigned int immediate, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = (regMemory[rs1] < immediate) ? 1 : 0;
	//cout << "\n" << hex << regMemory[rd] << "\n";
}

void xori(unsigned int rs1, unsigned int rd, unsigned int immediate, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = regMemory[rs1] ^ immediate;
	//	cout << "\n" << hex << regMemory[rd] << "\n";
}

void srli(unsigned int rs1, unsigned int rd, unsigned int shamt, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = regMemory[rs1] >> (shamt & 0x1F);
	//cout << "\n" << hex << regMemory[rd] << "\n";
}

void srai(unsigned int rs1, unsigned int rd, unsigned int shamt, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = static_cast<int>(regMemory[rs1]) >> (shamt & 0x1F);
	//cout << "\n" << hex << regMemory[rd] << "\n";
}

void ori(unsigned int rs1, unsigned int rd, unsigned int immediate, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = regMemory[rs1] | immediate;
	//cout << "\n" << hex << regMemory[rd] << "\n";
}

void andi(unsigned int rs1, unsigned int rd, unsigned int immediate, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = regMemory[rs1] & immediate;
	//	cout << "\n" << hex << regMemory[rd] << "\n";
}

void sb(unsigned int rs1, unsigned int rs2, unsigned int offset, bool compressed)
{

	int temp = regMemory[rs1] + offset;


	memory[temp] = regMemory[rs2];

	//cout << endl << temp <<"    "<< (int)memory[temp] << endl;

//	cout << endl << hex << temp << "    " << memory[temp] << endl;
	//cout << "\n" << hex << (int)memory[temp] << "\n";
	//cout << endl << (int)regMemory[rs2] << endl;

}

void sh(unsigned int rs1, unsigned int rs2, unsigned int offset, bool compressed)
{
	int temp = regMemory[rs1] + offset;



	memory[temp] = regMemory[rs2];
	memory[temp + 1] = (regMemory[rs2] >> 8);


	//cout << endl << temp << "    " << (int)memory[temp] << endl;

	/*cout << endl << hex << temp <<"    "<<memory[temp]<< endl;
	cout << endl << hex << temp+1 << "    " << memory[temp+1] << endl;*/


	//	cout << "\n" << hex << (int)memory[temp] <<(int)memory[temp+1]<< "\n";

}

void sw(unsigned int rs1, unsigned int rs2, unsigned int offset, bool compressed)
{


	int temp = regMemory[rs1] + offset;


	memory[temp] = regMemory[rs2];
	memory[temp + 1] = (regMemory[rs2] >> 8);
	memory[temp + 2] = (regMemory[rs2] >> 16);
	memory[temp + 3] = (regMemory[rs2] >> 24);

	//cout << endl << temp << "    " << (int)memory[temp] << endl;


	/*cout << endl << hex << temp << "    " << memory[temp] << endl;
	cout << endl << hex << temp +1<< "    " << memory[temp+1] << endl;
	cout << endl << hex << temp +2<< "    " << memory[temp+2] << endl;
	cout << endl << hex << temp +3<< "    " << memory[temp+3] << endl;*/

	//cout << "\n" << hex << (int)memory[temp] << (int)memory[temp + 1]<< (int)memory[temp + 2] << (int)memory[temp + 3]<<"\n";

}

void beq(unsigned int rs1, unsigned int rs2, unsigned int offset, bool compressed)
{

	//cout << endl << endl << regMemory[rs1] << "   " << regMemory[rs2] << endl << endl << endl;
	if (regMemory[rs1] == regMemory[rs2])
	{
		pc += offset - 4;
	}
}

void bne(unsigned int rs1, unsigned int rs2, unsigned int offset, bool compressed)
{

	int x = static_cast<int>(offset);
	if (!compressed)
	{
		if (regMemory[rs1] != regMemory[rs2])
		{
			pc += x - 4;
		}
	}
	else
	{
		if (regMemory[rs1] != regMemory[rs2])
		{
			pc += x - 2;
		}
	}
	//cout << endl << hex << pc << endl;
	//cout << endl << regMemory[rs1] << "  " << regMemory[rs2] << endl;
}

void blt(unsigned int rs1, unsigned int rs2, unsigned int offset, bool compressed)
{
	if (static_cast<int>(regMemory[rs1]) < static_cast<int>(regMemory[rs2]))
	{
		pc += offset - 4;
	}
}

void bge(unsigned int rs1, unsigned int rs2, unsigned int offset, bool compressed)
{
	if (static_cast<int>(regMemory[rs1]) >= static_cast<int>(regMemory[rs2]))
	{
		pc += offset - 4;
	}
}

void bltu(unsigned int rs1, unsigned int rs2, unsigned int offset, bool compressed)
{
	if (regMemory[rs1] < regMemory[rs2])
	{
		pc += offset - 4;
	}
}

void bgeu(unsigned int rs1, unsigned int rs2, unsigned int offset, bool compressed)
{
	if (regMemory[rs1] >= regMemory[rs2])
	{
		pc += offset - 4;
	}
}

void lui(unsigned int rd, unsigned int immediate, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = immediate;
	//cout << "\n" << hex << regMemory[rd] << "\n";
}

void auipc(unsigned int rd, unsigned int immediate, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = pc + immediate - 4;
	//cout << "\n" << hex << regMemory[rd] << "\n";
}

void jal(unsigned int rd, unsigned int immediate, bool compressed)
{

	if (!compressed)
	{
		if (rd != 0)
			regMemory[rd] = pc;
		pc += immediate - 4;
	}
	else
	{
		if (rd != 0)
			regMemory[rd] = pc;
		pc += immediate - 2;
	}

}

void jalr(unsigned int rd, unsigned int rs1, unsigned int immediate, bool compressed)
{
	if (rd != 0)
		regMemory[rd] = pc;

	pc = (regMemory[rs1] + immediate) & ~1;
	//cout << "\n" << hex << regMemory[rd] << "\n";
}

void lb(unsigned int rs1, unsigned int rd, unsigned int offset, bool compressed)
{
	int address = regMemory[rs1] + offset;
	if (rd != 0)
	{
		regMemory[rd] = static_cast<int>(memory[address]);
		if (memory[address] & 0x80)
			regMemory[rd] = regMemory[rd] | 0xFFFFFF00;
		else
			regMemory[rd] = regMemory[rd] & 0x000000FF;
	}
	/*cout << "\n" << (char)regMemory[rd] <<(char)memory[address] <<"+0\n";
	cout << "\n"  << (char)memory[address+1] << "+1\n";
	cout << "\n" << (char)memory[address-1] << "-1\n";
	cout << "\n" << (char)memory[address+2] << "+2\n";
	cout << "\n"  << (char)memory[address -2] << "-2\n";*/

	//cout << "\n" << (char)regMemory[rd] << "\n";



}

void lh(unsigned int rs1, unsigned int rd, unsigned int offset, bool compressed)
{
	int address = regMemory[rs1] + offset;
	if (rd != 0)
	{
		regMemory[rd] = static_cast<int>(memory[address] | (memory[address + 1] << 8));
		if (memory[address + 1] & 0x80)
			regMemory[rd] = regMemory[rd] | 0xFFFF0000;
		else
			regMemory[rd] = regMemory[rd] & 0x0000FFFF;
	}
	//cout << "\n" << hex << (char)regMemory[rd] << (char)(regMemory[rd] >> 8) << "\n";
}

void lw(unsigned int rs1, unsigned int rd, unsigned int offset, bool compressed)
{

	int address = regMemory[rs1] + offset;

	//cout << endl << address << endl;
	//cout << endl << (int)memory[address] << endl;
	if (rd != 0)
		regMemory[rd] = static_cast<int>(memory[address] | (memory[address + 1] << 8)) | (memory[address + 2] << 16) | (memory[address + 3] << 24);

	//cout << "\n" << hex << (char)regMemory[rd] << (char)(regMemory[rd] >> 8) << (char)(regMemory[rd] >> 16) << (char)(regMemory[rd] >> 24) << "\n";
}

void lbu(unsigned int rs1, unsigned int rd, unsigned int offset, bool compressed)
{
	//printRegisters();

	int address = regMemory[rs1] + offset;
	if (rd != 0)
	{
		regMemory[rd] = (memory[address]);
		regMemory[rd] = regMemory[rd] & 0x000000FF;
	}
	//cout << "\n" << (char)regMemory[rd] << "\n";
	//printRegisters();

}

void lhu(unsigned int rs1, unsigned int rd, unsigned int offset, bool compressed)
{
	int address = regMemory[rs1] + offset;
	if (rd != 0)
	{
		regMemory[rd] = static_cast<int>(memory[address] | (memory[address + 1] << 8));
		regMemory[rd] = regMemory[rd] & 0x0000FFFF;
	}
	//cout << "\n" << hex << (int)regMemory[rd] << (char)(regMemory[rd] >> 8) << "\n";
}

void ecall()
{
	//cout <<"a0 "<< regMemory[10] << " a1: " << regMemory[11] <<" a7: "<< regMemory[17];
	switch (regMemory[17])
	{
	case 1:
	{
		cout << endl << dec << (int)regMemory[10] << endl;
		break;
	}
	case 4:
	{
		int i = 0;
		while (memory[regMemory[10] + i] != NULL)
			cout << memory[regMemory[10] + i++];
		cout << endl;
		break;
	}
	case 5:
	{
		cin >> regMemory[10];
		break;
	}
	case 8:
	{
		int i = regMemory[11];
		int j = 0;
		string s;
		getline(cin, s);
		while (i != 0)
		{
			if (j >= s.size())
				return;
			memory[regMemory[10] + j] = s.at(j++);
			i--;
		}
		break;
	}

	case 10:
	{
		exit(0);
		break;
	}

	case 11:
	{
		cout << (char)regMemory[10];
		break;
	}
	case 12:
	{
		char h;
		cin >> h;
		regMemory[10] = h;
		break;
	}

	case 93:
	{
		exit(regMemory[10]);
		break;
	}

	default:
	{
		cout << regMemory[17] << endl;
		exit(0);
	}
	}

	//cout << "\n" << hex << "0x" << regMemory[17] << "\n";

}


void decompress(unsigned int comp_instWord)
{

	unsigned int instPC = pc - 2;
	printPrefix(instPC, comp_instWord);



	unsigned int opcode = comp_instWord & 0x3;
	unsigned int funct3 = comp_instWord >> 13;
	unsigned int rd, rs1, rs2, imm;


	switch (opcode)
	{
	case 0b00: // Quadrant 0
	{

		switch (funct3)
		{

		case 0b000: // c.addi4spn
		{
			rd = ((comp_instWord >> 2) & 0x7) + 8;

			unsigned int imm3 = comp_instWord >> 5 & 0x1;
			imm3 <<= 3;
			unsigned int imm2 = comp_instWord >> 6 & 0x1;
			imm2 <<= 2;
			unsigned int imm6 = comp_instWord >> 7 & 0x1;
			imm6 <<= 6;
			unsigned int imm7 = comp_instWord >> 8 & 0x1;
			imm7 <<= 7;
			unsigned int imm8 = comp_instWord >> 9 & 0x1;
			imm8 <<= 8;
			unsigned int imm9 = comp_instWord >> 10 & 0x1;
			imm9 <<= 9;
			unsigned int imm4 = comp_instWord >> 11 & 0x1;
			imm4 <<= 4;
			unsigned int imm5 = comp_instWord >> 12 & 0x1;
			imm5 <<= 5;


			imm = 0x0 | imm2 | imm3 | imm4 | imm5 | imm6 | imm7 | imm8 | imm9;
			if (imm9 != 0) imm |= 0xFFFFFC00;
			cout << "\tc.addi4spn  x" << rd << ", sp, " << dec << (int)imm << "\n";
			addi(2, rd, imm, 1);
			//printRegisters();
			return;
			break;
		}


		case 0b010: // c.lw
		{
			rd = ((comp_instWord >> 2) & 0x7) + 8;
			rs1 = ((comp_instWord >> 7) & 0x7) + 8;
			unsigned int imm = 0;

			unsigned int imm6 = comp_instWord >> 5 & 0x1;
			unsigned int imm2 = comp_instWord >> 6 & 0x1;
			unsigned int imm3_5 = comp_instWord >> 10 & 0x7;
			bool neg = imm6;
			imm6 <<= 6;
			imm2 <<= 2;
			imm3_5 <<= 3;
			imm = 0x0 | imm2 | imm3_5 | imm6;
			if (neg) imm |= 0xFFFFFFE0;
			cout << "\tc.lw\tx" << (int)rd << ", " << (int)imm << "(x" << (int)rs1 << ")" << "\n";
			lw(rs1, rd, imm, 1);
			return;
			break;
		}


		case 0b110: // c.sw
		{
			rs2 = ((comp_instWord >> 2) & 0x7) + 8;
			rs1 = ((comp_instWord >> 7) & 0x7) + 8;

			unsigned int imm6 = comp_instWord >> 5 & 0x1;
			unsigned int imm2 = comp_instWord >> 6 & 0x1;
			unsigned int imm3_5 = comp_instWord >> 10 & 0x7;
			bool neg = imm6;
			imm6 <<= 6;
			imm2 <<= 2;
			imm3_5 <<= 3;
			imm = 0x0 | imm2 | imm3_5 | imm6;
			if (neg) imm |= 0xFFFFFFE0;
			cout << "\tc.sw\tx" << rs2 << ", " << imm << "(x" << rs1 << ")\n";
			sw(rs1, rs2, imm, 1);
			return;
			break;
		}

		}
		break;
	}

	case 0b01: // Quadrant 1
	{
		switch (funct3)
		{


		case 0b000: // c.addi
		{
			unsigned int imm = 0;
			rd = (comp_instWord >> 7) & 0x1F;
			imm = (comp_instWord >> 2) & 0x1F;
			unsigned int imm5 = comp_instWord >> 12 & 0x1;
			imm5 <<= 5;
			imm |= imm5;
			if (imm5 != 0) imm |= 0xFFFFFFC0; // Sign extension
			if (rd == 0 && imm == 0)
			{
				cout << "\tc.nop\tx" << "\n";
				addi(0, 0, 0, 1);    //nop
				return;
			}
			else
				cout << "\tc.addi\tx" << dec << (int)rd << ", " << (int)imm << "(x" << (int)rd << ")\n";
			addi(rd, rd, imm, 1);
			return;
			break;
		}


		case 0b001: // c.jal
		{
			rd = 1; // x1 is the link register
			unsigned int imm = 0;
			unsigned imm5 = comp_instWord >> 2 & 0x1;
			unsigned int imm1_3 = (comp_instWord >> 3) & 0x7;
			unsigned int imm7 = comp_instWord >> 6 & 0x1;
			unsigned int imm6 = comp_instWord >> 7 & 0x1;
			unsigned int imm10 = comp_instWord >> 8 & 0x1;
			unsigned int imm8_9 = comp_instWord >> 9 & 0x3;
			unsigned int imm4 = comp_instWord >> 11 & 0x1;
			unsigned int imm11 = comp_instWord >> 12 & 0x1;
			imm5 <<= 5;
			imm1_3 <<= 1;
			imm7 <<= 7;
			imm6 <<= 6;
			imm10 <<= 10;
			imm8_9 <<= 8;
			imm4 <<= 4;
			imm11 <<= 11;
			imm = 0 | imm1_3 | imm5 | imm4 | imm6 | imm7 | imm8_9 | imm10 | imm11;
			if (imm11 != 0)
			{
				imm |= 0xFFFFF000;
			}
			cout << "\tc.jal\t  0x" << hex << (instPC + imm) << "\n";
			jal(1, imm, 1);
			break;
		}
		case 0b010:   //li
		{
			unsigned int imm = 0;
			unsigned int rd = (comp_instWord >> 7) & 0x1F;
			imm = (comp_instWord >> 2) & 0x1F;
			unsigned int imm5 = comp_instWord >> 12 & 0x1;
			imm5 <<= 5;
			imm |= imm5;
			if (imm5 != 0)
			{
				//cout << "was Here kkk sisi ra2sy" << endl;
				imm |= 0xFFFFFFC0; // Sign extension
			}
			int x = static_cast<int>(imm);
			cout << "\tc.li\tx" << dec << (int)rd << ", " << dec << static_cast<int32_t>(imm) << "\n";
			//printRegisters();
			//cout << "The immediate is " << dec << static_cast<int>(imm) << endl;
			//printRegisters();

			addi(0, rd, imm, 1);
			//printRegisters();
			return;
			break;
		}

		case 0b011:   //LUI
		{
			unsigned int imm = 0;
			rd = (comp_instWord >> 7) & 0x1F;

			if (rd != 2)
			{
				imm = (comp_instWord >> 2) & 0x1F;
				imm <<= 12;
				unsigned int imm17 = comp_instWord >> 12 & 0x1;
				imm17 <<= 12;
				imm |= imm17;
				if (imm17 != 0) imm |= 0xFFFC0000; // Sign extension
				cout << "\tc.lui\tx" << dec << rd << ", 0x" << hex << (imm >> 12) << "\n";
				lui(rd, imm, 1);
				return;
				break;
			}
			else
			{
				unsigned int imm = 0;
				unsigned int imm5 = comp_instWord >> 2 & 0x1;
				unsigned int imm7 = comp_instWord >> 3 & 0x1;
				unsigned int imm8 = comp_instWord >> 4 & 0x1;
				unsigned int imm6 = comp_instWord >> 5 & 0x1;
				unsigned int imm4 = comp_instWord >> 6 & 0x1;
				unsigned int imm9 = comp_instWord >> 12 & 0x1;

				imm5 <<= 5;
				imm7 <<= 7;
				imm8 <<= 8;
				imm6 <<= 6;
				imm4 <<= 4;
				imm9 <<= 9;
				imm |= 0x0 | imm5 | imm7 | imm8 | imm6 | imm4 | imm9;
				if ((imm9 >> 9) & 0x1)
				{
					//cout << "hdulslkjajlkdsjk.a;7ksa;ud;kj.sad;kjad";
					imm = imm | 0xFFFFFC00;
				}

				int hello = static_cast<int>(imm);
				cout << "\tc.addi16sp\t" << dec << (int)hello << "\n";
				addi(2, 2, hello, 1);
				return;




			}

		}
		case 0b101: // c.j
		{
			imm = 0;
			unsigned int imm5 = comp_instWord >> 2 & 0x1;
			unsigned int imm1_3 = comp_instWord >> 3 & 0x7;
			unsigned int imm7 = comp_instWord >> 6 & 0x1;
			unsigned int imm6 = comp_instWord >> 7 & 0x1;
			unsigned int imm10 = comp_instWord >> 8 & 0x1;
			unsigned int imm8_9 = comp_instWord >> 9 & 0x3;
			unsigned int imm4 = comp_instWord >> 11 & 0x1;
			unsigned int imm11 = comp_instWord >> 12 & 0x1;
			imm5 <<= 5;
			imm1_3 <<= 1;
			imm7 <<= 7;
			imm6 <<= 6;
			imm10 <<= 10;
			imm8_9 <<= 8;
			imm4 <<= 4;
			imm11 <<= 11;
			imm |= imm1_3 | imm4 | imm5 | imm6 | imm7 | imm8_9 | imm10 | imm11;

			if (imm11 != 0) imm |= 0xFF1000; // Sign extension

			cout << "\tc.j\tx" << 0 << ", 0x" << hex << (int)(instPC + (imm)) << "\n";
			jal(0, imm, 1);
			unsigned int opcode = 0x6F;
			return;
			break;
		}
		case 0b110: // c.beqz
		{

			imm = 0;
			unsigned int imm5 = comp_instWord >> 2 & 0x1;
			unsigned int imm1 = comp_instWord >> 3 & 0x1;
			unsigned int imm2 = comp_instWord >> 4 & 0x1;
			unsigned int imm6 = comp_instWord >> 5 & 0x1;
			unsigned int imm7 = comp_instWord >> 6 & 0x1;
			unsigned int imm3 = comp_instWord >> 10 & 0x1;
			unsigned int imm4 = comp_instWord >> 11 & 0x1;
			unsigned int imm8 = comp_instWord >> 12 & 0x1;
			imm5 >>= 5;
			imm1 >>= 1;
			imm2 >>= 2;
			imm6 >>= 6;
			imm7 >>= 7;
			imm3 >>= 3;
			imm4 >>= 4;
			imm8 >>= 8;
			imm |= imm1 | imm2 | imm3 | imm4 | imm5 | imm6 | imm7 | imm8;

			rs1 = (comp_instWord >> 7 & 0x7) + 8;
			if (!imm8 == 0) imm | 0xFFFFFFE00;
			cout << "\tc.beqz\tx" << rs1 << ", 2*" << (imm << 1) << "\n";
			beq(rs1, 0, imm, 1);
			return;
		}

		case 0b111:    //c.bnez
		{
			unsigned int imm = 0;
			unsigned int imm5 = comp_instWord >> 2 & 0x1;
			unsigned int imm1 = comp_instWord >> 3 & 0x1;
			unsigned int imm2 = comp_instWord >> 4 & 0x1;
			unsigned int imm6 = comp_instWord >> 5 & 0x1;
			unsigned int imm7 = comp_instWord >> 6 & 0x1;
			unsigned int imm3 = comp_instWord >> 10 & 0x1;
			unsigned int imm4 = comp_instWord >> 11 & 0x1;
			unsigned int imm8 = comp_instWord >> 12 & 0x1;
			imm5 <<= 5;
			imm1 <<= 1;
			imm2 <<= 2;
			imm6 <<= 6;
			imm7 <<= 7;
			imm3 <<= 3;
			imm4 <<= 4;
			imm8 <<= 8;
			imm |= imm1 | imm2 | imm3 | imm4 | imm5 | imm6 | imm7 | imm8;

			rs1 = (comp_instWord >> 7 & 0x7) + 8;
			if (imm8 != 0)
			{
				//cout << "bdakjiaddakakna";
				imm = imm | 0xFFFFFFE00;
			}
			cout << "\tc.bnez\tx" << dec << rs1 << ",  0x" << hex << (imm + instPC) << "\n";
			bne(rs1, 0, imm, 1);
			return;



		}

		case 0b100:   //srli
		{
			if (((comp_instWord >> 10) & 3) == 0)  //SRLI
			{
				imm = 0;
				unsigned int imm0_4 = comp_instWord >> 2 & 0x1F;
				unsigned int imm5 = comp_instWord >> 12 & 0x1;
				imm5 <<= 5;
				rd = (comp_instWord >> 7 & 0x7) + 8;
				if (imm5 != 0) imm |= 0xFFFFFFC0;
				cout << "\tc.srli\tx" << rd << ", " << dec << (int)imm << "\n";
				srli(rd, rd, imm, 1);
				return;

				break;

			}
			else if (((comp_instWord >> 10) & 3) == 1)   //SRAI
			{
				imm = 0;
				unsigned int imm0_4 = comp_instWord >> 2 & 0x1F;
				unsigned int imm5 = comp_instWord >> 12 & 0x1;
				rd = comp_instWord >> 7 & 0x7 + 8;
				if (imm5 != 0) imm |= 0xFFFFFFC0;
				cout << "\tc.srai\tx" << rd << ",  " << imm << "\n";
				srai(rd, rd, imm, 1);
				return;

				break;

			}
			else if (((comp_instWord >> 10) & 3) == 2)  //ANDI
			{
				imm = 0;
				unsigned int imm0_4 = comp_instWord >> 2 & 0x1F;
				unsigned int imm5 = comp_instWord >> 12 & 0x1;
				rd = comp_instWord >> 7 & 0x7 + 8;
				if (imm5 != 0) imm |= 0xFFFFFFC0;
				cout << "\tc.andi\tx" << (int)rd << ",  " << (int)imm << "\n";
				andi(rd, rd, imm, 1);
				return;

				break;
			}
			else if (((comp_instWord >> 10) & 0x7) == 0x3)
			{
				if (((comp_instWord >> 5) & 0x3) == 0)   //sub
				{

					rs2 = ((comp_instWord >> 2) & 0x7) + 8;
					rd = ((comp_instWord >> 7) & 0x7) + 8;
					cout << "\tc.sub\tx" << (int)rd << ",  x" << (int)rs2 << "\n";
					sub(rd, rs2, rd, 1);


				}
				else if (((comp_instWord >> 5) & 0x3) == 1)   //xor
				{
					rs2 = ((comp_instWord >> 2) & 0x7) + 8;
					rd = ((comp_instWord >> 7) & 0x7) + 8;
					cout << "\tc.xor\tx" << (int)rd << ",  x" << (int)rs2 << "\n";
					xorFn(rd, rs2, rd, 1);

				}
				else if (((comp_instWord >> 5) & 0x3) == 2)     //or
				{

					rs2 = ((comp_instWord >> 2) & 0x7) + 8;
					rd = ((comp_instWord >> 7) & 0x7) + 8;
					cout << "\tc.or\tx" << rd << ",  x" << rs2 << "\n";
					orFn(rd, rs2, rd, 1);

				}

				else if (((comp_instWord >> 5) & 0x3) == 3)    //and
				{

					rs2 = ((comp_instWord >> 2) & 0x7) + 8;
					rd = ((comp_instWord >> 7) & 0x7) + 8;
					cout << "\tc.and\tx" << (int)rd << ",  x" << (int)rs2 << "\n";
					andFn(rd, rs2, rd, 1);

				}





			}


		}
		}

		break;
	}

	case 0b10: // Quadrant 2
	{
		switch (funct3)
		{
		case 0b000: // c.slli
		{
			imm = 0;
			rd = (comp_instWord >> 7) & 0x1F;
			imm = (comp_instWord >> 2) & 0x1F;
			imm |= comp_instWord >> 12 & 0x1;
			if (imm >> 5) imm |= 0xFFFFFFC0;
			cout << "\tc.slli\tx" << dec << (int)rd << ",  " << (int)imm << "\n";
			slli(rd, rd, imm, 1);
			return;
			break;
		}
		case 0b010: // c.lwsp
		{
			rd = (comp_instWord >> 7) & 0x1F;

			imm = 0;
			unsigned int imm6 = comp_instWord >> 2 & 0x1;
			unsigned int imm7 = comp_instWord >> 3 & 0x1;
			unsigned int imm2_4 = comp_instWord >> 4 & 0x7;
			unsigned int imm5 = comp_instWord >> 12 & 0x1;
			imm6 <<= 6;
			imm7 <<= 7;
			imm2_4 <<= 2;
			imm5 <<= 5;
			imm |= imm6 | imm7 | imm5 | imm2_4;
			if (!imm7 == 0) imm |= 0xFFFFFF00;
			cout << "\tc.lw\tx" << rd << ",  " << imm << "\n";

			lw(2, rd, imm, 1);
			return;
			break;
		}
		case 0b100: // c.jr/c.jalr/c.mv/c.add
		{
			rs1 = (comp_instWord >> 7) & 0x1F;
			rs2 = (comp_instWord >> 2) & 0x1F;
			rd = rs1;
			unsigned int control = (comp_instWord >> 12) & 0x1;
			if (rs2 == 0 && rs1 != 0 && !control)
			{
				cout << "\tc.jr\tx" << rs1 << "\n";
				jalr(0, rs1, 0, 1);
				return;
			}
			else if (rs2 == 0 && rs1 != 0 && control)
			{
				cout << "\tc.jalr\tx" << rs1 << "\n";
				jalr(1, rs1, 0, 1);
				return;
			}
			else if (rs2 != 0 && rs1 != 0 && !control)
			{
				cout << "\tc.mv\tx" << dec << (int)rd << ", x" << (int)rs2 << "\n";
				add(rs2, 0, rd, 1);
				return;
			}
			else if (rs2 != 0 && rs1 != 0 && control)
			{
				cout << "\tc.add\tx" << (int)rd << ", x" << (int)rs2 << "\n";
				add(rs2, rd, rd, 1);
				return;
			}
			else if (rs2 == 0 && rs1 == 0 && control)
			{
				cout << "\tc.ebreak\t" << "\n";
				exit(0);

			}
		}
		case 0b110: // c.swsp
		{
			unsigned int imm = 0;
			rs2 = (comp_instWord >> 2) & 0x1F;
			unsigned int imm6 = (comp_instWord >> 7) & 0x1;
			unsigned int imm7 = (comp_instWord >> 8) & 0x1;
			unsigned int imm2_5 = (comp_instWord >> 9) & 0xF;
			imm6 <<= 6;
			imm7 <<= 7;
			imm2_5 <<= 2;
			imm = 0 | imm6 | imm7 | imm2_5;
			if (!imm7 == 0) imm |= 0xFFFFFF00;
			cout << "\tc.swsp\tx" << dec << (int)rs2 << ",  " << imm << "\n";
			sw(2, rs2, imm, 1);
			return;
			break;
		}


		}
		break;
	}

	default:
		cout << "Unknown compressed instruction" << endl;
	}

	return;
}
void instDecExec(unsigned int instWord)
{
	unsigned int rd, rs1, rs2, funct3, funct7, opcode;
	unsigned int I_imm, S_imm, B_imm, U_imm, J_imm;
	unsigned int address;
	unsigned int comp_opcode;

	unsigned int instPC = pc - 4;

	comp_opcode = instWord & 0x3;
	opcode = instWord & 0x0000007F;
	rd = (instWord >> 7) & 0x0000001F;
	funct3 = (instWord >> 12) & 0x00000007;
	rs1 = (instWord >> 15) & 0x0000001F;
	rs2 = (instWord >> 20) & 0x0000001F;
	funct7 = (instWord >> 25) & 0x0000007F;

	// — inst[31] — inst[30:25] inst[24:21] inst[20]
	I_imm = ((instWord >> 20) & 0x7FF) | (((instWord >> 31) ? 0xFFFFF800 : 0x0));
	S_imm = ((instWord >> 7) & 0x1F) | ((instWord >> 20) & 0xFE0) | (((instWord >> 31) ? 0xFFFFF000 : 0x0));
	B_imm = 0x0 | ((instWord >> 7) & 0x1E) | ((instWord >> 20) & 0x7E0) | ((instWord << 4) & 0x800) | ((instWord >> 19) & 0x1000);
	if (B_imm & 0x1000)
	{
		B_imm |= 0xFFFFE000; // Sign-extend to 32 bits
	}
	U_imm = instWord & 0xFFFFF000;


	J_imm = (instWord & 0xFF000)          // bits 19-12
		| ((instWord >> 9) & 0x800)    // bit 11
		| ((instWord >> 20) & 0x7FE)   // bits 10-1
		| ((instWord >> 11) & 0x100000); // bit 20

	// Adjust for sign extension if necessary
	if (instWord & 0x80000000)

	{ // Check if the sign bit (bit 31) is set
		J_imm |= 0xFFF00000; // Set the upper bits for sign extension
	}

	J_imm &= 0xFFFFFFFE; // Ensure the least significant bit is zero


	printPrefix(instPC, instWord);




	if (opcode == 0x33)    	// R Instructions
	{
		switch (funct3)
		{
		case 0:
		{
			if (funct7 == 32)
			{
				cout << "\tSUB\tx" << (int)rd << ", x" << (int)rs1 << ", x" << (int)rs2 << "\n";
				sub(rs1, rs2, rd, 0);
			}
			else
			{
				cout << "\tADD\tx" << (int)rd << ", x" << (int)rs1 << ", x" << (int)rs2 << "\n";
				add(rs1, rs2, rd, 0);
			}
			break;
		}

		case 1:
		{
			cout << "\tSLL\tx" << (int)rd << ", x" << (int)rs1 << ", x" << (int)rs2 << "\n";
			sll(rs1, rs2, rd, 0);
			break;
		}

		case 2:
		{
			cout << "\tSLT\tx" << (int)rd << ", x" << (int)rs1 << ", x" << (int)rs2 << "\n";
			slt(rs1, rs2, rd, 0);
			break;
		}

		case 3:
		{
			cout << "\tSLTU\tx" << (int)rd << ", x" << (int)rs1 << ", x" << (int)rs2 << "\n";
			sltu(rs1, rs2, rd, 0);
			break;
		}

		case 4:
		{
			cout << "\tXOR\tx" << (int)rd << ", x" << (int)rs1 << ", x" << (int)rs2 << "\n";
			xorFn(rs1, rs2, rd, 0);
			break;
		}

		case 5:
		{
			if (funct7 == 32)
			{
				cout << "\tSRA\tx" << (int)rd << ", x" << (int)rs1 << ", x" << (int)rs2 << "\n";
				sra(rs1, rs2, rd, 0);
			}
			else
			{
				cout << "\tSRL\tx" << (int)rd << ", x" << (int)rs1 << ", x" << (int)rs2 << "\n";
				srl(rs1, rs2, rd, 0);
			}
			break;
		}

		case 6:
		{
			cout << "\tOR\tx" << (int)rd << ", x" << (int)rs1 << ", x" << (int)rs2 << "\n";
			orFn(rs1, rs2, rd, 0);
			break;
		}


		case 7:
		{
			cout << "\tAND\tx" << (int)rd << ", x" << (int)rs1 << ", x" << (int)rs2 << "\n";
			andFn(rs1, rs2, rd, 0);
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
			cout << "\tADDI\tx" << (int)rd << ", x" << (int)rs1 << ", " << dec << (int)I_imm << "\n";
			addi(rs1, rd, I_imm, 0);
			break;
		}

		case 1:
		{
			cout << "\tSLLI\tx" << dec << (int)rd << ", x" << (int)rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			slli(rs1, rd, I_imm, 0);

			break;
		}

		case 2:
		{
			cout << "\tSLTI\tx" << dec << (int)rd << ", x" << (int)rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			slti(rs1, rd, I_imm, 0);

			break;
		}


		case 3:
		{
			cout << "\tSLTIU\tx" << dec << (int)rd << ", x" << (int)rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			sltiu(rs1, rd, I_imm, 0);

			break;
		}

		case 4:
		{
			cout << "\tXORI\tx" << dec << (int)rd << ", x" << (int)rs1 << ", " << dec << (int)I_imm << "\n";
			xori(rs1, rd, I_imm, 0);

			break;
		}

		case 5:
		{
			if (funct7 == 32)
			{
				cout << "\tSRAI\tx" << dec << (int)rd << ", x" << (int)rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
				srai(rs1, rd, I_imm, 0);

			}
			else
			{
				cout << "\tSRLI\tx" << dec << (int)rd << ", x" << (int)rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
				srli(rs1, rd, I_imm, 0);

			}
			break;
		}

		case 6:
		{
			cout << "\tORI\tx" << (int)rd << dec << ", x" << (int)rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			ori(rs1, rd, I_imm, 0);
			break;
		}
		case 7:
		{
			cout << "\tANDI\tx" << dec << (int)rd << ", x" << (int)rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			andi(rs1, rd, I_imm, 0);
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
			cout << "\tSB\tx" << (int)rs2 << "," << dec << S_imm << "(x" << (int)rs1 << ")" << "\n";
			sb(rs1, rs2, S_imm, 0);
			break;
		}

		case 1:
		{
			cout << "\tSH\tx" << (int)rs2 << "," << dec << S_imm << "(x" << (int)rs1 << ")" << "\n";
			sh(rs1, rs2, S_imm, 0);

			break;

		}

		case 2:
		{
			int x = static_cast<int> (S_imm);

			cout << "\tSW\tx" << dec << (int)rs2 << "," << dec << x << "(x" << (int)rs1 << ")" << "\n";
			sw(rs1, rs2, S_imm, 0);
			break;
		}

		default:
		{
			cout << "\t Unknown instruction \n";
		}
		}


	}
	else if (opcode == 0x63)  // B instruction
	{
		switch (funct3)
		{
		case 0:
		{
			cout << "\tBEQ\tx" << (int)rs1 << ", x" << (int)rs2 << ", " << hex << "0x" << hex << instPC + B_imm << "\n";
			beq(rs1, rs2, B_imm, 0);
			break;
		}

		case 1:
		{
			cout << "\tBNE\tx" << (int)rs1 << ", x" << (int)rs2 << ", " << hex << "0x" << (int)B_imm + instPC << "\n";
			bne(rs1, rs2, B_imm, 0);
			break;

		}

		case 4:
		{
			cout << "\tBLT\tx" << (int)rs1 << ", x" << (int)rs2 << ", " << hex << "0x" << (int)B_imm + instPC << "\n";
			blt(rs1, rs2, B_imm, 0);
			break;
		}

		case 5:
		{
			cout << "\tBGE\tx" << (int)rs1 << ", x" << (int)rs2 << ", " << hex << "0x" << (int)B_imm + instPC << "\n";
			bge(rs1, rs2, B_imm, 0);
			break;
		}

		case 6:
		{
			cout << "\tBLTU\tx" << (int)rs1 << ", x" << (int)rs2 << ", " << hex << "0x" << (int)B_imm + instPC << "\n";
			bltu(rs1, rs2, B_imm, 0);
			break;
		}

		case 7:
		{
			cout << "\tBGEU\tx" << (int)rs1 << ", x" << (int)rs2 << ", " << hex << "0x" << (int)B_imm + instPC << "\n";
			bgeu(rs1, rs2, B_imm, 0);
			break;
		}


		}
	}
	else if (opcode == 0x37)   //LUI
	{
		cout << "\tLUI\tx" << rd << ", " << hex << "0x" << (int)U_imm << "\n";
		lui(rd, U_imm, 0);

	}
	else if (opcode == 0x17)  //AUIPC
	{
		cout << "\tAUIBC\tx" << rd << ", " << hex << "0x" << (int)(U_imm >> 12) << "\n";
		auipc(rd, U_imm, 0);


	}
	else if (opcode == 0x6F)   //   JAL
	{
		cout << "\tJAL\tx" << rd << ", " << hex << "0x" << (int)J_imm << "\n";
		jal(rd, J_imm, 0);


	}
	else if (opcode == 0x67) // JALR
	{

		cout << "\tJALR\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
		jalr(rd, rs1, I_imm, 0);

	}
	else if (opcode == 0x03) // load
	{

		switch (funct3)
		{
		case 0:
		{
			cout << "\tLB\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			lb(rs1, rd, I_imm, 0);
			break;

		}

		case 1:
		{
			cout << "\tLH\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			lh(rs1, rd, I_imm, 0);
			break;
		}

		case 2:
		{
			int x = static_cast<int>(I_imm);
			cout << "\tLW\tx" << dec << rd << ", " << dec << x << "(x" << (int)rs1 << ")" << "\n";
			lw(rs1, rd, I_imm, 0);
			break;
		}


		case 4:
		{
			cout << "\tLBU\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			lbu(rs1, rd, I_imm, 0);
			break;
		}

		case 5:
		{
			cout << "\tLHU\tx" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			lhu(rs1, rd, I_imm, 0);
			break;
		}

		default:
			cout << "\tUnkown I Instruction \n";
		}
	}
	else if (opcode == 0x73) // ecall
	{
		cout << "\tECALL\ta7 = " << regMemory[17] << ",\t a0 = " << regMemory[10] << endl;
		ecall();
		/*for (int i = 8192; i < 10000; i += 1)
		{
			lb(0, 2, i);
			cout << (char)regMemory[2];
		}
		cout << endl << endl;*/

	}
	else
	{
		cout << "\tUnkown Instruction \n";
	}


}

// g++ -o riscsim ... names of files
// ./riscsim names of files

int main(int argc, char* argv[])
{
	unsigned int instWord = 0;
	ifstream inFile;
	ifstream inpDataFile;
	ofstream outFile;

	if (argc < 1) // An error if the number of files is less than one
		emitError("you did not enter any files\n");

	if (argc == 3)
		inpDataFile.open(argv[2], ios::in | ios::binary | ios::ate);	
	
	inFile.open(argv[1], ios::in | ios::binary | ios::ate);

	if (inpDataFile.is_open())
	{
		int fsize = inpDataFile.tellg();
		inpDataFile.seekg(0, inpDataFile.beg);
		if (!inpDataFile.read((char*)(memory + 0x10000), fsize))
			emitError("Cannot read from data file\n");
	}
	if (inFile.is_open())
	{
		int fsize = inFile.tellg();
		inFile.seekg(0, inFile.beg);
		if (!inFile.read((char*)memory, fsize))
			emitError("Cannot read from text file\n");
	}


	if (inFile.is_open())
	{

		while (true)
		{
			// deCompress(instWord);
			instWord = (unsigned char)memory[pc] |
				(((unsigned char)memory[pc + 1]) << 8) |
				(((unsigned char)memory[pc + 2]) << 16) |
				(((unsigned char)memory[pc + 3]) << 24);
			if (instWord == 0 || pc > 0x10000)
				break; // stop when PC reached address 32
			if ((instWord & 0x3) != 3)
			{
				instWord = (unsigned char)memory[pc] | (((unsigned char)memory[pc + 1]) << 8);
				pc += 2;
				decompress(instWord);

			}
			else
			{
				pc += 4;
				instDecExec(instWord);
			}

			if (instWord == 0 || pc > 65536) // stop when PC reached address 0x10000
				break;
			//printRegisters();

		}
	}
	else
		emitError("Cannot access text file\n");
}


/*int main()
{
	unsigned int instWord = 0;
	ifstream inFile;
	ifstream inpDataFile;
	ofstream outFile;

	//if (argc < 1) // An error if the number of files is less than one
	//    emitError("use: rvcdiss <machine_code_file_name>\n");

	inpDataFile.open("C:/Users/mosta/Desktop/samples/t1-d.bin", ios::in | ios::binary | ios::ate);
	inFile.open("C:/Users/mosta/Desktop/samples/t3.bin", ios::in | ios::binary | ios::ate);

	if (inpDataFile.is_open())
	{
		int fsize = inpDataFile.tellg();
		inpDataFile.seekg(0, inpDataFile.beg);
		if (!inpDataFile.read((char*)(memory + 0x10000), fsize))
			emitError("Cannot read from data file\n");
	}
	if (inFile.is_open())
	{
		int fsize = inFile.tellg();
		inFile.seekg(0, inFile.beg);
		if (!inFile.read((char*)memory, fsize))
			emitError("Cannot read from text file\n");
	}


	if (inFile.is_open())
	{

		while (true)
		{
			// deCompress(instWord);
			instWord = (unsigned char)memory[pc] |
				(((unsigned char)memory[pc + 1]) << 8) |
				(((unsigned char)memory[pc + 2]) << 16) |
				(((unsigned char)memory[pc + 3]) << 24);
			if (instWord == 0 || pc > 0x10000)
				break; // stop when PC reached address 32
			if ((instWord&0x3)!=3)
			{
				instWord = (unsigned char)memory[pc] | (((unsigned char)memory[pc + 1]) << 8);
				pc += 2;
				decompress(instWord);

			}
			else
			{
				pc += 4;
				instDecExec(instWord);
			}

			if (instWord == 0 || pc > 65536) // stop when PC reached address 0x10000
				break;
			   printRegisters();

		}
	}
	else
		emitError("Cannot access text file\n");
}*/
