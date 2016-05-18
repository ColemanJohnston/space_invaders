/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.

//Using SDL, SDL_image, standard IO, and strings
#include "ship.h"
#include "enemyShip.h"
#include "font.h"
#include "barrier.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <SDL2/SDL_ttf.h>
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

Mix_Music* gMusic;

//The window renderer
SDL_Renderer* gRenderer = NULL;
SDL_Texture* texture;
//lifes
int lifes = 3;


bool init()
{
	//Initialization flag
	bool success = true;
	TTF_Init();
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	//Error check later
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "5PAc3 1Nvadderrrzzz", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
	Mix_FreeMusic( gMusic );
	gMusic = NULL;
	//free memory

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

int main( int argc, char* args[] )
{
	int score = 0;

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
		Font font(gRenderer);

		//Disply the lives
		/*
		live1 = IMG_Load("./ship.bmp");
		texture = SDL_CreateTextureFromSurface(gRenderer, live1);
		SDL_BlitSurface(live1, NULL, gRenderer, NULL );
        //texture = SDL_CreateTextureFromSurface(renderer,surface);
   	 	//SDL_FreeSurface(live1);
		live2 = IMG_Load("./ship.bmp");
		//SDL_FreeSurface(live2);
		live3 = IMG_Load("./ship.bmp");
		//SDL_FreeSurface(live3);
		


		enemyShip enemies[10][10];

		//barrier
		Barrier barrier1[10][10];
		int XLocation = 100;
		int Ylocation = 380;
		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				barrier1[i][j].setRenderer(gRenderer);
				barrier1[i][j].setX(XLocation);
				barrier1[i][j].setY(Ylocation);
				Ylocation+=5;
			}
			Ylocation = 380;
			XLocation+=5;
		}
		Barrier barrier2[10][10];
		XLocation = 250;
		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				barrier2[i][j].setRenderer(gRenderer);
				barrier2[i][j].setX(XLocation);
				barrier2[i][j].setY(Ylocation);
				Ylocation+=5;
			}
			Ylocation = 380;
			XLocation+=5;
		}
		Barrier barrier3[10][10];
		XLocation = 400;
		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				barrier3[i][j].setRenderer(gRenderer);
				barrier3[i][j].setX(XLocation);
				barrier3[i][j].setY(Ylocation);
				Ylocation+=5;
			}
			Ylocation = 380;
			XLocation+=5;
		}

		//Barrier barriers[3];
		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				enemies[i][j].setRenderer(gRenderer);
				enemies[i][j].setX(j * 30);
				enemies[i][j].setY(i * 30);
			}
		}
		//Load music
	gMusic = Mix_LoadMUS( "./Back_to_the_place_PSG.wav" );
	
	Mix_PlayMusic( gMusic, -1 );
	if( gMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
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
			SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
			SDL_RenderClear( gRenderer );
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

			//TODO: Fix beam collision into player ship.
			SDL_Rect shipCollisionBox = titanic.getShipCollisionBox();
			//SDL_Rect 
			SDL_Rect tempBeamBox = titanic.getBeamBox();
			SDL_Rect enemyBeam;
			SDL_Rect barriersBox;
			//Render ship
			titanic.render();
			//font.display(250, 250, 35, 35, "Hello");
			//SCREEN_WIDTH = 640;//Coleman: make sure ship knows screen size
			//SCREEN_HEIGHT = 480
			font.display(250, 250, 35, 35, to_string(score));
			if(lifes == 3)
			{
				//lifeRec1.w = 0;
				//lifeRec1.h = 0;
				titanic.render(618, 0);
				titanic.render(593, 0);
				titanic.render(568, 0);
			}
			else if(lifes == 2)
			{
				//lifeRec2.w = 0;
				//lifeRec2.h = 0;
				titanic.render(593, 0);
				titanic.render(568, 0);

			}
			else if(lifes == 1)
			{
				//lifeRec3.w = 0;
				//lifeRec3.h = 0;
				titanic.render(568, 0);
			}

			//SDL_Rect lifeRec1;

			//titanic.render(0, 1);
			//titanic.render(0, 2);
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
						titanic.resetBeam();
					}

					barriersBox = barrier2[i][j].getCollisionBox();
					if(SDL_HasIntersection(&tempBeamBox, &barriersBox))
					{
						barrier2[i][j].destroy();
						titanic.resetBeam();
					}

					barriersBox = barrier3[i][j].getCollisionBox();
					if(SDL_HasIntersection(&tempBeamBox, &barriersBox))
					{
						barrier3[i][j].destroy();
						titanic.resetBeam();
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
						titanic.resetBeam();
					}
					if(SDL_HasIntersection(&enemyBeam,&shipCollisionBox))
					{
						lifes--;
						if(lifes == 0)
						{
							titanic.destroy();
						}
						//titanic.destroy();
						enemies[i][j].resetBeam();
					}
					enemies[i][j].render();
				}
			}


			//enemies[1][1].render();
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
			//barriers[0].render();
			//barriers[1].render();
			//barriers[2].render();

			//Update screen

			SDL_RenderPresent( gRenderer );
			
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}*/
