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
	SDL_SetRenderDrawColor(renderer, 20, 20, 200, 255); //color
	SDL_Rect rect1 = {0, 0, 12, 12};
	SDL_Rect rect2 = {12, 0, 12, 12};
	SDL_Rect rect3 = {24, 0, 12, 12};
	SDL_Rect rect4 = {36, 0, 12, 12};
	SDL_Rect rect5 = {0, 12, 12, 12};

	// SDL_Rect rect1;
	// rect1.x = 1 * 12;
	// rect1.y = 1 * 1;
	// rect1.w = 8 * 6;
	// rect1.h = 5 * 6;

	// SDL_Rect rect2;
	// rect2.x = 1 * 24;
	// rect2.y = 1 * 1;
	// rect2.w = 8 * 6;
	// rect2.h = 5 * 6;

	// SDL_Rect rect3;
	// rect3.x = 1 * 36;
	// rect3.y = 1 * 1;
	// rect3.w = 8 * 6;
	// rect3.h = 5 * 6;



	// SDL_Rect rect4;
	// rect4.x = 1 * 1;
	// rect4.y = 1 * 36;
	// rect4.w = 8 * 6;
	// rect4.h = 5 * 6;




	SDL_RenderFillRect(renderer, &rect1);
	SDL_RenderFillRect(renderer, &rect2);
	SDL_RenderFillRect(renderer, &rect3);
	SDL_RenderFillRect(renderer, &rect4);
	SDL_RenderFillRect(renderer, &rect5);

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