#include "ship.h"
#include "board.h"
#include "enemyShip.h"
#include "font.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

Board::Board()
{
	//Initialize flag
	bool success = true;
	TTF_Init();

	//Initialize SDL
	TTF_Init();
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texfture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		window = SDL_CreateWindow( "Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if(window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				//Initialize music
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }

                music = Mix_LoadMUS( "./Back_to_the_place_PSG.wav" );
				Mix_PlayMusic( music, 3 );
				if( music == NULL )
				{
					printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
				}

			}


		}
	}
	if(!success)
	{
		exit(0);
	}
	//set rederers for barrier and enemy objects
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			barrier1[i][j].setRenderer(renderer);
			barrier2[i][j].setRenderer(renderer);
			barrier3[i][j].setRenderer(renderer);
			enemies[i][j].setRenderer(renderer);
			barrier1[i][j].initAudio();
			barrier2[i][j].initAudio();
			barrier3[i][j].initAudio();
			enemies[i][j].initAudio();
		}
	}
	//set the renderer for the player ship
	playerShip.setRenderer(renderer);
	playerShip.initAudio();
}

//********************************************************************************************************************************
void Board::playerScore(Font &font)
{
<<<<<<< HEAD
	//Font font(renderer);
	//font.display(250, 250, 35, 35, to_string(score));
=======
	font.display(10, 0, 40, 35, "Score: " + to_string(score));
>>>>>>> 6dc8daaa62adc92a20b612b5ab3ddaa9e4c66fc0
}

//********************************************************************************************************************************
void Board::displayEnemy()
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			enemies[i][j].render();
		}
	}
}

//********************************************************************************************************************************
void Board::displayPlayerShip()
{
	playerShip.render();
}

//********************************************************************************************************************************
void Board::beginMenu()
{
	SDL_Event e;

	Ship playerMenu(renderer);
	enemyShip enemyStart(renderer, 210, SCREEN_HEIGHT/2),
	enemyQuit(renderer,410, SCREEN_HEIGHT/2);
	Font startFont(renderer);
	Font quitFont(renderer);
	enemyStart.initAudio();
	enemyQuit.initAudio();
	playerMenu.initAudio();

	bool quit = false;
	while(!quit)
	{
		while(SDL_PollEvent( &e) != 0)
		{
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			playerMenu.handleEvent( e );
		}

		playerMenu.move();
		SDL_Rect startCollisionBox = enemyStart.getShipCollisionBox();
		SDL_Rect quitCollisionBox = enemyQuit.getShipCollisionBox();
		SDL_Rect tempBeamBox = playerMenu.getBeamBox();

		if(SDL_HasIntersection(&tempBeamBox, &startCollisionBox))
		{
			startGameLoop();
			playerMenu.resetBeam();
		}
		if(SDL_HasIntersection(&tempBeamBox, &quitCollisionBox))
		{
			quit = true;
		}

		SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );
		SDL_RenderClear( renderer );

		playerMenu.render();
		enemyStart.render();
		enemyQuit.render();
		startFont.display(200, 200, 40, 35, "START");
		quitFont.display(400, 200, 40, 35, "QUIT");
		SDL_RenderPresent( renderer );
	}
}

//********************************************************************************************************************************
void Board::loseScreen()
{

}

//********************************************************************************************************************************
void Board::winScreen()
{
	
}

//********************************************************************************************************************************
void Board::startGameLoop()
{
	srand ((unsigned)time(0));
	resetGameLoop();
	//Start up SDL and create window

	//Main loop flag

	bool quit = false;
	bool isInBottom = false;
	Font font(renderer);
	//Event handler
	SDL_Event e;
	Font font(renderer);
	//int score = 0;

	//barrier
	int XLocation = 113;
	int Ylocation = 380;
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			barrier1[i][j].setX(XLocation);
			barrier1[i][j].setY(Ylocation);
			Ylocation+=5;
		}
		Ylocation = 380;
		XLocation+=5;
	}
	
	XLocation = 276;
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			barrier2[i][j].setX(XLocation);
			barrier2[i][j].setY(Ylocation);
			Ylocation+=5;
		}
		Ylocation = 380;
		XLocation+=5;
	}

	XLocation = 439;
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			barrier3[i][j].setX(XLocation);
			barrier3[i][j].setY(Ylocation);
			Ylocation+=5;
		}
		Ylocation = 380;
		XLocation+=5;
	}

	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			enemies[i][j].setX(j * 30);
			enemies[i][j].setY(i * 30);
		}
	}

	while( !quit && !isInBottom)
	{
		if((score + 1 )%101 == 0)
		{
			int tempScore = score;
			resetGameLoop();
			score = tempScore;

		}
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
				score = 0;
			}

			//Handle input for the dot
			playerShip.handleEvent( e );
		}

		//Move the ship and check collision
		playerShip.move();
		
		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				enemies[i][j].move(enemies, isInBottom);
				/*
				if(isInBottom)
				{
					Font gameOver(renderer);
					gameOver.display(200, 200, 50 , 50, "GAME OVER");
				}
				*/
			}
		}
		//Clear screen
		SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );
		SDL_RenderClear( renderer );
		int r;
		int c;

		if(rand() % 121 == 0)
		{
			do
			{
				r = rand() % 10;
				c = rand() % 10;
			}while(!enemies[r][c].shoot());
		}				

		SDL_Rect shipCollisionBox = playerShip.getShipCollisionBox(); 
		SDL_Rect tempBeamBox = playerShip.getBeamBox();
		SDL_Rect enemyBeam;
		SDL_Rect barriersBox;
		//Render ship
		playerShip.render();
