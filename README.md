# LC-3 Executor
Course project for Introduction to Computing System (ICS) in Summer, 2022. 

LC-3 Executor is a C++ program that executes LC-3 assembly instructions. It is developed as an assignment for Lab6b of the course Introduction to Computing Systems.

## Author

Minghao Sun 

Contact: b.sun.med@gmail.com

## Version

2.0

## Description

LC-3 Executor is a C++ program that simulates the execution of LC-3 assembly instructions. It provides functionality to execute various instructions, including BR, ADD, LD, ST, JSR/JSRR, AND, LDR, STR, RTI, NOT, LDI, STI, JMP/RET, and LEA.

The program uses a class called `Reg` to represent general-purpose registers (GPR) and condition code registers. The GPRs are initialized with default values and can be modified during the execution of instructions. The condition code registers hold the condition codes based on the results of certain operations.

The main function reads LC-3 instructions from standard input and executes them sequentially. It uses helper functions to parse and interpret different types of instructions.

## Usage

To use the LC-3 Executor program:

1. Compile the source code using a C++ compiler.
2. Run the compiled executable.
3. Enter LC-3 assembly instructions line by line.
4. End input with an empty line.

The program will execute the provided instructions and display relevant output.

## Dependencies

The LC-3 Executor program has the following dependencies:

- C++ compiler
- Standard C++ library

Make sure you have these dependencies installed before compiling and running the program.

## License

This project is licensed under the [MIT License](LICENSE).

