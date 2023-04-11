#ifndef CHIP_8
#define CHIP_8
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include "screen.hpp"
#define ROM "test_rom_opcode.ch8"
#define MEMORY_START 				0x000
#define CHIP8_INTERPRETOR_START 	0X000
#define CHIP8_INTERPRETOR_END 		0X1FF
#define STOARGE_START				0x050
#define STORAGE_END					0X0A0
#define ROM_MEMORY_START			0x200
#define ROM_MEMORY_END				0xFFF
#define MEMORY_END					0XFFF
#define FONT_SIZE					80
#define FONT_STARTING_ADDRESS		0x50
#define NUM_INSTRUCTIONS			36



class Chip8{
	public:
		void test();
		Chip8();
		~Chip8();
		void load_rom();
		void load_font();
		void cycle();
		void execute_opcode();
		uint32_t display[64*32];
		Screen* screen;
	private:
		uint16_t opcode;
		uint8_t registers[16];
		uint8_t memory[4096];
		uint16_t index_register;
		uint16_t program_counter;
		uint16_t stack[16];
		uint8_t stack_pointer;
		uint8_t delay_timer;
		uint8_t sound_timer;
		uint8_t input_keys[16];
		const uint8_t font[FONT_SIZE];
		void (Chip8::*opcode_table[NUM_INSTRUCTIONS])();
		const uint8_t fi_nibble() const;
		const uint8_t se_nibble() const;
		const uint8_t th_nibble() const;
		const uint8_t fo_nibble() const;
		void OP_0nnn();
		void OP_00EE();
		void OP_00E0();
		void OP_1nnn();
		void OP_2nnn();
		void OP_3xkk();
		void OP_4xkk();
		void OP_5xy0();
		void OP_6xkk();
		void OP_7xkk();
		void OP_8xy0();
		void OP_8xy1();
		void OP_8xy2();
		void OP_8xy3();
		void OP_8xy4();
		void OP_8xy5();
		void OP_8xy6();
		void OP_8xy7();
		void OP_8xyE();
		void OP_9xy0();
		void OP_Annn();
		void OP_Bnnn();
		void OP_Cxkk();
		void OP_Dxyn();
		void OP_Ex9E();
		void OP_ExA1();
		void OP_Fx07();
		void OP_Fx0A();
		void OP_Fx15();
		void OP_Fx18();
		void OP_Fx1E();
		void OP_Fx29();
		void OP_Fx33();
		void OP_Fx55();
		void OP_Fx65();
		void OP_NULL();
};
#endif