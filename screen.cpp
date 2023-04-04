#include "screen.hpp"

Screen::Screen(){
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("CHIP 8 EMULATOR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH*8, HEIGHT*8, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
}


Screen::~Screen(){
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void Screen::update(void const* sprite, int pitch){
	SDL_UpdateTexture(texture, NULL, sprite, 8);
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


char Screen::checkKey(){
	while(SDL_PollEvent(&event)){            
	    switch( event.type ){
	        /* Keyboard event */
	        case SDLK_0:
	        	return '0';
	        case SDLK_1:
	        	return '1';
	        case SDLK_2:
	        	return '2';
	        case SDLK_3:
	        	return '3';
	        case SDLK_4:
	        	return '4';
	        case SDLK_5:
	        	return '5';
	        case SDLK_6:
	        	return '6';
	        case SDLK_7:
	        	return '7';
			case SDLK_8:
				return '8';
			case SDLK_9:
				return '9';
			case SDLK_a:
				return 'A';
			case SDLK_b:
				return 'B';
			case SDLK_c:
				return 'C';
			case SDLK_d:
				return 'D';
			case SDLK_e:
				return 'E';
			case SDLK_f:
				return 'F';
	        default:
	            return -1;
	    }
	}

	return -1;
}


void Screen::load_screen(){


    for (;;)
    {
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                return;
            }
        }
    }
}