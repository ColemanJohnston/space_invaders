#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "ship.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <string>

class enemyShip : public Ship
{
public:
//*********************************************************************
	enemyShip(SDL_Renderer* renderer);
	//Summary: Argument constructor.
	//Precondition: The window that the object is rendering to already
	//has a renderer.
	//Postcondition: The object is ready to be used and rendered to the
	//window, but the audio is not set up yet.
//*********************************************************************
	enemyShip(SDL_Renderer* renderer, int posX, int posY);
	//Summary: Argument constructor with positions.
	//Precondition: The window that the object is rendering to already
	//has a renderer.
	//Postcondition: The object is ready to be used and rendered to the
	//window at the specified (x,y) coordinates, but the audio is not 
	//set up yet.
//*********************************************************************	
	enemyShip();
	//Summary: Default Constructor.
	//Precondition: None.
	//Postcondition: The member variables are initialized, but the 
	//audio is not set up yet, and it is not ready to be rendered to a
	//window.
//*********************************************************************
	void move(enemyShip arr[][10], bool& isInBottom);
	//Summary: Moves the ships position. 
	//Precondition: The ship's position variables must be within the 
	//window  
	//Postcondition: The ship's position is changed accordingly, and if
	//a the ship is at the edge, it changes all the ships in the array 
	//so that all the ships can move in unison.
//*********************************************************************
	void setX(int x);
	//Summary: Sets the x position for the ship
	//Precondition: The variable passed in must be an integer less than
	//the screen width and >= 0.
	//Postcondition: The x position of the ship is set to the variable
	//passed in.
//*********************************************************************
	void setY(int y);
	//Summary: Sets the y position for the ship
	//Precondition: The variable passed in must be an integer less than
	//the screen height and >= 0.
	//Postcondition: The y position of the ship is set to the variable
	//passed in.
//*********************************************************************
	void setRenderer(SDL_Renderer* renderer);
	//Summary: Sets up the renderer so that the ship can render itself
	//to the screen.
	//Precondition: The renderer for the window must be set up and 
	//passed into the function.
	//Postcondition: The renderer and texture is set up for the Beam
	//and the ship. They are ready to be rendered to the window.
//*********************************************************************
    bool shoot();
    //Summary: A function to shoot the beam.
	//Precondition: None.
	//Postcondition: The ship shoots a beam by calling the shoot() 
	//function from the beam class.
//*********************************************************************
    void reset();
	//Summary: A function to reset the Ship to a state like the constructor just ran. 
	//Precondition: None.
	//Postcondition: The member variables of the ship are reset to a state where it can be
	//used again.
//*********************************************************************    
};
#endif