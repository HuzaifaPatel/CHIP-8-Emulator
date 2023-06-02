#include "chip8.hpp"
#include "screen.hpp"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std::chrono_literals;

int main(){
	Chip8* chip8 = new Chip8();
	chip8->load_rom();
	chip8->load_font();
	
	while(true){
       	for (int i = 100; i--;) {
			chip8->screen->checkKey(chip8->input_keys);
            chip8->cycle();
            chip8->execute_opcode();
        }
        // chip8->test();
        chip8->screen->update(chip8->display, sizeof(chip8->display[0]) * WIDTH);
		std::this_thread::sleep_for(17ms);
	}
}