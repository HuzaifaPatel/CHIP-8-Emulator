#ifndef SCREEN_H
#define SCREEN_H
#include <SDL2/SDL.h>  
#include <iostream>

#define WIDTH 	640
#define HEIGHT 	320



class Screen{
	public:
		Screen();
		void update();
		void input();
		void draw();
		void load_screen();
		SDL_Renderer* renderer;
		SDL_Window* window;
		bool running;
		bool fullscreen;
		int frameCount;
		int timerFPS;
		int lastFrame;
		int lastTime;
		int fps;
};
#endif