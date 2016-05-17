#ifndef BARRIER_H
#define BARRIER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>

class Barrier
{
	public:
		static const int BARRIER_WIDTH = 5;
		static const int BARRIER_HEIGHT = 5;
		static const int SCREEN_WIDTH = 640;//Coleman: make sure beam knows screen size
		static const int SCREEN_HEIGHT = 480;//Coleman: make sure beam knows screen size 

		Barrier(SDL_Renderer* renderer);
		Barrier();
		~Barrier(){Mix_FreeChunk( explosion_sound );}

		void setRenderer(SDL_Renderer* renderer);
		void setX(int x);
		void setY(int y);
		void render();
		void destroy();
		SDL_Rect getCollisionBox()const {return mCollider;}
		void reset();
		void initAudio();
		
	private:
		bool isShowing;
		SDL_Rect mCollider;
		SDL_Renderer* renderer;
		Mix_Chunk* explosion_sound;
};
#endif