#ifndef BEAM_H
#define BEAM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <stdio.h>
#include <string>

class Beam
{
    public:
		//The dimensions of the beam
		static const int BEAM_WIDTH = 4;
		static const int BEAM_HEIGHT = 8;
		
		static const int SCREEN_WIDTH = 640;//Coleman: make sure beam knows screen size
		static const int SCREEN_HEIGHT = 480;//Coleman: make sure beam knows screen size 

		//Maximum axis velocity of the beam
		static const int BEAM_VEL = 10;

		//Initializes the variables
		Beam(SDL_Renderer* renderer);//constructor needs the renderer in order to render itself to the screen and not have a global variable

		Beam();

		void setRenderer(SDL_Renderer* renderer);

		//Moves the dot and checks collision
		void move();

		//Shows the beam on the screen
		void render();

		//shoot the beam
		void shoot(int startX, int startY, int velocity);

    private:
		
		bool isMoving;

		//The X and Y offsets of the beam
		int mPosX, mPosY;

		//The velocity of the beam
		int mVelY;
		
		//Dot's collision box
		SDL_Rect mCollider;

		//ship needs the renderer from the rest of the class in order to be able to render itself 
		SDL_Renderer* renderer;
};
#endif