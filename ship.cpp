#include "ship.h"
#include "beam.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h> 
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
    isShowing = true;
    explosion_sound = Mix_LoadWAV( "./explosion.wav" );
    Mix_Volume(1,25);

    //Initialize the velocity
    mVelX = 0; 
}

Ship::Ship(SDL_Renderer* renderer)//do NOT try to run default constructor
{
    this->renderer = renderer;
    //make surface
    SDL_Surface* surface = IMG_Load("./ship.png");
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    explosion_sound = Mix_LoadWAV( "./explosion.wav" );
    Mix_Volume(1,25);

    //Initialize the offsets
    mPosX = SCREEN_WIDTH / 2;
    mPosY = SCREEN_HEIGHT - 25;

    //Set collision box dimension
    mCollider.w = SHIP_WIDTH;
    mCollider.h = SHIP_HEIGHT;
    mCollider.x = mPosX;
    mCollider.y = mPosY;
    isShowing = true;

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
            case SDLK_SPACE: 
            if(isShowing)
                beam.shoot(mPosX + 8,mPosY,-10); break;
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

SDL_Rect Ship::getShipCollisionBox()
{
    return mCollider;
}

SDL_Rect Ship::getBeamBox()
{
    beam.getCollisionBox();
}

void Ship::render()
{
    //Show the ship
	if(isShowing)
    {
        SDL_RenderCopy(renderer, texture, 0, &mCollider);
    }

    beam.render();
}

void Ship::setRenderer(SDL_Renderer* renderer)
{
    this->renderer = renderer;

    SDL_Surface* surface = IMG_Load("./ship.bmp");
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    beam.setRenderer(renderer);
    //
    

}

void Ship::destroy()
{
    mCollider.x = 2;
    mCollider.y = 2;
    mCollider.w = 0;
    mCollider.h = 0;
    mPosX = 2;
    mPosY = 2;
    isShowing = false;
    mVelX = 0;
    Mix_PlayChannel( 1, explosion_sound, 0 );
}

void Ship::reset()
{
    //reset the offsets
    mPosX = SCREEN_WIDTH / 2;
    mPosY = SCREEN_HEIGHT - 25;

    //reset collision box dimension
    mCollider.w = SHIP_WIDTH;
    mCollider.h = SHIP_HEIGHT;
    mCollider.x = mPosX;
    mCollider.y = mPosY;
    isShowing = true;

    //re-initialize the velocity
    mVelX = 0;    
}