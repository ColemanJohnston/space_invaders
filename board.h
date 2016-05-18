#ifndef BOARD_H
#define BOARD_H

#include "ship.h"
#include "enemyShip.h"
#include "barrier.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <SDL2/SDL_ttf.h>

class Board{

private:
	SDL_Texture * texture;
	Ship playerShip;
	//TTF_Font font;
	enemyShip enemies[10][10];
	Barrier barrier1[10][10];
	Barrier barrier2[10][10];
	Barrier barrier3[10][10];
	SDL_Renderer * renderer;
	SDL_Window * window;
	Mix_Music * music;
	int screenWidth;
	int screenHeight;
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	int lifes = 3;
	int score = 0;
	

public:
	Board();
	void playerScore();
	void displayEnemy();
	void displayPlayerShip();
	void beginMenu();
	void loseScreen();
	void winScreen();
	void startGameLoop();
	void resetGameLoop();
	~Board();
};
#endif
