#include "chip8.hpp"


Chip8::Chip8()

	:

	font{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	},

	// order of these matter
	opcode_table{
		&Chip8::OP_0nnn,
		&Chip8::OP_00EE,
		&Chip8::OP_00E0,
		&Chip8::OP_1nnn,
		&Chip8::OP_2nnn,
		&Chip8::OP_3xkk,
		&Chip8::OP_4xkk,
		&Chip8::OP_5xy0,
		&Chip8::OP_6xkk,
		&Chip8::OP_7xkk,
		&Chip8::OP_8xy0,
		&Chip8::OP_8xy1,
		&Chip8::OP_8xy2,
		&Chip8::OP_8xy3,
		&Chip8::OP_8xy4,
		&Chip8::OP_8xy5,
		&Chip8::OP_8xy6,
		&Chip8::OP_8xy7,
		&Chip8::OP_8xyE,
		&Chip8::OP_9xy0,
		&Chip8::OP_Annn,
		&Chip8::OP_Bnnn,
		&Chip8::OP_Cxkk,
		&Chip8::OP_Dxyn,
		&Chip8::OP_Ex9E,
		&Chip8::OP_ExA1,
		&Chip8::OP_Fx07,
		&Chip8::OP_Fx0A,
		&Chip8::OP_Fx15,
		&Chip8::OP_Fx18,
		&Chip8::OP_Fx1E,
		&Chip8::OP_Fx29,
		&Chip8::OP_Fx33,
		&Chip8::OP_Fx55,
		&Chip8::OP_Fx65,
		&Chip8::OP_NULL
	}

{
	screen = new Screen();
	program_counter = ROM_MEMORY_START;
	stack_pointer = 0; // stack pointer should start at top.
	load_font();

}


void Chip8::load_rom(){
	std::ifstream rom(ROM);
	int rom_size = 0;

	if(rom.is_open()){

		// get length of rom
		rom.seekg(0, rom.end);
		rom_size = (int)rom.tellg();
		rom.seekg(0, rom.beg);

		char* rom_content = new char[rom_size];

		rom.read(rom_content, rom_size);
		rom.close();

		for(int i = 0; i < rom_size; i++){
			memory[ROM_MEMORY_START + i] = rom_content[i];
		}

		delete[] rom_content;
	}
}


void Chip8::load_font(){
	for(int i = 0; i < FONT_SIZE; i++){
		memory[FONT_STARTING_ADDRESS + i] = font[i];
	}
}



const uint8_t Chip8::fi_nibble() const {return (opcode & 0xF000) >> 12;}
const uint8_t Chip8::se_nibble() const {return (opcode & 0x0F00) >> 8;}
const uint8_t Chip8::th_nibble() const {return (opcode & 0x00F0) >> 4;}
const uint8_t Chip8::fo_nibble() const {return opcode & 0x000F;}





void Chip8::cycle(){
	opcode = memory[program_counter] << 8 | memory[program_counter + 1];
	program_counter +=2;
}


void Chip8::execute_opcode(){
	uint8_t fi_n = fi_nibble();
	uint8_t se_n = se_nibble();
	uint8_t th_n = th_nibble();
	uint8_t fo_n = fo_nibble();

	std::cout << std::hex << fi_n << std::endl;

	// one - three opcode inclusive
	if(fi_n == 0x0){
		(this->*opcode_table[(fi_n == 0x0) + (se_n == 0x0) + (th_n == 0x0) + (fo_n == 0x0) - 1])();
		return;
	}


	// four - ten opcode	
	if(fi_n > 0x0 || fi_n < 0x8){
		(this->*opcode_table[fi_n + 2])();
		return;
	}


	// nineteen
	// if(fi_n == 0x8 && fo_n == 0xE){
	// 	(this->*opcode_table[0xF + 2])();
	// 	return;
	// }


	// eleven - eighteen
	// if(fi_n == 0x8){
	// 	(this->*opcode_table[fi_n + 10])();
	// 	return;
	// }


	// if(fi_n > 0x9 || fi_n < 0xE){

	// }


}



