
/**
* @name LC-3 Executor
*
* @file LC-3_Executor.cpp
* @version 2.0
*
* @brief This file includes the LC-3 executor assignment for Lab6b
* of the course Introduction to Computing Systems
*
* @author Minghao Sun (Student ID: 3180100729)
* Contact: b.sun.med@gmail.com
*
*/

#include <iostream>
#include <string>
#include <cmath>

#define MAX_INSTRUCTION_SIZE 0x00FF // Maximal instruction size shouldn't be so large in case of stack overflow.
#define DEFAULT_MEMORY 0x7777


class Reg {
public:
	Reg(uint16_t register_number, uint16_t register_value); // constructor
	uint16_t SetValue(uint16_t value);
	uint16_t GetValue();
	void PrintOutGPR(); // Print values of all general purpose registers.
	void PrintOutCon(); // Print values of three single-bit condition code registers.
	void SetConditionCode(uint16_t gpr_value);
	void ClearConditionCode();
	uint16_t GetConditionCode(char ch);

private:
	uint16_t reg_number; // register identifier for GPR or single-bit condition code registers, uint8_t also works.
	uint16_t reg_value; // fixed 16-bit unsigned integer type
};

// General purpose register (GPR) objects constructor
Reg gpr_reg[8] = {
	Reg(0, 0x7777),
	Reg(1, 0x7777),
	Reg(2, 0x7777),
	Reg(3, 0x7777),
	Reg(4, 0x7777),
	Reg(5, 0x7777),
	Reg(6, 0x7777),
	Reg(7, 0x7777)
};

// Condition code single-bit registers. Their value will be set as 0x0001 if the situation is set.
Reg condition_reg[3] = {
	Reg(0, 0x0000), // N, condition_reg[0], condition code - 0x0000 / 0x0001
	Reg(1, 0x0000), // Z, condition_reg[1], condition code
	Reg(2, 0x0000)  // P, condition_reg[2], condition code
};

void Reg::SetConditionCode(uint16_t DR_value) {
	int16_t DR_value_signed = DR_value;
	printf("Unsigned DR value = x%04X, signed DR value = %d.\n", DR_value, DR_value_signed);
	if (DR_value_signed < 0) { // N
		std::cout << "condition code = N" << std::endl;
		condition_reg[0].SetValue(0x0001);
	} else if (DR_value_signed == 0) { // Z
		std::cout << "condition code = Z" << std::endl;
		condition_reg[1].SetValue(0x0001);
	} else { // P
		std::cout << "condition code = P" << std::endl;
		condition_reg[2].SetValue(0x0001);
	}
}

// Clear three single-bit condition code before setting new condition codes for each new instruction.
void Reg::ClearConditionCode() {
	for (int i = 0; i < 3; i++) {
		condition_reg[i].SetValue(0x0000);
	}
}

uint16_t Reg::GetConditionCode(char ch) {
	if (ch == 'N') {
		return 0x0000;
	} else if (ch == 'Z') {
		return 0x0001;
	} else if (ch == 'P') {
		return 0x0002;
	} else {
		return 0x0003; // not defined
	}
}

Reg::Reg(uint16_t register_number, uint16_t register_value) {
	reg_number = register_number;
	reg_value = register_value;
}

uint16_t Reg::SetValue(uint16_t value) {
	reg_value = value;
	return reg_value;
}

uint16_t Reg::GetValue() {
	return reg_value;
}

void Reg::PrintOutGPR() {
	for (int i = 0; i < 8; i++) {
		printf("R%d = x%04hX\n", i, gpr_reg[i].GetValue());
	}
}

void Reg::PrintOutCon() {
	std::cout << "Condition code registers:" << std::endl;
	for (int i = 0; i < 3; i++) {
		printf("R%d = x%04hX\n", i, condition_reg[i].GetValue());
	}
	std::cout << std::endl;
}

uint16_t OpcodeHash(std::string instruction) {
	uint16_t sum_hash = 0;
	for (uint16_t i = 0; i < 4; i++) { // Get the number of bit[15:12] to specify the opcode
		sum_hash += (uint16_t)((instruction[i] - '0') * pow(2, 3 - i));
	}
	return sum_hash;
}

