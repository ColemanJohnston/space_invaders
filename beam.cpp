#include "beam.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h> 
#include <string>


Beam::Beam()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;

    //Set collision box dimension
    mCollider.w = 0;
    mCollider.h = 0;
    mCollider.x = mPosX;
    mCollider.y = mPosY;
    isMoving = false;

    //Initialize the velocity
    mVelY = 0;       
}

Beam::Beam(SDL_Renderer* renderer)
{
    this->renderer = renderer;

    //Initialize the offsets
    mPosX = SCREEN_WIDTH / 2;
    mPosY = SCREEN_HEIGHT - 25;

    //Set collision box dimension
    mCollider.w = BEAM_WIDTH;
    mCollider.h = BEAM_HEIGHT;
    mCollider.x = mPosX;
    mCollider.y = mPosY;
    isMoving = false;

    //Initialize the velocity
    mVelY = 0;
}

void Beam::setRenderer(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

void Beam::move()
{
    if(isMoving)
    {
        mPosY += mVelY;
    	mCollider.y = mPosY;

        //If the ship collided or went too far to the left or right
        if( mPosY < 0  || mPosY > SCREEN_HEIGHT)
        {
            destroy();
        }
    }
}

void Beam::render()
{
    //Show the ship
    if(isMoving)
    {
	   SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );
       SDL_RenderFillRect( renderer, &mCollider );
    }
}


void Beam::shoot(int startX, int startY,int velocity)
{
    if(!isMoving)
    {
        mCollider.w = BEAM_WIDTH;
        mCollider.h = BEAM_HEIGHT;
        mCollider.x = startX;
        mCollider.y = startY;
        mPosX = startX;
        mPosY = startY;
        mVelY = velocity;
        isMoving = true;
        Mix_PlayChannel( 2, laser_sound, 0 );
    }
}

void Beam::destroy()
{
    mPosY = SCREEN_HEIGHT - 1;
    mPosX = SCREEN_WIDTH - 1;
    mCollider.y = mPosY;
    mCollider.x = mPosX;
    isMoving = false;
    mCollider.w = 0;
    mCollider.h = 0;
}

void Beam::initAudio()
{
    laser_sound = Mix_LoadWAV( "./laser1.wav" );
    Mix_Volume(2,35);    
}