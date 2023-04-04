#include "chip8.hpp"


Chip8::Chip8() : font{
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
	}{


	screen = new Screen();
	program_counter = ROM_MEMORY_START;

	load_font_in_memory();
}


void Chip8::load_rom(){
	std::ifstream rom("test_rom_opcode.ch8");
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


void Chip8::load_font_in_memory(){
	for(int i = 0; i < FONT_SIZE; i++){
		memory[FONT_STARTING_ADDRESS + i] = font[i];
	}
}


void Chip8::OP_CLS(){
	screen->clear_screen();
}


void Chip8::OP_RET(){
	program_counter = stack[0];
	stack_pointer -= 1;
}


void Chip8::OP_JP(){
	program_counter = opcode & 0xF000;
}


void Chip8::OP_CALL(){
	stack_pointer += 1;
	stack[0] = program_counter;
	program_counter = opcode & 0xF000;
}


void Chip8::OP_3xkk(){
	unsigned int x = (opcode & 0x0F00) >> 8;
	unsigned int kk = opcode & 0x00FF;

	if(registers[x] == kk){
		program_counter += 2;
	}
}


void Chip8::OP_4xkk(){
	unsigned int x = (opcode & 0x0F00) >> 8;
	unsigned int kk = opcode & 0x00FF;

	if(registers[x] != kk){
		program_counter += 2;
	}
}


void Chip8::OP_5xy0(){
	unsigned long x = (opcode & 0x0F00) >> 8;
	unsigned long y = (opcode & 0x00F0) >> 8;

	if(registers[x] == registers[y]){
		program_counter += 2;
	}
}


void Chip8::OP_6xkk(){
	unsigned long x = (opcode & 0x0F00) >> 8;
	registers[x] = opcode & 0x00FF;
}


void Chip8::OP_7xkk(){
	unsigned long x = (opcode & 0x0F00) >> 8;

	registers[x] = registers[x] + (opcode & 0x00FF);
}


void Chip8::OP_8xy0(){
	unsigned long x = (opcode & 0x0F00) >> 8;
	unsigned long y = (opcode & 0x00F0) >> 8;

	registers[x] = registers[y];
}


void Chip8::OP_8xy1(){
	unsigned long x = (opcode & 0x0F00) >> 8;
	unsigned long y = (opcode & 0x00F0) >> 8;

	registers[x] = x | y;
}


void Chip8::OP_8xy2(){
	unsigned long x = (opcode & 0x0F00) >> 8;
	unsigned long y = (opcode & 0x00F0) >> 8;

	registers[x] = x & y;
}


void Chip8::OP_8xy3(){
	unsigned long x = (opcode & 0x0F00) >> 8;
	unsigned long y = (opcode & 0x00F0) >> 8;

	registers[x] = x ^ y;
}


void Chip8::OP_8xy4(){
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
			display[row + x + y + col] = 1;
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





int main(){
	Chip8* chip = new Chip8();
	chip->screen->load_screen();
}