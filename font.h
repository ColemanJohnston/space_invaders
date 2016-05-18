#ifndef FONT_H
#define FONT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;
class Font
{
	public:
		static const int SCREEN_WIDTH = 640;
		static const int SCREEN_HEIGHT = 480;
		Font();
		Font(SDL_Renderer* renderer);
		~Font(){SDL_DestroyTexture(Message);}

		//void render();
		void display(int x, int y, int width, int height, string text);
		void destroy();

	protected:
		SDL_Color color;
		SDL_Renderer* renderer;
		SDL_Surface* surfaceMessage;
		SDL_Texture* Message;
		TTF_Font* fontType;
		SDL_Rect textBox;

		//X and Y position
		int x;
		int y;
};
#endif