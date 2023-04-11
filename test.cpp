#include <iostream>

int fna(int a);	// Example prototype of a function to be called


int fna(int a){
	return a;
}



int main(){

	int (* const opcode_table[])(int) = {fna};


	opcode_table[0](6);	// Calling method 1
	(*opcode_table[0])(6);	// Calling method 2


	unsigned int fi_n = (0x00ee & 0xF000) == 0;
	unsigned int se_n = (0x00ee & 0x0F00) == 0;
	unsigned int th_n = (0x00ee & 0x00F0) == 0;
	unsigned int fo_n = (0x00ee & 0x000F) == 0;

	std::cout << fi_n << std::endl;
	std::cout << se_n << std::endl;
	std::cout << th_n << std::endl;
	std::cout << fo_n << std::endl;

}