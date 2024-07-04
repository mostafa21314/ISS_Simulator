#pragma once
#include<string>
using namespace std;
class instructionR
{



	void add(string rs1, string rs2, string rd)
	{
		int x = getRig();
		int y = getRig();
		int z;
		int carry;
		while (y != 0) 
		{
			carry = (x & y) << 1;
			x = x ^ y;
			y = carry;
		}
		z = x;
	}
};

