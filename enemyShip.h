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
	void move();
	void setX(int x);
	void setY(int y);
	void setRenderer(SDL_Renderer* renderer);
};

/*class enemyShipGrid
{
public:
	enemyShip enemies[Ship::SHIP_WIDTH][Ship::SHIP_HEIGHT];

};
*/
#endif


