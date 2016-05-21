#ifndef BARRIER_H
#define BARRIER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
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
		//Postcondition: The variables are initialized, but it cannot render to a 
		//window or play sound. 
//**********************************************************************************
		~Barrier(){Mix_FreeChunk( explosion_sound );}
		//Summary: Destructor. 
		//Precondition: None.
		//Postcondition: Frees the memory allocated for the sound chunk.
//**********************************************************************************
		void setRenderer(SDL_Renderer* renderer);
		//Summary: Sets up the object so that it can be rendered to a window.
		//Precondition: The renderer for the window must be set up prior to running
		//this function.
		//Postcondition: The object is ready to be rendered to a window.
//**********************************************************************************
		void setX(int x);
		//Summary: Sets the x position for the barrier.
		//Precondition: x must be >= 0 or less than the screen width.
		//Postcondition: The X position for the barrier is set the the variable 
		//passed in
//**********************************************************************************
		void setY(int y);
		//Summary: Sets the y position for the barrier.
		//Precondition: y must be >= 0 or less than the screen height.
		//Postcondition: The y position for the barrier is set the the variable 
		//passed in
//**********************************************************************************
		void render();
		//Summary: Renders the barrier to the window.
		//Precondition: The renderer must be set up prior to running this function.
		//Postcondition: The barrier is rendered to the screen if it has not been
		//destroyed.
//**********************************************************************************
		void destroy();
		//Summary: Simulates the barrier being destroyed.
		//Precondition: None.
		//Postcondition: Makes it so the that barrier cannot collide and doesn't 
		//render to the screen. 
//**********************************************************************************
		SDL_Rect getCollisionBox()const {return mCollider;}
		//Summary: Getter for the collision box.
		//Precondition: None.
		//Postcondition: Returns a copy of the barrier's collision box.
//**********************************************************************************
		void reset();
		//Summary: Resets the object so that it is similar to after the constructor 
		//was called.
		//Precondition: None.
		//Postcondition: The barrier can render to the screen, and has a collision
		//box that can collide with things again.
//**********************************************************************************
		void initAudio();
		//Summary: Initializes the audio.
		//Precondition: The audio for the window must be initialized prior to calling
		//this function.
		//Postcondition: The audio is now capable of playing.
//**********************************************************************************
		
	private:
		//flag to indicate whether or not the barrier should be shown on the screen.
		bool isShowing;

		//Collision box and position indicator.
		SDL_Rect mCollider;

		//Renderer pointer so that it can render itself to the window.
		SDL_Renderer* renderer;

		//sound that plays when the barrier is destroyed.
		Mix_Chunk* explosion_sound;
};
#endif