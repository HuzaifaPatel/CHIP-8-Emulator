#ifndef CHIP_8
#define CHIP_8
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <bitset>
#include <string>
#include <sstream> 
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



class Chip8{
	public:
		Chip8();
		~Chip8();
		void load_rom();
		void load_font_in_memory();
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
		uint32_t display[64*32];
		uint8_t font[FONT_SIZE];


};
#endif