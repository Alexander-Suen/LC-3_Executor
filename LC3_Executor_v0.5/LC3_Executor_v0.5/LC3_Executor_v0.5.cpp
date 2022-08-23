
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


class Reg { // Register class Reg
public:
	Reg(int reg_number, int reg_value); // constructor
	int reg_number;
	int reg_value;

	int SetValue(int value);
	int GetValue(int reg_num);
	// Instruction declaration

	void BR(string str);
	void ADD(string str);
	void LD(string str);
	void ST(string str);
	void JSR_JSRR(string str);
	void AND(string str);
	void LDR(string str);
	void STR(string str);
	void NOT(string str);
	void LDI(string str);
	void STI(string str);
	void RET(string str);
	void LEA(string str);

};

Reg::Reg(int para1, int para2) {
	reg_number = para1;
	reg_value = para2;
}


int Reg::SetValue(int value) {
	reg_value = value;
	return reg_value;
}

int Reg::GetValue(int reg_num) {
	return reg_value;
}

// Get the number from the substring
int GetNum(string str) {
	int sum_num = 0;
	for (int i = 0; i < str.length(); i++) {
		sum_num += (int)((str[i] - '0') * pow(2, str.length() - 1 - i));
	}

	return sum_num;
}



void PrintOut(Reg* registers) {
	for (int i = 0; i < 8; i++) {
		printf("R%d = x%04hX\n", i, registers[i].GetValue(i));
	}
}


// Instruction implementation
void Reg::BR(string str) {

}

void Reg::ADD(string str) {

}

void Reg::LD(string str) {

}

void Reg::ST(string str) {

}

void Reg::JSR_JSRR(string str) {

}

void Reg::AND(string str) {

}

void Reg::LDR(string str) {

}

void Reg::STR(string str) {

}

void Reg::NOT(string str) {
	
	

}

void Reg::LDI(string str) {

}

void Reg::STI(string str) {

}

void Reg::RET(string str) {

}

void Reg::LEA(string str) {

}



// Calculate sum of the first four bits of an instruction
int BitHash(string instruction) {
	int sum_hash = 0;
	for (int i = 0; i < 4; i++)
	{
		sum_hash += (int)((instruction[i] - '0') * pow(2, 3 - i));
	}

	return sum_hash;
}

Reg registers[8] = { // register objects constructors
	Reg(0, 0x7777),
	Reg(1, 0x7777),
	Reg(2, 0x7777),
	Reg(3, 0x7777),
	Reg(4, 0x7777),
	Reg(5, 0x7777),
	Reg(6, 0x7777),
	Reg(7, 0x7777)
};

int main() {
	//cout << "Hello, LC-3 Executor!" << endl;
	
	int SR1_num = 0;
	int SR2_num = 0;
	int DR_num = 0;
	int imm5 = 0;
	int PCoffset9 = 0;
	int PCoffset11 = 0; // JSR
	int offset6 = 0; // LDR, STR

	//string str;
	string instruction[100];
	int ins_count = -1;
	int total_count = 0;

	// read all the instructions
	while (1) {
		ins_count++;
		getline(cin, instruction[ins_count]);
		if (BitHash(instruction[ins_count]) == 15) {
			total_count = ins_count + 1;
			break;
		}
	}

	//// Debug
	//cout << ins_count << " " << total_count << endl;
	//for (int i = 0; i < total_count; i++) {
	//	cout << instruction[i] << endl;
	//}

	// Instruction processing
	ins_count = -1;
	while (ins_count < total_count) {
		ins_count++;
		switch (BitHash(instruction[ins_count])) {
		case 0: // BR (0000)

			break;
		case 1: // ADD (0001)
			DR_num = GetNum(instruction[ins_count].substr(4, 3));
			SR1_num = GetNum(instruction[ins_count].substr(7, 3));
			if (instruction[ins_count][10] == '1') { // if str[10] == '1'
				imm5 = GetNum(instruction[ins_count].substr(11, 5));
				//cout << imm5 << endl;
				registers[DR_num].SetValue(registers[SR1_num].GetValue(SR1_num) + imm5);
			}
			else { // str[10] == '0'
				SR2_num = GetNum(instruction[ins_count].substr(13, 3));
				registers[DR_num].SetValue(registers[SR1_num].GetValue(SR1_num) + registers[SR2_num].GetValue(SR2_num));
			}
			break;
		case 2: // LD (0010)
			DR_num = GetNum(instruction[ins_count].substr(4, 3));
			PCoffset9 = GetNum(instruction[ins_count].substr(7, 9));

			break;
		case 3: // ST (0011)

			break;
		case 4: // JSR_JSRR (0100)

			break;
		case 5: // AND (0101)
			DR_num = GetNum(instruction[ins_count].substr(4, 3));
			SR1_num = GetNum(instruction[ins_count].substr(7, 3));
			if (instruction[ins_count][10] == '1') { // if str[10] == '1'
				imm5 = GetNum(instruction[ins_count].substr(11, 5));
				//cout << imm5 << endl;
				registers[DR_num].SetValue(registers[SR1_num].GetValue(SR1_num) & imm5);
			}
			else { // str[10] == '0'
				SR2_num = GetNum(instruction[ins_count].substr(13, 3));
				registers[DR_num].SetValue(registers[SR1_num].GetValue(SR1_num) & registers[SR2_num].GetValue(SR2_num));
			}
			break;
		case 6: // LDR (0110)

			break;
		case 7: // STR (0111)

			break;
		case 8: // RTI (1101)
			cout << "RTI(1101) is not required" << endl;
			break;
		case 9: // NOT (1001)
			DR_num = GetNum(instruction[ins_count].substr(4, 3));
			SR1_num = GetNum(instruction[ins_count].substr(7, 3));
			//cout << DR_num << endl << SR_num << endl;
			registers[DR_num].SetValue(~registers[SR1_num].GetValue(SR1_num));
			break;
		case 10: // LDI (1010)

			break;
		case 11: // STI (1011)

			break;
		case 12: // RET (1100)

			break;
		case 13: // reserved (1101)
			cout << "Reserved, 1101" << endl;
			break;
		case 14: // LEA (1110)

			break;
		case 15:
			PrintOut(registers);
			cout << "Total number of instructions: " << ins_count + 1 << endl; // instruction counter
			exit(0);
			break;
		default:
			cout << "Invalid instruction" << endl;
			break;
		} // switch


	} // while




} // main






