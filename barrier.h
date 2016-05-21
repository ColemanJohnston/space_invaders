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
		
		//make sure barrier knows its dimensions.
		static const int BARRIER_WIDTH = 5;
		static const int BARRIER_HEIGHT = 5;

		//make sure barrier knows screen size
		static const int SCREEN_WIDTH = 640;
		static const int SCREEN_HEIGHT = 480; 

//**********************************************************************************
		Barrier(SDL_Renderer* renderer);
		//Summary: Argument constructor.
		//Precondition: The renderer for the window must be set up before this 
		//function is called.
		//Postcondition: The variables for this function are initialized, and it can
		//render itself to the screen, but the audio cannot play yet.
//**********************************************************************************
		Barrier();
		//Summary: Default constructor.
		//Precondition: None.
		//Postcondition: The variables 
//**********************************************************************************
		~Barrier(){Mix_FreeChunk( explosion_sound );}
		//Summary:
		//Precondition:
		//Postcondition:
//**********************************************************************************
		void setRenderer(SDL_Renderer* renderer);
		//Summary:
		//Precondition:
		//Postcondition:
//**********************************************************************************
		void setX(int x);
		//Summary:
		//Precondition:
		//Postcondition:
//**********************************************************************************
		void setY(int y);
		//Summary:
		//Precondition:
		//Postcondition:
//**********************************************************************************
		void render();
		//Summary:
		//Precondition:
		//Postcondition:
//**********************************************************************************
		void destroy();
		//Summary:
		//Precondition:
		//Postcondition:
//**********************************************************************************
		SDL_Rect getCollisionBox()const {return mCollider;}
		//Summary:
		//Precondition:
		//Postcondition:
//**********************************************************************************
		void reset();
		//Summary:
		//Precondition:
		//Postcondition:
//**********************************************************************************
		void initAudio();
		//Summary:
		//Precondition:
		//Postcondition:
//**********************************************************************************
		
	private:
		bool isShowing;
		SDL_Rect mCollider;
		SDL_Renderer* renderer;
		Mix_Chunk* explosion_sound;
};
#endif