#ifndef SHIP_H
#define SHIP_H

#include "beam.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

class Ship
{
    public:
		//The dimensions of the ship
		static const int SHIP_WIDTH = 20;
		static const int SHIP_HEIGHT = 20;
		
		static const int SCREEN_WIDTH = 640;//Coleman: make sure ship knows screen size
		static const int SCREEN_HEIGHT = 480;//Coleman: make sure ship knows screen size 

		//Maximum axis velocity of the ship
		static const int SHIP_VEL = 10;

		//Initializes the variables
		Ship();
		Ship(SDL_Renderer* renderer);//constructor needs the renderer in order to render itself to the screen and not have a global variable

		~Ship(){SDL_DestroyTexture(texture);}

		//Takes key presses and adjusts the ship's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot and checks collision
		void move();
		SDL_Rect getShipCollisionBox();
		SDL_Rect getBeamBox();

		//Shows the ship on the screen
		void render();
		
		void setRenderer(SDL_Renderer* renderer);

		void destroy();

		void resetBeam(){beam.destroy();}

    protected:
		//ship needs the renderer from the rest of the class in order to be able to render itself 
		SDL_Renderer* renderer;

		//The X and Y offsets of the ship
		int mPosX, mPosY;

		//The velocity of the ship
		int mVelX;

		bool isShowing;

		Beam beam;
		
		//Dot's collision box
		SDL_Rect mCollider;

		//render the picture associated with the ship
		SDL_Texture* texture;
};
#endif