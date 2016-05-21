#include "ship.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <string>
#include "enemyShip.h"

enemyShip::enemyShip():Ship()
{
	mPosX = 0;
	mPosY = 0;
	mCollider.x = mPosX;
	mCollider.y = mPosY;
	mVelX = 1;	
}
enemyShip::enemyShip(SDL_Renderer* renderer) : Ship()
{
	mPosX = 0;
	mPosY = 0;
	mCollider.x = mPosX;
	mCollider.y = mPosY;
	mVelX = 1;
	setRenderer(renderer);
} 

enemyShip::enemyShip(SDL_Renderer * renderer, int posX, int posY): Ship()
{
	this->mPosX = posX;
	this->mPosY = posY;
	mCollider.x = mPosX;
	mCollider.y = mPosY;
	mVelX = 1;
	setRenderer(renderer);
}

void enemyShip::setX(int x)
{
	if(x < 0 || x >= SCREEN_WIDTH)
		x = 0;

	this->mPosX = x;
	this->mCollider.x = x;
}
void enemyShip::setY(int y)
{
	if(y < 0 || y >= SCREEN_HEIGHT)
		y = 0;

	this->mPosY = y;
	this->mCollider.y = y;
}

void enemyShip::move(enemyShip arr[][10], bool& isInBottom)
{
    //Move the ship left or right
    if(isShowing)
    {
		mPosX += mVelX;
		mCollider.x = mPosX;
    }


    //If the ship collided or went too far to the left or right
    if((( mPosX < 0 ) || ( mPosX + SHIP_WIDTH > SCREEN_WIDTH)) && isShowing)
    {
        //Move back
		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				if(isShowing)
				{
					arr[i][j].mPosX -= mVelX;
					arr[i][j].mCollider.x = mPosX;
					arr[i][j].mVelX *= -1;
					arr[i][j].mPosY += 20;
					arr[i][j].mCollider.y += 20;
				}
			}
		}
    }
    if(mPosY > SCREEN_HEIGHT - 20)
    {
    	isInBottom = true;
    }
    beam.move();
}

void enemyShip::setRenderer(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    beam.setRenderer(renderer);
    SDL_Surface* surface = IMG_Load("./redChip.png");
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
}

bool enemyShip::shoot()
{
	if(isShowing)
	{
		beam.shoot(mCollider.x,mCollider.y,5);
		return true;
	}
	else
		return false;
}

void enemyShip::reset()
{
	//reset the offsets
    mPosX = 0;
    mPosY = 0;

    //reset collision box dimension
    mCollider.w = SHIP_WIDTH;
    mCollider.h = SHIP_HEIGHT;
    mCollider.x = mPosX;
    mCollider.y = mPosY;
    isShowing = true;

    //re-initialize the velocity
    mVelX = 1;    
}