<<<<<<< HEAD
		//playerScore();
		font.display(250, 250, 35, 35, to_string(score));
=======
		playerScore(font);
		//font.display(50, 0, 35, 35, "Score: " + to_string(score));
>>>>>>> 6dc8daaa62adc92a20b612b5ab3ddaa9e4c66fc0

		if(lifes == 3)
			   {

				playerShip.render(618, 0);
				playerShip.render(593, 0);
				playerShip.render(568, 0);
			}
			else if(lifes == 2)
			{
				playerShip.render(593, 0);
				playerShip.render(568, 0);

			}
			else if(lifes == 1)
			{
				playerShip.render(568, 0);
			}

		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				
				SDL_Rect tempEnemyBox = enemies[i][j].getShipCollisionBox();
				if(tempEnemyBox.y + 20 > SCREEN_HEIGHT)
				{
					beginMenu();
				}
				enemyBeam = enemies[i][j].getBeamBox();
				barriersBox = barrier1[i][j].getCollisionBox();
				if(SDL_HasIntersection(&tempBeamBox, &barriersBox))
				{
					barrier1[i][j].destroy();
					playerShip.resetBeam();
				}

				barriersBox = barrier2[i][j].getCollisionBox();
				if(SDL_HasIntersection(&tempBeamBox, &barriersBox))
				{
					barrier2[i][j].destroy();
					playerShip.resetBeam();
				}

				barriersBox = barrier3[i][j].getCollisionBox();
				if(SDL_HasIntersection(&tempBeamBox, &barriersBox))
				{
					barrier3[i][j].destroy();
					playerShip.resetBeam();
				}
				for(int k = 0; k < 10; k++)
				{
					for(int l = 0; l < 10; l++)
					{
						barriersBox = barrier1[k][l].getCollisionBox();
						if(SDL_HasIntersection(&enemyBeam, &barriersBox))
						{
							barrier1[k][l].destroy();
							enemies[i][j].resetBeam();
						}
						barriersBox = barrier2[k][l].getCollisionBox();
						if(SDL_HasIntersection(&enemyBeam, &barriersBox))
						{
							barrier2[k][l].destroy();
							enemies[i][j].resetBeam();
						}
						barriersBox = barrier3[k][l].getCollisionBox();
						if(SDL_HasIntersection(&enemyBeam, &barriersBox))
						{
							barrier3[k][l].destroy();
							enemies[i][j].resetBeam();
						}
					}
				}


				if(SDL_HasIntersection(&tempBeamBox,&tempEnemyBox))
				{
					enemies[i][j].destroy();
					score++;
					playerShip.resetBeam();
					score++;
				}
				if(SDL_HasIntersection(&enemyBeam,&shipCollisionBox))
				{
					lifes--;
					if(lifes == 0)
					{	
						playerShip.destroy();
					}
					enemies[i][j].resetBeam();
				}
				/*
				if(SDL_HasIntersection(&enemies[i][j],&shipCollisionBox))
				{
					isInBottom = true;
				}
				*/
				enemies[i][j].render();
			}
		}

		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				barrier1[i][j].render();
			}
		}
		
		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				barrier2[i][j].render();
			}
		}
		
		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				barrier3[i][j].render();
			}
		}

			SDL_RenderPresent( renderer );
		}

		resetGameLoop();
}
//********************************************************************************************************************************
void Board::resetGameLoop()
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			barrier1[i][j].reset();
			barrier2[i][j].reset();
			barrier3[i][j].reset();
			enemies[i][j].reset();
		}
	}
	playerShip.reset();
	lifes = 3;
	score = 0;

}
//*********************************************************************************************************************************
Board::~Board()
{

	//Destroy window	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	Mix_FreeMusic(music);
	window = NULL;
	renderer = NULL;
	music = NULL;

	//Quit SDL
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}