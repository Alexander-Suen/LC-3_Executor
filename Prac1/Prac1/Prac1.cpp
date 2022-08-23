
/**
* @name LC-3 Executor
* 
* @file Prac1.cpp
* 
* @brief This file includes the LC-3 executor assignment for Lab6
* of the course Introduction to Computing Systems
* 
* @author Minghao Sun (3180100729)
* Contact: b.sun.med@gmail.com
* 
*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

static int R0;
static int R1;
static int R2;
static int R3;
static int R4;
static int R5;
static int R6;
static int R7;

//class R // register class R
//{
//public:
//	int SetValue(int value);
//};


int GetR0()
{
	return R0;
}

void SetR0(int R0_num)
{
	R0 = R0_num;
}

int GetR1()
{
	return R1;
}

void SetR1(int R1_num)
{
	R1 = R1_num;
}

int GetR2()
{
	return R2;
}

void SetR2(int R2_num)
{
	R2 = R2_num;
}

int GetR3()
{
	return R3;
}

void SetR3(int R3_num)
{
	R3 = R3_num;
}

int GetR4()
{
	return R0;
}

void SetR4(int R4_num)
{
	R4 = R4_num;
}

int GetR5()
{
	return R5;
}

void SetR5(int R5_num)
{
	R5 = R5_num;
}

int GetR6()
{
	return R6;
}

void SetR6(int R6_num)
{
	R6 = R6_num;
}

int GetR7()
{
	return R7;
}

void SetR7(int R7_num)
{
	R7 = R7_num;
}

void InitReg()
{
	SetR0(0x7777);
	SetR1(0x7777);
	SetR2(0x7777);
	SetR3(0x7777);
	SetR4(0x7777);
	SetR5(0x7777);
	SetR6(0x7777);
	SetR7(0x7777);
}

void PrintOut()
{
	printf("R%d = x%04hX\n", 0, GetR0());
	printf("R%d = x%04hX\n", 1, GetR1());
	printf("R%d = x%04hX\n", 2, GetR2());
	printf("R%d = x%04hX\n", 3, GetR3());
	printf("R%d = x%04hX\n", 4, GetR4());
	printf("R%d = x%04hX\n", 5, GetR5());
	printf("R%d = x%04hX\n", 6, GetR6());
	printf("R%d = x%04hX\n", 7, GetR7());

}


// Instruction implementation
void BR(string str)
{

}

void ADD(string str)
{

}

void LD(string str)
{

}

void ST(string str)
{

}

void JSR_JSRR()
{

}

void AND()
{

}

void LDR()
{

}

void STR()
{

}

void NOT()
{

}

void LDI()
{

}

void STI()
{

}

void RET()
{

}

void LEA()
{

}

void TRAPx25() // HALT
{
	PrintOut();

	exit(0); // EXIT_SUCESS
}




// Calculate sum of the first four bits of an instruction
int BitHash(string instruction)
{
	int sum_hash = 0;
	for (int i = 0; i < 4; i++)
	{
		sum_hash += (int)((instruction[i] - '0') * pow(2, 3 - i));
	}
	
	return sum_hash;
}




int main()
{
	cout << "Hello, LC-3 Executor!" << endl;
	InitReg(); // Initialize values of all registers as 0x7777

	string str;

	while (1){
		getline(cin, str);

		switch (BitHash(str))
		{
		case 0:
			BR(str);
			break;
		case 1:
			ADD(str);
			break;
		case 2:
			LD(str);
			break;
		case 3:
			ST(str);
			break;
		case 4:
			JSR_JSRR();
			break;
		case 5:
			AND();
			break;
		case 6:
			LDR();
			break;
		case 7:
			STR();
			break;
		case 8:
			cout << "RTI(1101) is not required" << endl;
			break;
		case 9:
			NOT();
			break;
		case 10:
			LDI();
			break;
		case 11:
			STI();
			break;
		case 12:
			RET();
			break;
		case 13:
			cout << "Reserved, 1101" << endl;
			break;
		case 14:
			LEA();
			break;
		case 15:
			TRAPx25();
			break;
		default:
			cout << "Invalid instruction" << endl;
			break;
		} // switch
	} // while
	
} // main








