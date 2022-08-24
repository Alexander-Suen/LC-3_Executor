
/**
* @name LC-3 Executor
*
* @file LC3_Executor_v0.5.cpp
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
	int GetCondition();
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

int Reg::GetCondition() {
	if (reg_value > 0) {
		return 1;
	} else if (reg_value == 0) {
		return 0;
	} else {
		return -1;
	}
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
	int incre_num = 0; // LDI, increment number
	int BaseR = 0; // JMP, JSRR, LDR, STR
	int condition_code = 0;

	//string str;
	string instruction[100];
	int ins_count = -1;
	int total_count = 0;

	// Read all the instructions
	// Input should be ended with an empty line (\n) rather than HALT.
	while (1) {
		ins_count++;
		getline(cin, instruction[ins_count]);
		if (instruction[ins_count] == "") {
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

			PCoffset9 = GetNum(instruction[ins_count].substr(7, 9));
			cout << "BR: PCoffset9 = " << PCoffset9 << endl;
			// trace back to find the conditional code of last instruction

			if (instruction[ins_count][4] == '1') { // BRn

			} else if (instruction[ins_count][5] == '1') { // BRz

			} else if (instruction[ins_count][6] == '1') { // BRp

			} else {

			}

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
			cout << "LD: PCoffset9 = " << PCoffset9 << ", ins_count = " << ins_count << endl;
			cout << "LD: instruction[ins_count + PCoffset9 + 1] = " << instruction[ins_count + PCoffset9 + 1] << endl;
			cout << "LD: GetNum(instruction[ins_count + PCoffset9 + 1]) = " <<
				GetNum(instruction[ins_count + PCoffset9 + 1]) << endl;
			registers[DR_num].SetValue(GetNum(instruction[ins_count + PCoffset9 + 1]));
			break;
		case 3: // ST (0011)
			SR1_num = GetNum(instruction[ins_count].substr(4, 3));
			PCoffset9 = GetNum(instruction[ins_count].substr(7, 9));

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
			DR_num = GetNum(instruction[ins_count].substr(4, 3));
			BaseR = GetNum(instruction[ins_count].substr(7, 3));
			offset6 = GetNum(instruction[ins_count].substr(10, 6));
			cout << "LDR: DR_num = " << DR_num << ", BaseR = " << BaseR << ", offset6 = " << offset6 << endl;
			printf("LDR: R2 value = x%04X\n", registers[BaseR].GetValue(BaseR)); // format print
			cout << "LDR: instruction[ins_count + registers[BaseR].GetValue(BaseR) + offset6 - 0x7777] = " <<
				instruction[ins_count + registers[BaseR].GetValue(BaseR) + offset6 - 0x7777] << endl;
			//cout << "LDR: R2 value = " << registers[BaseR].GetValue(BaseR) << endl;
			// Convert 16-bit string to int (hexadecimal) by "strtoull(string.c_str(), NULL, 2)
			registers[DR_num].SetValue( strtoull(instruction[ins_count + registers[BaseR].GetValue(BaseR) + offset6 - 0x7777].c_str(), NULL, 2) );
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
			DR_num = GetNum(instruction[ins_count].substr(4, 3));
			PCoffset9 = GetNum(instruction[ins_count].substr(7, 9));
			cout << "LDI: PCoffset9 = " << PCoffset9 << ", ins_count = " << ins_count << endl;
			cout << "LDI: instruction[ins_count + PCoffset9 + 1] = " << instruction[ins_count + PCoffset9 + 1] << endl;
			cout << "LDI: GetNum(instruction[ins_count + PCoffset9 + 1]) = " << GetNum(instruction[ins_count + PCoffset9 + 1]) << endl; // Error: 
			cout << "LDI: strtoull(str.c_str(), NULL, 2) = " << strtoull(instruction[ins_count + PCoffset9 + 1].c_str(), NULL, 2) << endl;
			incre_num = strtoull(instruction[ins_count + PCoffset9 + 1].c_str(), NULL, 2) - 0x7777; // get relative address
			cout << "LDI: strtoull(str.c_str(), NULL, 2) = " << incre_num << endl; // increment number
			registers[DR_num].SetValue( GetNum( instruction[ins_count + incre_num])); // Load address indirectly
			break;
		case 11: // STI (1011)

			break;
		case 12: // RET (1100)

			break;
		case 13: // reserved (1101)
			cout << "Reserved, 1101" << endl;
			break;
		case 14: // LEA (1110), load effect address
			DR_num = GetNum(instruction[ins_count].substr(4, 3));
			PCoffset9 = GetNum(instruction[ins_count].substr(7, 9));
			cout << "LEA: DR_num = " << DR_num << ", PCoffset9 = " << PCoffset9 << endl;
			registers[DR_num].SetValue(0x7777 + ins_count + PCoffset9);
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