void Chip8::OP_0nnn(){
	std::cout << "OP_0nnn" << std::endl;
}


void Chip8::OP_00E0(){
	std::cout << "OP_00E0" << std::endl;
	screen->clear_screen();
}


void Chip8::OP_00EE(){ // GOOD
	std::cout << "OP_00EE" << std::endl;
	program_counter = stack[--stack_pointer];
}


void Chip8::OP_1nnn(){ // GOOD
	std::cout << "OP_1nnn" << std::endl;
	program_counter = opcode & 0x0FFF;
}


void Chip8::OP_2nnn(){ // GOOD
	std::cout << "OP_2nnn" << std::endl;
	stack[stack_pointer++] = program_counter;
	program_counter = opcode & 0x0FFF;
}


void Chip8::OP_3xkk(){ // GOOD
	std::cout << "OP_3xkk" << std::endl;
	if(registers[se_nibble()] == (opcode & 0x00FF))
		program_counter += 2;
}


void Chip8::OP_4xkk(){ // GOOD
	std::cout << "OP_4xkk" << std::endl;
	if(registers[se_nibble()] != (opcode & 0x00FF))
		program_counter += 2;
}


void Chip8::OP_5xy0(){ // GOOD
	std::cout << "OP_5xy0" << std::endl;
	if(registers[se_nibble()] == registers[th_nibble()])
		program_counter += 2;
}


void Chip8::OP_6xkk(){ // GOOD
	std::cout << "OP_6xkk" << std::endl;
	registers[se_nibble()] = opcode & 0x00FF;
}


void Chip8::OP_7xkk(){ // GOOD
	std::cout << "OP_7xkk" << std::endl;
	registers[se_nibble()] += opcode & 0x00FF;
}


void Chip8::OP_8xy0(){
	std::cout << "OP_8xy0" << std::endl;
	unsigned long x = (opcode & 0x0F00) >> 8;
	unsigned long y = (opcode & 0x00F0) >> 8;

	registers[x] = registers[y];
}



void Chip8::OP_8xy1(){
	std::cout << "OP_8xy1" << std::endl;
	unsigned long x = (opcode & 0x0F00) >> 8;
	unsigned long y = (opcode & 0x00F0) >> 8;

	registers[x] = x | y;
}


void Chip8::OP_8xy2(){
	std::cout << "OP_8xy2" << std::endl;
	unsigned long x = (opcode & 0x0F00) >> 8;
	unsigned long y = (opcode & 0x00F0) >> 8;

	registers[x] = x & y;
}


void Chip8::OP_8xy3(){
	std::cout << "OP_8xy3" << std::endl;
	unsigned long x = (opcode & 0x0F00) >> 8;
	unsigned long y = (opcode & 0x00F0) >> 8;

	registers[x] = x ^ y;
}


void Chip8::OP_8xy4(){
	std::cout << "OP_8xy4" << std::endl;
	unsigned long x = (opcode & 0x0F00) >> 8;
	unsigned long y = (opcode & 0x00F0) >> 8;

	registers[x] = registers[x] + registers[y];

	if(registers[x] > 0xFF){
		registers[15] = 1;
	}else{
		registers[15] = 0;
	}
}


void Chip8::OP_8xy5(){
	std::cout << "OP_8xy5" << std::endl;
	unsigned long x = (opcode & 0x0F00) >> 8;
	unsigned long y = (opcode & 0x00F0) >> 8;

	registers[x] = registers[x] - registers[y];

	if(registers[x] > registers[y]){
		registers[15] = 1;
	}else{
		registers[15] = 0;
	}
}


void Chip8::OP_8xy6(){
	std::cout << "OP_8xy6" << std::endl;
	unsigned long x = opcode & 0x0001;

	if(x){
		registers[15] = 1;
	}else{
		registers[15] = 0;
	}

	x = (opcode & 0x0F00) >> 8;

	registers[x] = registers[x] / 2;	
}


