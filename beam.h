#ifndef BEAM_H
#define BEAM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_mixer.h>
#include <string>

class Beam
{
    public:
		//The dimensions of the beam
		static const int BEAM_WIDTH = 4;
		static const int BEAM_HEIGHT = 8;
		static const int SCREEN_WIDTH = 640;//make sure beam knows screen size
		static const int SCREEN_HEIGHT = 480;//make sure beam knows screen size 

//*****************************************************************************************		
		Beam(SDL_Renderer* renderer);
		//Summary: Argument constructor.
		//Precondition: The renderer for the window must be already set up and passed in.
		//Postcondition: The object initialized and ready to be rendered to the screen, but
		//the audio is not ready to play yet.
//*****************************************************************************************
		Beam();
		//Summary: Default constructor.
		//Precondition: None.
		//Postcondition: The variables are initialized, but it is not capable of rendering 
		//or playing sounds. 
//*****************************************************************************************
		~Beam(){ Mix_FreeChunk( laser_sound ); }
		//Summary: Destructor.
		//Precondition: None.
		//Postcondition: Frees the memory allocated for the sound chunk.
//*****************************************************************************************
		void setRenderer(SDL_Renderer* renderer);
		//Summary: Sets up renderer so that the beam can render itself to the screen.
		//Precondition: The renderer for the window must be already set up and passed into
		//the function.
		//Postcondition: The beam is ready to render itself to the window.
//*****************************************************************************************
		void move();
		//Summary: Moves the beam.
		//Precondition: The beams location must be inside the screen.
		//Postcondition:
//*****************************************************************************************
		void render();
		//Summary: Renders the beam to the screen.
		//Precondition: The beam's render must be set up before this function can be called.
		//Postcondition: The beam is rendered to the window.
//*****************************************************************************************
		void shoot(int startX, int startY, int velocity);
		//Summary: shoots the beam.
		//Precondition: startX and startY must be coordinates inside the screen.
		//Postcondition: If the beam is not already moving it starts the beam moving in 
		//the Y direction at the rate specified in the velocity parameter. 
//*****************************************************************************************
		void destroy();
		//Summary: Simulates the beam being destroyed.
		//Precondition: None.
		//Postcondition: Makes it so the object doesn't render to the window, and the 
		//collision box can't hit anything.
//*****************************************************************************************
		SDL_Rect getCollisionBox()const {return mCollider;}
		//Summary: Getter for the Collision box.
		//Precondition: None.
		//Postcondition: returns a copy of the collision box.
//*****************************************************************************************
		void initAudio();
		//Summary: Initializes the audio for the beam.
		//Precondition: The audio for the Window must be set up before this function is 
		//called.
		//Postcondition: The audio is ready to play.
//*****************************************************************************************

    private:
    	//boolean to signal if the beam is moving.
		bool isMoving;

		//The X and Y offsets of the beam
		int mPosX, mPosY;

		//The velocity of the beam
		int mVelY;
		
		//Dot's collision box
		SDL_Rect mCollider;

		//Beam needs the renderer from the window in order to render itself 
		SDL_Renderer* renderer;

		//sound sound that plays when the laser shoots.
		Mix_Chunk* laser_sound;
};
#endif