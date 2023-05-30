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
		&Chip8::OP_00EE,
		&Chip8::OP_00E0,
		&Chip8::OP_0nnn,
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
		&Chip8::OP_Fx65
	}

{
	screen = new Screen();
	program_counter = ROM_MEMORY_START;
	stack_pointer = 0; // stack pointer should start at top.
	load_font();

}


void Chip8::load_rom(){
	std::ifstream rom(ROM, std::ios_base::binary);
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
			memory[ROM_MEMORY_START + i] =  rom_content[i];
			// std::cout << std::hex << rom_content[i] << std::endl;
		}

		delete[] rom_content;
	}else{
		std::cout << "ERROR" << std::endl;
		exit(1);
	}
}


void Chip8::load_font(){
	for(int i = 0; i < FONT_SIZE; i++){
		memory[FONT_STARTING_ADDRESS + i] = font[i];
	}
}



const uint8_t Chip8::fi_nibble() const {return (this->opcode & 0xF000) >> 12;}
const uint8_t Chip8::se_nibble() const {return (this->opcode & 0x0F00) >> 8;}
const uint8_t Chip8::th_nibble() const {return (this->opcode & 0x00F0) >> 4;}
const uint8_t Chip8::fo_nibble() const {return this->opcode & 0x000F;}





void Chip8::cycle(){
	this->opcode = (memory[program_counter] << 8) | memory[program_counter + 1];
	this->program_counter += 2;

	if (delay_timer > 0){
		--delay_timer;
	}
}


