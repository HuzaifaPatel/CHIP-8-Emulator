#include "screen.hpp"

Screen::Screen(){
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("CHIP 8 EMULATOR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH*16, HEIGHT*16, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
}


Screen::~Screen(){
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void Screen::update(void const* sprite, int pitch){
	SDL_UpdateTexture(texture, NULL, sprite, pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}



void Screen::clear_screen(){
	SDL_RenderClear(renderer);
}


void Screen::checkKey(uint8_t* input_keys){
	while(SDL_PollEvent(&event)){   
	    switch (event.type){
        	case SDL_KEYDOWN:
			    switch(event.key.keysym.sym){
			        /* Keyboard event */
			        case SDLK_0:
			        	input_keys[0] = 1;
			        	break;
			        case SDLK_1:
			        	input_keys[1] = 1;
			        	break;
			        case SDLK_2:
			        	input_keys[2] = 1;
			        	break;
			        case SDLK_3:
			        	input_keys[3] = 1;
			        	break;
			        case SDLK_4:
			        	input_keys[4] = 1;
			        	break;
			        case SDLK_5:
			        	input_keys[5] = 1;
			        	break;
			        case SDLK_6:
			        	input_keys[6] = 1;
			        	break;
			        case SDLK_7:
			        	input_keys[7] = 1;
			        	break;
					case SDLK_8:
						input_keys[8] = 1;
						break;
					case SDLK_9:
						input_keys[9] = 1;
						break;
					case SDLK_a:
						input_keys[10] = 1;
						break;
					case SDLK_b:
						input_keys[11] = 1;
						break;
					case SDLK_c:
						input_keys[12] = 1;
						break;
					case SDLK_d:
						input_keys[13] = 1;
						break;
					case SDLK_e:
						input_keys[14] = 1;
						break;
					case SDLK_f:
						input_keys[15] = 1;
						break;
			    }
			    break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym){
			        /* Keyboard event */
			        case SDLK_0:
			        	input_keys[0] = 0;
			        	break;
			        case SDLK_1:
			        	input_keys[1] = 0;
			        	break;
			        case SDLK_2:
			        	input_keys[2] = 0;
			        	break;
			        case SDLK_3:
			        	input_keys[3] = 0;
			        	break;
			        case SDLK_4:
			        	input_keys[4] = 0;
			        	break;
			        case SDLK_5:
			        	input_keys[5] = 0;
			        	break;
			        case SDLK_6:
			        	input_keys[6] = 0;
			        	break;
			        case SDLK_7:
			        	input_keys[7] = 0;
			        	break;
					case SDLK_8:
						input_keys[8] = 0;
						break;
					case SDLK_9:
						input_keys[9] = 0;
						break;
					case SDLK_a:
						input_keys[10] = 0;
						break;
					case SDLK_b:
						input_keys[11] = 0;
						break;
					case SDLK_c:
						input_keys[12] = 0;
						break;
					case SDLK_d:
						input_keys[13] = 0;
						break;
					case SDLK_e:
						input_keys[14] = 0;
						break;
					case SDLK_f:
						input_keys[15] = 0;
						break;
				}
				break;
		}
	}
}
