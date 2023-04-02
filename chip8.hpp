#include<stdint.h>

#define MEMORY_START 				0x000

#define CHIP8_INTERPRETOR_START 	0X000
#define CHIP8_INTERPRETOR_END 		0X1FF
#define STOARGE_START				0x050
#define STORAGE_END					0X0A0
#define ROM_MEMORY_START			0x200
#define ROM_MEMORY_END				0xFFF

#define MEMORY_END					0XFFF



class chip8{
	public:
		void load_rom();

	private:
		inline uint16_t opcode;
		inline uint8_t register[16];
		inline uint8_t memory[4096];
		inline uint16_t index_register;
		inline uint16_t program_counter;
		inline uint16_t stack[16];
		inline uint8_t stack_pointer;
		inline uint8_t delay_timer;
		inline uint8_t sound_timer;
		inline uint8_t input_keys[16];
		inline uint32_t display[64*32];

	public:

};