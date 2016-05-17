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

	mVelX = 1;	
}
enemyShip::enemyShip(SDL_Renderer* renderer) : Ship(renderer)
{
	mPosX = 0;
	mPosY = 0;
	mCollider.x = mPosX;
	mCollider.y = mPosY;
	mVelX = 1;
} 

enemyShip::enemyShip(SDL_Renderer * renderer, int posX, int posY): Ship(renderer)
{
	this->mPosX = posX;
	this->mPosY = posY;
	mCollider.x = mPosX;
	mCollider.y = mPosY;
	mVelX = 0;
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

void enemyShip::move(enemyShip arr[][10])
{
    //Move the ship left or right
    if(isShowing)
    {
		mPosX += mVelX;
		mCollider.x = mPosX;
    }


    //If the ship collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + SHIP_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				arr[i][j].mPosX -= mVelX;
				arr[i][j].mCollider.x = mPosX;
				arr[i][j].mVelX *= -1;
				arr[i][j].mPosY += 20;
				arr[i][j].mCollider.y += 20;
			}
		}
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