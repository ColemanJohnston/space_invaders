/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include "ship.h"
#include "enemyShip.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
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
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				//Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
			}
		}
	}

	return success;
}

void close()
{

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

int main( int argc, char* args[] )
{
	srand ((unsigned)time(0));
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//The dot that will be moving around on the screen
		Ship titanic(gRenderer);

		enemyShip enemies[10][10];
		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				enemies[i][j].setRenderer(gRenderer);
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
				titanic.handleEvent( e );
			}

			//Move the ship and check collision
			titanic.move();
			
			for(int i = 0; i < 10; i++)
			{
				for(int j = 0; j < 10; j++)
				{
					enemies[i][j].move(enemies);
				}
			}
			//Clear screen
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );
			int r;
			int c;

			SDL_Rect enemyBeam;
			if(rand() % 121 == 0)
			{
				do
				{
					r = rand() % 10;
					c = rand() % 10;
				}while(!enemies[r][c].shoot());
			}		
			//TODO: Fix beam collision into player ship.
			SDL_Rect shipCollisionBox = titanic.getShipCollisionBox();
			SDL_Rect tempBeamBox = titanic.getBeamBox();
			//Render ship
			titanic.render();
			for(int i = 0; i < 10; i++)
			{
				for(int j = 0; j < 10; j++)
				{
					
					SDL_Rect tempEnemyBox = enemies[i][j].getShipCollisionBox();
					enemyBeam = enemies[i][j].getBeamBox();

					if(SDL_HasIntersection(&tempBeamBox,&tempEnemyBox))
					{
						enemies[i][j].destroy();
						titanic.resetBeam();
					}
					if(SDL_HasIntersection(&enemyBeam,&shipCollisionBox))
					{
						titanic.destroy();
						enemies[i][j].resetBeam();
					}
					enemies[i][j].render();
				}
			}

			//enemies[1][1].render();

			//Update screen
			SDL_RenderPresent( gRenderer );
			
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}