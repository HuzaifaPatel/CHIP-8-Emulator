#include <iostream>

int main(){
	int i = (0xf4 & 0xFF) | ((0x50 & 0x0F) << 8);
	std::cout << i  << std::endl;
}