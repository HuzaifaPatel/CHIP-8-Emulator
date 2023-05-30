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


void Screen::input(){
	SDL_Event e;

	while(SDL_PollEvent(&e)){
		if(e.type == SDL_QUIT){
			running = false;
		}

		const uint8_t* keystates = SDL_GetKeyboardState(NULL);

		if(keystates[SDL_SCANCODE_ESCAPE]){
			running = false;
		}

		if(keystates[SDL_SCANCODE_F11]){
			fullscreen = 1;
		}
	}
}


void Screen::clear_screen(){
	SDL_RenderClear(renderer);
}


char Screen::checkKey(uint8_t* input_keys){
	while(SDL_PollEvent(&event)){   
	    switch (event.type){
        	case SDL_KEYDOWN:
			    switch(event.key.keysym.sym){
			        /* Keyboard event */
			        case SDLK_0:
			        	input_keys[0] = 0;
			        case SDLK_1:
			        	input_keys[1] = 1;
			        case SDLK_2:
			        	input_keys[2] = 2;
			        case SDLK_3:
			        	input_keys[3] = 3;
			        case SDLK_4:
			        	input_keys[4] = 4;
			        case SDLK_5:
			        	input_keys[5] = 5;
			        case SDLK_6:
			        	input_keys[6] = 6;
			        case SDLK_7:
			        	input_keys[7] = 7;
					case SDLK_8:
						input_keys[8] = 8;
					case SDLK_9:
						input_keys[9] = 9;
					case SDLK_a:
						input_keys[10] = 10;
					case SDLK_b:
						input_keys[11] = 11;
					case SDLK_c:
						input_keys[12] = 12;
					case SDLK_d:
						input_keys[13] = 13;
					case SDLK_e:
						input_keys[14] = 14;
					case SDLK_f:
						input_keys[15] = 15;
			    }
			case SDL_KEYUP:
				switch(event.key.keysym.sym){
			        /* Keyboard event */
			        case SDLK_0:
			        	input_keys[0] = 0;
			        case SDLK_1:
			        	input_keys[1] = 1;
			        case SDLK_2:
			        	input_keys[2] = 2;
			        case SDLK_3:
			        	input_keys[3] = 3;
			        case SDLK_4:
			        	input_keys[4] = 4;
			        case SDLK_5:
			        	input_keys[5] = 5;
			        case SDLK_6:
			        	input_keys[6] = 6;
			        case SDLK_7:
			        	input_keys[7] = 7;
					case SDLK_8:
						input_keys[8] = 8;
					case SDLK_9:
						input_keys[9] = 9;
					case SDLK_a:
						input_keys[10] = 10;
					case SDLK_b:
						input_keys[11] = 11;
					case SDLK_c:
						input_keys[12] = 12;
					case SDLK_d:
						input_keys[13] = 13;
					case SDLK_e:
						input_keys[14] = 14;
					case SDLK_f:
						input_keys[15] = 15;
				}
		}
	}

	return 48;
}



void Screen::clearKey(uint8_t* input_keys, uint8_t NUM_INPUT_KEYS){
	for(uint8_t key = 0; key < NUM_INPUT_KEYS; key++){
		input_keys[key] = 0;
	}
}