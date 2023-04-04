#ifndef SCREEN_H
#define SCREEN_H
#include <SDL2/SDL.h>  
#include <iostream>

#define WIDTH 	64
#define HEIGHT 	32



class Screen{
	public:
		Screen();
		~Screen();
		void update(void const* buffer, int pitch);
		void input();
		void load_screen();
		void clear_screen();
		char checkKey();
		bool running;
		bool fullscreen;
		int frameCount;
		int timerFPS;
		int lastFrame;
		int lastTime;
		int fps;
		SDL_Renderer* renderer;
		SDL_Window* window;
		SDL_Surface* screen;
		SDL_Surface* pixels;
		SDL_Texture* texture;
		SDL_Event event;

};
#endif