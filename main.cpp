#include "chip8.hpp"
#include "screen.hpp"

int main(){
	Chip8* chip8 = new Chip8();
	chip8->load_rom();
	chip8->load_font();
	
	while(true){
		// SDL_Event ev;
        // while (SDL_PollEvent(&ev))
        // {
        //     if (ev.type == SDL_QUIT)
        //     {
        //     	return 0;
        //     }
        // }

		chip8->cycle();
		chip8->execute_opcode();
		chip8->screen->update(chip8->display, sizeof(chip8->display[0]) * WIDTH);

	}
}