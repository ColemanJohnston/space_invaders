#ifndef SHIP_H
#define SHIP_H

#include "beam.h"//class that encasulates the functionality of the beam
#include <SDL2/SDL.h>//graphics
#include <SDL2/SDL_image.h>//allows us to load image formats
#include <SDL2/SDL_mixer.h>//allows us to play sound
#include <string>//string functions

class Ship
{
    public:
//************************************************************************************************
		Ship();
		//Summary: Default constructor.
		//Precondition: The member variables of the object are not initialized.
		//Postcondition: Member variables are initialized, the the object cannot yet
		//render itself to the screen or play sound because those need to be set or initialized 
		//with functions.
//************************************************************************************************
		Ship(SDL_Renderer* renderer);
		//Summary: Argument constructor includes the renderer that allows the object to render
		//itself to the screen.
		//Precondition: The member variables of the object are not initialized.
		//Postcondition: The member variables are intialized, and the object can render itself to 
		//the screen, but cannot play sound until 
//************************************************************************************************
		~Ship();
		//Summary: Destructor cleans up texture and sound chunk.
		//Precondition: The object is fully functional.
		//Postcondition: The heap memory that the object is using is set free.
//************************************************************************************************
		void handleEvent( SDL_Event& e );
		//Summmary: Takes key presses and adjusts the ship's velocity or fires a beam.
		//Precondition: A new event took place and is passed into the function.
		//Postcondition: The velocity of the ship is changed according to if left and right arrow
		//keys are pressed and passed into the function. If a space bar event is passed into the
		//function it calls the beams shoot() method.
//***********************************************************************************************
		void move();
		//Summary: Changes the ship's position according to the value of its velocity.
		//Precondition: The ships position variables indicate that it is inside the screen.
		//Postcondition: The ships position is changed according to its velocity, but the ship 
		//will stop moving if it is outside the edges of the screen.
//***********************************************************************************************
		SDL_Rect getShipCollisionBox();
		//Summary: Getter for the ship's collision box.
		//Precondition: None.
		//Postconditon: A copy of the ships collision box is passed through the function.
//***********************************************************************************************
		SDL_Rect getBeamBox();
		//Summary: Getter for the collision box of the Beam object associated with the ship.
		//Precondition: None.
		//Postcondition: A copy of the collision box from the beam associated with the ship is 
		//returned.
//***********************************************************************************************
		void render();
		//Summmary: Renders the ship and its beam to the screen.
		//Precondition: The ship must have a renderer set through the setRenderer function, or 
		//the overloaded constructor.
		//Postcondition: If isShowing is true then the ship is rendered to the screen, but if it
		//is false the ship is not rendered to the screen. The render() method from the beam is
		//always called.
//***********************************************************************************************
		void render(int x, int y);
		//Summary: Renders the ship image to a position on the screen.
		//Precondition: The ship must have a renderer before this function runs.
		//Postcondition: An image of the ship is rendered to the screeen at the (x,y) position.
//***********************************************************************************************
		void setRenderer(SDL_Renderer* renderer);
		//Summary: Sets up the renderer and texture for the ship objects.
		//Precondition: The rendered associated with a window must be passed into this function.
		//Postcondition: The renderer and texture for both the beam object and the ship object 
		//are fully set up after this function runs.
//***********************************************************************************************
		void destroy();
		//Summary: Makes it as if the ship was destroyed.
		//Precondition: None.
		//Postcondition: Makes it so that the ship will not render, and makes the collision box
		//can't collide with anything.
//***********************************************************************************************
		void resetBeam(){beam.destroy();}
		//Summary: A function to reset the beam if it collides with something.
		//Precondition: None.
		//Postcondition: The Ship's beam is reset so that it cannot collide with anything and is
		//prepared to be shot again.
//***********************************************************************************************
		void reset();
		//Summary: A function to reset the Ship to a state like the constructor just ran. 
		//Precondition: None.
		//Postcondition: The member variables of the ship are reset to a state where it can be
		//used again.
//***********************************************************************************************
		void initAudio();
		//Summary: Starts the audio for the ship.
		//Precondition: The audio for the window must be initialized before this function is 
		//called in order for the audio to work properly.
		//Postcondition: The audio can play after this function runs.
//***********************************************************************************************
		//The size of all ships.
		static const int SHIP_WIDTH = 20;
		static const int SHIP_HEIGHT = 20;
		
		//The size of the  screen.
		static const int SCREEN_WIDTH = 640;
		static const int SCREEN_HEIGHT = 480; 

		//Maximum number of pixels the ship can move in a frame.
		static const int SHIP_VEL = 10;
//*************************************************************************************************
    protected:
		//ship needs the renderer from window in order to be able to render itself 
		SDL_Renderer* renderer;

		//pointer to the sound that plays when the ship explodes
		Mix_Chunk* explosion_sound; 

		//The X and Y offsets of the ship
		int mPosX, mPosY;

		//The velocity of the ship at a given time
		int mVelX;

		//boolean to signal if the ship should be showing  on the screen.
		bool isShowing;

		//beam object associated with each ship so that it can shoot.
		Beam beam;
		
		//Ship's collision box and box that the ship renders in.
		SDL_Rect mCollider;

		//The picture associated to the ship.
		SDL_Texture* texture;
};
#endif