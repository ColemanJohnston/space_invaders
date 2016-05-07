#include "ship.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <stdio.h>
#include <string>
#include "enemyShip.h"

enemyShip::enemyShip():Ship()
{
	mPosX = 0;
	mPosY = 0;
	mCollider.x = mPosX;
	mCollider.y = mPosY;
	mVelX = 2;	
}
enemyShip::enemyShip(SDL_Renderer* renderer) : Ship(renderer)
{
	mPosX = 0;
	mPosY = 0;
	mCollider.x = mPosX;
	mCollider.y = mPosY;
	mVelX = 2;
} 

void enemyShip::setX(int x)
{
	this->mPosX = x;
	this->mCollider.x = x;
}
void enemyShip::setY(int y)
{
	this->mPosY = y;
	this->mCollider.y = y;
}

void enemyShip::move()
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
		mVelX *= -1;
		mPosY += 5;
		mCollider.y += 5;
    }
}

void enemyShip::setRenderer(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    SDL_Surface* surface = IMG_Load("./redChip.png");
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
}