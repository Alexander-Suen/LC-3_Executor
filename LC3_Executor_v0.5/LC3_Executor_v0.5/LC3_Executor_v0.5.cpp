
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
	int GetValue(int reg_num); // reg_num not required

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

// Get the condition code from the former instruction
int GetCondition(int ins_count, const string instruction[], const Reg registers[]) {
	ins_count--; // Get the former instruction
	//cout << "GetCondition(): ins_count = " << ins_count << ", registers[GetNum(instruction[ins_count].substr(4, 3))] = " << registers[GetNum(instruction[ins_count].substr(4, 3))].reg_value << endl;

	if (registers[GetNum(instruction[ins_count].substr(4, 3))].reg_value > 0) {
		return 1;
	}
	else if (registers[GetNum(instruction[ins_count].substr(4, 3))].reg_value == 0) {
		return 0;
	}
	else {
		return -1;
	}
}


void PrintOut(Reg* registers) {
	for (int i = 0; i < 8; i++) {
		printf("R%d = x%04hX\n", i, registers[i].GetValue(i));
	}
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
	int condition_code = 2; // default condition code = 2
	int temp_ins_count = 0; // BR

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
			//cout << "BR" << endl;
			condition_code = GetCondition(ins_count, instruction, registers); // Get condition code
			//cout << "condition_code = " << condition_code << endl;

			//temp_ins_count = ins_count--;
			//if (registers[GetNum(instruction[temp_ins_count].substr(4, 3))].GetValue(GetNum(instruction[temp_ins_count].substr(4, 3))) > 0) {
			//	cout << "Condition code = 1" << endl;
			//	condition_code = 1;
			//} else if (registers[GetNum(instruction[temp_ins_count].substr(4, 3))].GetValue(GetNum(instruction[temp_ins_count].substr(4, 3))) == 0)  {
			//	cout << "Condition code = 0" << endl;
			//	condition_code = 0;
			//} else if (registers[GetNum(instruction[temp_ins_count].substr(4, 3))].GetValue(GetNum(instruction[temp_ins_count].substr(4, 3))) < 0) {
			//	cout << "Condition code = -1" << endl;
			//	condition_code = -1;
			//}

			PCoffset9 = GetNum(instruction[ins_count].substr(7, 9));
			//cout << "BR: PCoffset9 = " << PCoffset9 << endl;
			//cout << "instruction[ins_count] = " << instruction[ins_count] << endl;
			// trace back to find the conditional code of last instruction

			// BR n z p
			if (instruction[ins_count][4] == '1') { // BRn
				//cout << "BRn" << endl;
				if (condition_code == -1) {
					ins_count += PCoffset9;
				}
			} else if (instruction[ins_count][5] == '1') { // BRz
				//cout << "BRz" << endl;
				if (condition_code == 0) {
					ins_count += PCoffset9;
				}
			} else if (instruction[ins_count][6] == '1') { // BRp
				//cout << "BRp" << endl;
				if (condition_code == 1) {
					ins_count += PCoffset9;
				}
			} else { // n, z, p = 0, 0, 0, unconditionally branch
				//cout << "BRnzp" << endl;
				ins_count += PCoffset9; // PC is implemented in "ins_count++"
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
			//cout << "LD: PCoffset9 = " << PCoffset9 << ", ins_count = " << ins_count << endl;
			//cout << "LD: instruction[ins_count + PCoffset9 + 1] = " << instruction[ins_count + PCoffset9 + 1] << endl;
			//cout << "LD: GetNum(instruction[ins_count + PCoffset9 + 1]) = " <<
			//	GetNum(instruction[ins_count + PCoffset9 + 1]) << endl;
			registers[DR_num].SetValue(GetNum(instruction[ins_count + PCoffset9 + 1]));
			break;
		case 3: // ST (0011)
			SR1_num = GetNum(instruction[ins_count].substr(4, 3));
			PCoffset9 = GetNum(instruction[ins_count].substr(7, 9));

			break;
		case 4: // JSR_JSRR (0100)
			if (instruction[ins_count][4] == '1') { // JSR
				PCoffset11 = GetNum(instruction[ins_count].substr(5, 11));
				//cout << "PCoffset11 = " << PCoffset11 << endl;
				registers[7].SetValue(0x7777 + ins_count + 1);
				ins_count += PCoffset11;

			} else { // instruction[ins_count][4] == '0', JSRR
				BaseR = GetNum(instruction[ins_count].substr(7, 3));
				//cout << "BaseR = " << BaseR << endl;
				registers[7].SetValue(0x7777 + ins_count + 1);
				ins_count = registers[BaseR].GetValue(BaseR) - 0x7777 - 1; // No PC
			}
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
			//cout << "LDR: DR_num = " << DR_num << ", BaseR = " << BaseR << ", offset6 = " << offset6 << endl;
			//printf("LDR: R2 value = x%04X\n", registers[BaseR].GetValue(BaseR)); // format print
			//cout << "LDR: instruction[ins_count + registers[BaseR].GetValue(BaseR) + offset6 - 0x7777] = " <<
			//	instruction[ins_count + registers[BaseR].GetValue(BaseR) + offset6 - 0x7777] << endl;
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
			//cout << "LDI: PCoffset9 = " << PCoffset9 << ", ins_count = " << ins_count << endl;
			//cout << "LDI: instruction[ins_count + PCoffset9 + 1] = " << instruction[ins_count + PCoffset9 + 1] << endl;
			//cout << "LDI: GetNum(instruction[ins_count + PCoffset9 + 1]) = " << GetNum(instruction[ins_count + PCoffset9 + 1]) << endl; // Error: 
			//cout << "LDI: strtoull(str.c_str(), NULL, 2) = " << strtoull(instruction[ins_count + PCoffset9 + 1].c_str(), NULL, 2) << endl;
			incre_num = strtoull(instruction[ins_count + PCoffset9 + 1].c_str(), NULL, 2) - 0x7777; // get relative address
			//cout << "LDI: strtoull(str.c_str(), NULL, 2) = " << incre_num << endl; // increment number
			registers[DR_num].SetValue( GetNum( instruction[ins_count + incre_num])); // Load address indirectly
			break;
		case 11: // STI (1011)

			break;
		case 12: // JMP, RET (1100)
			BaseR = GetNum(instruction[ins_count].substr(7, 3));
			//cout << "BaseR = " << BaseR << endl;
			ins_count = ins_count + registers[BaseR].GetValue(BaseR) - 0x7777 - 2;
			//cout << "ins_count = " << ins_count << endl;
			break;
		case 13: // reserved (1101)
			cout << "Reserved, 1101" << endl;
			break;
		case 14: // LEA (1110), load effect address
			DR_num = GetNum(instruction[ins_count].substr(4, 3));
			PCoffset9 = GetNum(instruction[ins_count].substr(7, 9));
			//cout << "LEA: DR_num = " << DR_num << ", PCoffset9 = " << PCoffset9 << endl;
			registers[DR_num].SetValue(0x7777 + ins_count + PCoffset9);
			break;
		case 15:
			PrintOut(registers);
			//cout << "Total number of valid instructions: " << total_count - 1 << endl; // instruction counter, ignoring the empty instruction
			exit(0);
			break;
		default:
			cout << "Invalid instruction" << endl;
			break;
		} // switch

		//cout << "Instruction " << ins_count << ":" << endl;
		//PrintOut(registers);
		//cout << endl;

	} // while




} // main






