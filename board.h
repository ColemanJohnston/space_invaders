#ifndef BOARD_H
#define BOARD_H
#include "ship.h"
#include "enemyShip.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>

class Board{

private:
	SDL_Texture texture;
	Ship playerShip;
	enemyShip[10][10];
	SDL_Renderer * renderer;
	SDL_window * window;
	int screenWidth;
	int screenHeight;

public:
	Board();
	~Board();
	void playerScore();
	void displayEnemy();
	void displayPlayerShip();
	void beginMenu();
	void loseScreen();
	void winScreen();
	void startGameLoop();
};
#endif