void Chip8::OP_8xy7(){
	std::cout << "OP_8xy7" << std::endl;
	unsigned long x = (opcode & 0x0F00) >> 8;
	unsigned long y = (opcode & 0x00F0) >> 8;

	registers[x] = registers[y] - registers[x];

	if(y > x){
		registers[15] = 1;
	}else{
		registers[15] = 0;
	}
}


void Chip8::OP_8xyE(){
	unsigned long x = opcode & 0x8000;

	if(x){
		registers[15] = 1;
	}else{
		registers[15] = 0;
	}

	x = (opcode & 0x0F00) >> 8;

	registers[x] *= 2;
}


void Chip8::OP_9xy0(){
	unsigned long x = (opcode & 0x0F00) >> 8;
	unsigned long y = (opcode & 0x00F0) >> 8;

	if(x != y){
		program_counter += 2;
	}
}

void Chip8::OP_Annn(){
	unsigned long nnn = opcode & 0x0FFF;

	index_register = nnn;
}


void Chip8::OP_Bnnn(){
	unsigned long nnn = opcode & 0x0FFF;

	program_counter = nnn + registers[0];
}


void Chip8::OP_Cxkk(){
	unsigned long x = (opcode & 0x0F00) >> 8;
	unsigned int kk = opcode & 0x00FF;

	registers[x] = (rand() % 255) & kk;
}

void Chip8::OP_Dxyn(){
	unsigned long Vx = (opcode & 0x0F00) >> 8;
	unsigned long Vy = (opcode & 0x00F0) >> 8;
	unsigned long x = registers[Vx];
	unsigned long y = registers[Vy];
	unsigned long n = (opcode & 0x000F);
	uint16_t temp_index_register = index_register;

	for(int row = 0; row < n; row++){
		temp_index_register += row;

		for(int col = 0; col < 8; col++){
			display[row + col] = 1;
		}
	}

}



void Chip8::OP_Ex9E(){
	unsigned long x = (opcode & 0x0F00) >> 8;

	if(registers[x] == screen->checkKey()){
		program_counter += 2;
	}
}


void Chip8::OP_ExA1(){
	unsigned long x = (opcode & 0x0F00) >> 8;

	if(registers[x] != screen->checkKey()){
		program_counter += 2;
	}
}



void Chip8::OP_Fx07(){

}


void Chip8::OP_Fx0A(){
	unsigned long x = (opcode & 0x0F00) >> 8;
	
	registers[x] = screen->checkKey();
}


void Chip8::OP_Fx15(){

}


void Chip8::OP_Fx18(){

}


void Chip8::OP_Fx1E(){
	unsigned long x = (opcode & 0x0F00) >> 8;

	index_register += x;
}


void Chip8::OP_Fx29(){
	unsigned long x = (opcode & 0x0F00) >> 8;

	for(int i = 0; i < FONT_SIZE; i++){
		if(memory[FONT_STARTING_ADDRESS + i] == x){
			index_register = FONT_STARTING_ADDRESS + i;
			break;
		}
	}
}


void Chip8::OP_Fx33(){
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t value = registers[Vx];

	// Ones-place
	memory[index_register + 2] = value % 10;
	value /= 10;

	// Tens-place
	memory[index_register + 1] = value % 10;
	value /= 10;

	// Hundreds-place
	memory[index_register] = value % 10;
}


void Chip8::OP_Fx55(){
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;

	for(int i = 0; i < 16; i++){
		memory[index_register + i] = registers[i]; 
	}
}


void Chip8::OP_Fx65(){
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;

	for (uint8_t i = 0; i <= Vx; ++i)
	{
		registers[i] = memory[index_register + i];
	}
}






void Chip8::OP_NULL(){

}


void Chip8::test(){
	for(int i = 0; i < 16; i++){
		printf("REGISTERS %2d : %x\n",i, registers[i]);
	}

	for(int i = 0; i < 16; i++){
		printf("STACK %2d : %x\n",i, stack[i]);
	}


	printf("STACK POINTER: %x\n", stack_pointer);

	printf("PROGRAM COUNTER: %x\n", program_counter);
}