void Chip8::execute_opcode(){
	int fi_n = fi_nibble();
	int se_n = se_nibble();
	int th_n = th_nibble();
	int fo_n = fo_nibble();

	// if(opcode == 0x00){
	// 	exit(1);
	// }

	
	if(fi_n == 0x00 && se_n == 0x00 && th_n == 0xE && fo_n == 0xE){
		(this->*opcode_table[0])();
	}


	if(fi_n == 0x00 && se_n == 0x00 && th_n == 0xE && fo_n == 0x0){
		(this->*opcode_table[1])();
	}

	if(fi_n == 0x00){
		(this->*opcode_table[2])();
	}


	// three - nine opcode
	if(fi_n > 0x00 && fi_n < 0x8){
		(this->*opcode_table[fi_n + 2])();
		return;
	}


	if(fi_n == 0x8 && fo_n == 0x0){
		(this->*opcode_table[10])();
		return;
	}


	if(fi_n == 0x8 && fo_n == 0x1){
		(this->*opcode_table[11])();
		return;
	}


	if(fi_n == 0x8 && fo_n == 0x2){
		(this->*opcode_table[12])();
		return;
	}



	if(fi_n == 0x8 && fo_n == 0x3){
		(this->*opcode_table[13])();
		return;
	}


	if(fi_n == 0x8 && fo_n == 0x4){
		(this->*opcode_table[14])();
		return;
	}
	

	if(fi_n == 0x8 && fo_n == 0x5){
		(this->*opcode_table[15])();
		return;
	}


	if(fi_n == 0x8 && fo_n == 0x6){
		(this->*opcode_table[16])();
		return;
	}


	if(fi_n == 0x8 && fo_n == 0x7){
		(this->*opcode_table[17])();
		return;
	}


	if(fi_n == 0x08 && fo_n == 0xE){
		(this->*opcode_table[18])();
		return;
	}



	if(fi_n == 0x09){
		(this->*opcode_table[19])();
		return;
	}


	if(fi_n == 0x0A){
		(this->*opcode_table[20])();
		return;	
	}


	if(fi_n == 0x0B){
		(this->*opcode_table[21])();
		return;	
	}


	if(fi_n == 0x0C){
		(this->*opcode_table[22])();
		return;	
	}


	if(fi_n == 0x0D){
		(this->*opcode_table[23])();
		return;	
	}


	if(fi_n == 0x0E && fo_n == 0x0E){
		(this->*opcode_table[24])();
		return;	
	}


	if(fi_n == 0x0E && fo_n == 0x01){
		(this->*opcode_table[25])();
		return;	
	}


	if(fi_n == 0x0F && fo_n == 0x07){
		(this->*opcode_table[26])();
		return;	
	}


	if(fi_n == 0x0F && fo_n == 0x0A){
		(this->*opcode_table[27])();
		return;	
	}



	if(fi_n == 0x0F && th_n == 0x01 && fo_n == 0x05){
		(this->*opcode_table[28])();
		return;	
	}


	if(fi_n == 0x0F && fo_n == 0x08){
		(this->*opcode_table[29])();
		return;	
	}


	if(fi_n == 0x0F && fo_n == 0x0E){
		(this->*opcode_table[30])();
		return;	
	}



	if(fi_n == 0x0F && fo_n == 0x09){
		(this->*opcode_table[31])();
		return;	
	}



	if(fi_n == 0x0F && fo_n == 0x03){
		(this->*opcode_table[32])();
		return;	
	}



	if(fi_n == 0x0F && th_n == 0x05 & fo_n == 0x05){
		(this->*opcode_table[33])();
		return;	
	}



	if(fi_n == 0x0F && th_n == 0x06 & fo_n == 0x05){
		(this->*opcode_table[34])();
		return;	
	}
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
	// std::cout << "OP_1nnn" << std::endl;
	unsigned long old_opcode = memory[program_counter] << 8 | memory[program_counter + 1];
	program_counter = opcode & 0x0FFF;

	// if((memory[program_counter] << 8 | memory[program_counter + 1]) == old_opcode){
	// 	exit(1);
	// }
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


void Chip8::OP_8xy0(){ // GOOD
	std::cout << "OP_8xy0" << std::endl;
	registers[se_nibble()] = registers[th_nibble()];
}



void Chip8::OP_8xy1(){ // GOOD
	std::cout << "OP_8xy1" << std::endl;
	uint8_t x = (opcode & 0x0F00) >> 8;
	uint8_t y = (opcode & 0x00F0) >> 4;

	registers[x] |= registers[y];
}


void Chip8::OP_8xy2(){ // GOOD
	std::cout << "OP_8xy2" << std::endl;
	uint8_t x = (opcode & 0x0F00) >> 8;
	uint8_t y = (opcode & 0x00F0) >> 4;

	registers[x] &= registers[y];
}


void Chip8::OP_8xy3(){ // GOOD
	std::cout << "OP_8xy3" << std::endl;
	uint8_t x = (opcode & 0x0F00) >> 8;
	uint8_t y = (opcode & 0x00F0) >> 4;

	registers[x] ^= registers[y];
}


void Chip8::OP_8xy4(){ // GOOD
	std::cout << "OP_8xy4" << std::endl;
	uint8_t x = (opcode & 0x0F00) >> 8;
	uint8_t y = (opcode & 0x00F0) >> 4;
	uint16_t temp = (uint16_t)registers[x] + (uint16_t)registers[y];

	registers[x] = temp;

	if(temp > 0xFF){	
		registers[0xF] = 1;
	}else{
		registers[0xF] = 0;
	}
}


void Chip8::OP_8xy5(){ // GOOD
	std::cout << "OP_8xy5" << std::endl;
	uint8_t x = (opcode & 0x0F00) >> 8;
	uint8_t y = (opcode & 0x00F0) >> 4;
	uint8_t temp = registers[x];

	registers[x] -= registers[y];

	if(temp > registers[y]){
		registers[0xF] = 1;
	}else{
		registers[0xF] = 0;
	}
}


void Chip8::OP_8xy6(){ // GOOD
	std::cout << "OP_8xy6" << std::endl;
	uint8_t x = opcode & 0x0F00 >> 8;
	uint8_t temp = registers[x];
	
	registers[x] >>= 1;

	if(temp & 0x01){
		registers[0xF] = 1;
	}else{
		registers[0xF] = 0;
	}
}


void Chip8::OP_8xy7(){ // GOOD
	std::cout << "OP_8xy7" << std::endl;
	uint8_t x = (opcode & 0x0F00) >> 8;
	uint8_t y = (opcode & 0x00F0) >> 4;
	uint16_t temp = registers[x];

	registers[x] = registers[y] - registers[x];

	if(registers[y] > temp){
		registers[0xF] = 1;
	}else{
		registers[0xF] = 0;
	}

}


void Chip8::OP_8xyE(){ // GOOD
    uint8_t carry = registers[(opcode >> 8) & 0xF] >> 7;
    registers[(opcode >> 8) & 0xF] <<= 1;
    registers[0xF] = carry;
}


void Chip8::OP_9xy0(){ // GOOD
	std::cout << "OP_9xy0" << std::endl;
	uint8_t x = (opcode & 0x0F00) >> 8;
	uint8_t y = (opcode & 0x00F0) >> 4;

	if(registers[x] != registers[y]){
		program_counter += 2;
	}
}


void Chip8::OP_Annn(){ // GOOD
	std::cout << "OP_ANNN" << std::endl;
	unsigned long nnn = opcode & 0x0FFF;

	index_register = nnn;
}


void Chip8::OP_Bnnn(){ // GOOD
	std::cout << "OP_Bnnn" << std::endl;
	uint32_t nnn = opcode & 0x0FFF;

	program_counter = nnn + registers[0];
}


void Chip8::OP_Cxkk(){ // GOOD
	std::cout << "OP_Cxkk" << std::endl;
	uint8_t x = (opcode & 0x0F00) >> 8;
	uint16_t kk = opcode & 0x00FF;

	registers[x] = (rand() % 255) & kk;
}


void Chip8::OP_Dxyn(){
	std::cout << "OP_Dxyn" << std::endl;
	uint8_t x = registers[(opcode & 0x0F00) >> 8] % WIDTH;
	uint8_t y = registers[(opcode & 0x00F0) >> 4] % HEIGHT;
	unsigned long num_bytes = opcode & 0x000F;

	for(unsigned long row = 0; row < num_bytes; row++){

		uint8_t spriteByte = memory[index_register + row];

		for(unsigned long col = 0; col < 8; col++){
			uint32_t sprite_pixel = spriteByte & (0x80 >> col);
			uint32_t* pixel_on_screen = &display[(y + row) * WIDTH + (col + x)];

            if(sprite_pixel){
                if(*pixel_on_screen == 0x0) {
                    *pixel_on_screen = 0xFFFFFFFF;
                }
                else {
                    *pixel_on_screen = 0x00000000;
                     registers[0xF] = 1;
                }
            }
		}
	}
}



void Chip8::OP_Ex9E(){ // GOOD
	std::cout << "OP_Ex9E" << std::endl;
	uint8_t x = (opcode & 0x0F00) >> 8;
	bool key_pressed = false;

	for(uint8_t key = 0; key < NUM_INPUT_KEYS; key++){
		if(input_keys[key] && registers[x] == key_pressed){
			key_pressed = true;
		}
	}

	if(key_pressed){
		program_counter += 2;
	}
}


void Chip8::OP_ExA1(){ // GOOD
	std::cout << "OP_ExA1" << std::endl;
	uint8_t x = (opcode & 0x0F00) >> 8;
	bool key_pressed = false;

	for(uint8_t key = 0; key < NUM_INPUT_KEYS; key++){
		if(input_keys[key] && registers[x] == key_pressed){
			key_pressed = true;
		}
	}

	if(!key_pressed){
		program_counter += 2;
	}
}



void Chip8::OP_Fx07(){ // GOOD
	std::cout << "OP_Fx07" << std::endl;
	uint8_t x = (opcode & 0x0F00) >> 8;

	registers[x] = this->delay_timer;
}


void Chip8::OP_Fx0A(){ // GOOD
	std::cout << "OP_Fx0A" << std::endl;
	uint8_t x = (opcode & 0x0F00) >> 8;
	uint8_t key_pressed = 0;

	for(uint8_t key = 0; key < NUM_INPUT_KEYS; key++){
		if(input_keys[key]){
			registers[x] = input_keys[key];
			key_pressed = input_keys[key];
			break;
		}
	}

	if(!key_pressed){
		program_counter -= 2;
	}else{
		std::cout << "foudn" << std::endl;
	}
}


void Chip8::OP_Fx15(){ //  GOOD
	std::cout << "OP_Fx15" << std::endl;
	uint8_t x = (opcode & 0x0F00) >> 8;

	this->delay_timer = registers[x];
}


void Chip8::OP_Fx18(){ // GOOD
	std::cout << "Fx18" << std::endl;

	uint8_t x = (opcode & 0x0F00) >> 8;	

	sound_timer = registers[x];
}


void Chip8::OP_Fx1E(){ // GOOD
	std::cout << "Fx1E" << std::endl;

	uint8_t x = (opcode & 0x0F00) >> 8;

	index_register += registers[x];
}

// load font in index register
void Chip8::OP_Fx29(){ // GOOD
	std::cout << "Fx29" << std::endl;

	unsigned long x = (opcode & 0x0F00) >> 8;
	unsigned long Vx = registers[x];

	index_register = 0x50 + (5 * Vx);

}


void Chip8::OP_Fx33(){ // GOOD
	std::cout << "Fx33" << std::endl;

	uint8_t Vx = (opcode & 0x0F00) >> 8;
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


void Chip8::OP_Fx55(){ // GOOD
	std::cout << "Fx55" << std::endl;

	uint8_t Vx = (opcode & 0x0F00) >> 8;

	for(uint8_t i = 0; i <= Vx; i++){
		memory[index_register + i] = registers[i]; 
	}
}


void Chip8::OP_Fx65(){ // GOOD
	std::cout << "Fx65" << std::endl;

	uint8_t Vx = (opcode & 0x0F00) >> 8;

	for (uint8_t i = 0; i <= Vx; ++i){
		registers[i] = memory[index_register + i];
	}
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