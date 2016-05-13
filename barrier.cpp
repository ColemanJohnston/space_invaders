#include "barrier.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
Barrier::Barrier()
{
    mCollider.w = BARRIER_WIDTH;
    mCollider.h = BARRIER_HEIGHT;
    mCollider.x = 0;
    mCollider.y = 0; 
}
Barrier::Barrier(SDL_Renderer* renderer)
{
	this->renderer = renderer;
    //Set collision box dimension
    mCollider.w = BARRIER_WIDTH;
    mCollider.h = BARRIER_HEIGHT;
    mCollider.x = SCREEN_WIDTH/2;
    mCollider.y = SCREEN_HEIGHT -25;  
   // SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF ); 
}
void Barrier::setRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}
void Barrier::render()
{
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );
	SDL_RenderFillRect( renderer, &mCollider );
}
void Barrier::destroy()
{
    mCollider.y = SCREEN_HEIGHT - 1;
    mCollider.x = SCREEN_WIDTH - 1;
    mCollider.w = 0;
    mCollider.h = 0;

    isShowing = false;
}
void Barrier::setX(int x)
{
	this->mCollider.x = x;
}
void Barrier::setY(int y)
{
	this->mCollider.y = y;
}