std::string SEXT(std::string str) {
	std::string SEXT_str = str;
	for (int i = 0; i < 16 - str.length(); i++) {
		SEXT_str = str[0] + SEXT_str;
	}
	return SEXT_str;
}

uint16_t GetNum(std::string str) {
	uint16_t sum_num = 0;
	for (int i = 0; i < str.length(); i++) {
		sum_num += (uint16_t)((str[i] - '0') * pow(2, str.length() - 1 - i));
	}
	return sum_num;
}

uint16_t StringToUnsigned(std::string instr) {
	uint16_t sum_num = 0;

	return 0x0001;

}

int main() {
	//std::cout << "Hello, LC-3 executor!" << std::endl;

	uint16_t DR_num = 0x0000;
	uint16_t SR1_num = 0x0000;
	uint16_t SR2_num = 0x0000;
	uint16_t BaseR_num = 0x0000; // 

	uint16_t imm5 = 0x0000; // unsigned, SEXT
	uint16_t offset6 = 0x0000; // unsigned, SEXT
	uint16_t offset9 = 0x0000; // unsigned, SEXT
	uint16_t offset11 = 0x0000; // unsigned, SEXT
	uint16_t PCoffset9 = 0x0000;
	uint16_t PCoffset11 = 0x0000;

	uint16_t PC = DEFAULT_MEMORY; // PC indicates the address of the next instruction to be executed.
	uint16_t temp_PC = DEFAULT_MEMORY; // Default value of the memory locations is 0x7777.

	std::string instr[MAX_INSTRUCTION_SIZE]; // LC-3 memory address space = 2^16 (addressibility = 16 bits)


	uint16_t instr_count = 0x0000;
	uint16_t instr_count_total = 0x0000;

	//std::cout << SEXT("101010") << " " << SEXT("001100110") << std::endl; // SEXT test
	//std::cout << "array_index = " << array_index << ", PC - 0x0001 - DEFAULT_MEMORY = " << PC - 0x0001 - DEFAULT_MEMORY << std::endl;

	// Read all the instructions
	// Input should be ended with an empty line rather than HALT	
	while (1) {
		PC = PC + 0x0001; // In FETCH phase, state 2.
		getline(std::cin, instr[PC - 0x0001 - DEFAULT_MEMORY]); // array index = PC - 0x0001 - DEFAULT_MEMORY
		if (instr[PC - 0x0001 - DEFAULT_MEMORY] == "") { // for this part, don't use array_index, or you will get stack overflowed.
			instr_count_total = PC - DEFAULT_MEMORY - 0x0001;
			break;
		}
	}

	PC = DEFAULT_MEMORY;
	while (PC - 0x0001 - DEFAULT_MEMORY < instr_count_total) {
		PC = PC + 0x0001; // After here, we can use array_index.
		uint16_t array_index = PC - 0x0001 - DEFAULT_MEMORY;
		switch (OpcodeHash(instr[array_index])) {
		case 0: // BR (0000)
			std::cout << "BR:" << std::endl;
			offset9 = GetNum(SEXT(instr[array_index].substr(7, 9)));
			//printf("offset9 = x%04X\n", offset9);
			//std::cout << "instr[array_index] = " << instr[array_index] << std::endl;
			PCoffset9 = offset9 + PC; // the address of the next instruction to be executed
			
			// trace back to find the last conditional code
			// BR n z p
			if (instr[array_index][4] == '1') { // BRn
				std::cout << "BRn" << std::endl;
				if (condition_reg[0].GetValue() == 0x0001) { // condition code register N: condition_reg[0]
					PC = PC + offset9; 
				}
			}
			else if (instr[array_index][5] == '1') { // BRz
			 //cout << "BRz" << endl;
				if (condition_reg[1].GetValue() == 0x0001) {
					PC = PC + offset9;
				}
			}
			else if (instr[array_index][6] == '1') { // BRp
			 //cout << "BRp" << endl;
				if (condition_reg[2].GetValue() == 0x0001) {
					PC = PC + offset9;
				}
			}
			else { // n, z, p = 0, 0, 0, unconditionally branch
			 //cout << "BRnzp" << endl;
				PC = PC + offset9;
			}

			break;
		case 1: // ADD (0001)
			std::cout << "ADD:" << std::endl;
			DR_num = GetNum(instr[array_index].substr(4, 3));
			SR1_num = GetNum(instr[array_index].substr(7, 3));

			if (instr[array_index][10] == '1') { // if str[10] == '1'
				imm5 = GetNum(SEXT(instr[array_index].substr(11, 5))); // imm5 SEXT
				//std::cout << instr[array_index].substr(11, 5) << " " << SEXT(instr[array_index].substr(11, 5)) << std::endl;
				//printf("imm5 = x%04X\n", imm5);
				gpr_reg[DR_num].SetValue(gpr_reg[SR1_num].GetValue() + imm5); // SEXT + imm5
			}
			else { // str[10] == '0'
				SR2_num = GetNum(instr[array_index].substr(13, 3));
				gpr_reg[DR_num].SetValue(gpr_reg[SR1_num].GetValue() + gpr_reg[SR2_num].GetValue());
			}
			// Set condition code
			condition_reg[0].ClearConditionCode();
			condition_reg[0].SetConditionCode(gpr_reg[DR_num].GetValue());
			condition_reg[0].PrintOutCon();
			break;
		case 2: // LD (0010)
			std::cout << "LD:" << std::endl;
			DR_num = GetNum(instr[array_index].substr(4, 3));
			offset9 = GetNum(SEXT(instr[array_index].substr(7, 9)));
			PCoffset9 = PC + offset9;
			//cout << "LD: PCoffset9 = " << PCoffset9 << ", ins_count = " << ins_count << endl;
			//cout << "LD: instruction[ins_count + PCoffset9 + 1] = " << instruction[ins_count + PCoffset9 + 1] << endl;
			//cout << "LD: GetNum(instruction[ins_count + PCoffset9 + 1]) = " <<
			//	GetNum(instruction[ins_count + PCoffset9 + 1]) << endl;
			gpr_reg[DR_num].SetValue(strtoull(instr[PCoffset9 - DEFAULT_MEMORY].c_str(), NULL, 2)); // Convert the string to an unsigned int and set its value.
			break;
		case 3: // ST (0011)
			std::cout << "ST:" << std::endl;
			//SR1_num = GetNum(instruction[ins_count].substr(4, 3));
			//PCoffset9 = GetNum(instruction[ins_count].substr(7, 9));

			break;
		case 4: // JSR_JSRR (0100)
			std::cout << "JSR_JSRR:" << std::endl;

			if (instr[array_index][4] == '1') { // JSR
				offset11 = GetNum(SEXT(instr[array_index].substr(5, 11)));
				gpr_reg[7].SetValue(array_index + DEFAULT_MEMORY + 0x0001); // put the address of the instruction following JSR into R7
				PC = PC + offset11; // jump to PCoffset11
			}
			else { // instr[array_index][4] == '0', JSRR
				BaseR_num = GetNum(instr[array_index].substr(7, 3));
				//cout << "BaseR = " << BaseR << endl;
				gpr_reg[7].SetValue(array_index + DEFAULT_MEMORY + 0x0001);
				PC = gpr_reg[BaseR_num].GetValue(); // jump to the address contained in PC (value in BaseR)
			}
			break;
		case 5: // AND (0101)
			std::cout << "AND" << std::endl;
			DR_num = GetNum(instr[array_index].substr(4, 3));
			SR1_num = GetNum(instr[array_index].substr(7, 3));

			if (instr[array_index][10] == '1') { // if str[10] == '1'
				imm5 = GetNum(SEXT(instr[array_index].substr(11, 5))); // imm5 SEXT
				//std::cout << instr[array_index].substr(11, 5) << " " << SEXT(instr[array_index].substr(11, 5)) << std::endl;
				//printf("imm5 = x%04X\n", imm5);
				gpr_reg[DR_num].SetValue(gpr_reg[SR1_num].GetValue() + imm5); // SEXT + imm5
			}
			else { // str[10] == '0'
				SR2_num = GetNum(instr[array_index].substr(13, 3));
				gpr_reg[DR_num].SetValue(gpr_reg[SR1_num].GetValue() & gpr_reg[SR2_num].GetValue()); // bit-wise AND operation
			}

			condition_reg[0].ClearConditionCode();
			condition_reg[0].SetConditionCode(gpr_reg[DR_num].GetValue());
			condition_reg[0].PrintOutCon();
			break;
		case 6: // LDR (0110)
			std::cout << "LDR" << std::endl;
			DR_num = GetNum(instr[array_index].substr(4, 3));
			offset6 = GetNum(SEXT(instr[array_index].substr(10, 6)));
			BaseR_num = GetNum(instr[array_index].substr(7, 3));

			//std::cout << "LDR: DR_num = " << DR_num << ", offset6 = ";
			//printf("x%04X", offset6);
			//std::cout << ", BaseR_num = " << BaseR_num << std::endl;
			//std::cout << "LDR: instr = " << instr[gpr_reg[BaseR_num].GetValue() + offset6 - DEFAULT_MEMORY] << std::endl;
			//std::cout << "LDR: strtoull = " << strtoull(instr[gpr_reg[BaseR_num].GetValue() + offset6 - DEFAULT_MEMORY].c_str(), NULL, 2) << std::endl;
			gpr_reg[DR_num].SetValue(strtoull(instr[gpr_reg[BaseR_num].GetValue() + offset6 - DEFAULT_MEMORY].c_str(), NULL, 2));
			break;
		case 7: // STR (0111)
			std::cout << "STR:" << std::endl;

			break;
		case 8: // RTI (1101)
			std::cout << "RTI(1101) is not required" << std::endl;
			break;
		case 9: // NOT (1001)
			std::cout << "NOT:" << std::endl;
			DR_num = GetNum(instr[array_index].substr(4, 3));
			SR1_num = GetNum(instr[array_index].substr(7, 3));
			gpr_reg[DR_num].SetValue(~gpr_reg[SR1_num].GetValue());

			condition_reg[0].ClearConditionCode();
			condition_reg[0].SetConditionCode(gpr_reg[DR_num].GetValue());
			condition_reg[0].PrintOutCon();
			break;
		case 10: // LDI (1010)
			std::cout << "LDI:" << std::endl;
			DR_num = GetNum(instr[array_index].substr(4, 3));
			offset9 = GetNum(SEXT(instr[array_index].substr(7, 9)));
			PCoffset9 = PC + offset9; 

			gpr_reg[DR_num].SetValue(strtoull(instr[strtoull(instr[PCoffset9 - DEFAULT_MEMORY].c_str(), NULL, 2)
				- DEFAULT_MEMORY].c_str(), NULL, 2));
			break;
		case 11: // STI (1011)
			std::cout << "STI:" << std::endl;

			break;
		case 12: // JMP, RET (1100)
			std::cout << "JMP, RET:" << std::endl;
			BaseR_num = GetNum(instr[array_index].substr(7, 3));
			//std::cout << "BaseR = " << BaseR_num << std::endl;
			//printf("JMP: PC = x%04X, gpr_reg[BaseR_num].GetValue() = x%04X\n", PC, gpr_reg[BaseR_num].GetValue());
			PC = gpr_reg[BaseR_num].GetValue();
			//printf("JMP: PC = x%04X\n", PC);
			break;
		case 13: // reserved (1101)
			std::cout << "Reserved, 1101" << std::endl;
			break;
		case 14: // LEA (1110), load effect address
			std::cout << "LEA:" << std::endl;
			DR_num = GetNum(instr[array_index].substr(4, 3));
			offset9 = GetNum(SEXT(instr[array_index].substr(7, 9)));
			PCoffset9 = PC + offset9;
			printf("DR_num = %d, offset9 = x%04X, PCoffset9 = x%04X\n", DR_num, offset9, PCoffset9);
			gpr_reg[DR_num].SetValue(PCoffset9);
			break;
		case 15:
			gpr_reg[0].PrintOutGPR();
			condition_reg[0].PrintOutCon();
			std::cout << "Total number of instructions = " << instr_count_total << std::endl;
			exit(0);
			break;
		default:
			std::cout << "Invalid instruction" << std::endl;
			break;

		} // switch

	} // while





} // main
















