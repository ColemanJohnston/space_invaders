#include "beam.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <stdio.h>
#include <string>


Beam::Beam()
{
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

Beam::Beam(SDL_Renderer* renderer)//do NOT try to run default constructor
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
        if( mPosY < 0 )
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
    }
}

void Beam::destroy()
{
    mPosY = SCREEN_HEIGHT - 1;
    mposX = SCREEN_WIDTH - 1;
    mCollider.y = mPosY;
    mCollider.x = mPosX;
    isMoving = false;
    mCollider.w = 0;
    mCollider.h = 0;
}