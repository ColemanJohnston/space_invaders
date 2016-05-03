#include "ship.h"
#include "beam.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <stdio.h>
#include <string>

Ship::Ship()
{
   //Initialize the offsets
    mPosX = SCREEN_WIDTH / 2;
    mPosY = SCREEN_HEIGHT - 25;

    //Set collision box dimension
    mCollider.w = SHIP_WIDTH;
    mCollider.h = SHIP_HEIGHT;
    mCollider.x = mPosX;
    mCollider.y = mPosY;

    //Initialize the velocity
    mVelX = 0; 
}

Ship::Ship(SDL_Renderer* renderer)//do NOT try to run default constructor
{
    this->renderer = renderer;
    //make surface
    SDL_Surface* surface = IMG_Load("./ship.bmp");
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    //Initialize the offsets
    mPosX = SCREEN_WIDTH / 2;
    mPosY = SCREEN_HEIGHT - 25;

    //Set collision box dimension
    mCollider.w = SHIP_WIDTH;
    mCollider.h = SHIP_HEIGHT;
    mCollider.x = mPosX;
    mCollider.y = mPosY;

    beam.setRenderer(renderer);

    //Initialize the velocity
    mVelX = 0;
}

void Ship::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT: mVelX -= SHIP_VEL; break;
            case SDLK_RIGHT: mVelX += SHIP_VEL; break;
            case SDLK_SPACE: beam.shoot(mPosX + 8,mPosY,-10); break;
        }
     }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT: mVelX += SHIP_VEL; break;
            case SDLK_RIGHT: mVelX -= SHIP_VEL; break;
        }
    }
}

void Ship::move()
{
    //Move the ship left or right
    mPosX += mVelX;
	mCollider.x = mPosX;

    //If the ship collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + SHIP_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
		mCollider.x = mPosX;
    }
    beam.move();
}

void Ship::render()
{
    //Show the ship
	SDL_RenderCopy(renderer, texture, 0, &mCollider);
    beam.render();
}

void Ship::setRenderer(SDL_Renderer* renderer)
{
    this->renderer = renderer;

    SDL_Surface* surface = IMG_Load("./ship.bmp");
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    beam.setRenderer(renderer);
}