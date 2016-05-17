#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "ship.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <stdio.h>
#include <string>

class enemyShip : public Ship
{
public:
	enemyShip(SDL_Renderer* renderer);
	enemyShip();
	enemyShip(SDL_Renderer* renderer, int posX, int posY);
	void move(enemyShip arr[][10]);
	void setX(int x);
	void setY(int y);
	void setRenderer(SDL_Renderer* renderer);
    bool shoot();
};
#endif


