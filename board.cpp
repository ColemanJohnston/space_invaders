#include "ship.h"
#include "board.h"
#include "enemyShip.h"
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

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
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
				Mix_PlayMusic( music, -1 );
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
		}
	}
	//set the renderer for the player ship
	playerShip.setRenderer(renderer);
}

//********************************************************************************************************************************
void Board::playerScore()
{
	
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
	//Start up SDL and create window

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//barrier
	int XLocation = 100;
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
	
	XLocation = 250;
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

	XLocation = 400;
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

	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
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
				enemies[i][j].move(enemies);
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
		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				
				SDL_Rect tempEnemyBox = enemies[i][j].getShipCollisionBox();
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
					playerShip.resetBeam();
				}
				if(SDL_HasIntersection(&enemyBeam,&shipCollisionBox))
				{
					playerShip.destroy();
					enemies[i][j].resetBeam();
				}
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
	
}
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