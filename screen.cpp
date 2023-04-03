#include "screen.hpp"

Screen::Screen(){
	this->running = 1;
	this->fullscreen = 0;
}


void Screen::update(){
	if(fullscreen){
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	}

	if(!fullscreen){
		SDL_SetWindowFullscreen(window, 0);
	}
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


void Screen::draw(){
	SDL_SetRenderDrawColor(renderer, 40, 43, 200, 255);
	SDL_Rect rect;
	rect.x = rect.y = 0;
	rect.w = 100;
	rect.h = 100;
	SDL_RenderFillRect(renderer, &rect);

	frameCount++;
	int timerFPS = SDL_GetTicks() - lastFrame;

	if(timerFPS < (1000/60)){
		SDL_Delay((1000/60) - timerFPS);
	}

	SDL_RenderPresent(renderer);
}


void Screen::load_screen(){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		std::cout << "FAILED AT SDL_INIT_EVERYTHING" << std::endl;
	}

	if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0){
		std::cout << "Failed at SDL_CreateWindowAndRederer";
	}

	SDL_SetWindowTitle(window, "Chip 8 Emulator");
	SDL_ShowCursor(1);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

	while(running){
		lastFrame = SDL_GetTicks();
		if(lastFrame >= (lastFrame + 1000)) {
			lastTime = lastFrame;
			fps = frameCount;
			frameCount = 0;
		}

		std::cout << fps << std::endl;

		update();
		input();
		draw();
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}