#include "chip8.hpp"
#include "screen.hpp"

int main(){
	Chip8* chip8 = new Chip8();
	chip8->load_rom();
	chip8->load_font();
	
	while(true){
		chip8->cycle();
		chip8->screen->checkKey(chip8->input_keys);
		chip8->execute_opcode();
		chip8->screen->update(chip8->display, sizeof(chip8->display[0]) * WIDTH);
		// chip8->screen->clearKey(chip8->input_keys, NUM_INPUT_KEYS);
	}
}