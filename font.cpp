#include "font.h"

Font::Font()
{
	x = 0;
	y = 0;

}
Font::Font(SDL_Renderer* renderer)
{
<<<<<<< HEAD
	this->renderer = renderer;
	fontType = TTF_OpenFont("PressStart2P.ttf", 30); //this opens a font style and sets a size
	color = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
=======

	this->renderer = renderer; //this opens a font style and sets a size
	color = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	fontSize = 40;
	fontType = TTF_OpenFont("PressStart2P.ttf", fontSize);
>>>>>>> 6dc8daaa62adc92a20b612b5ab3ddaa9e4c66fc0
	surfaceMessage = TTF_RenderText_Solid(fontType, "yes", color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 5;  //controls the rect's x coordinate 
	Message_rect.y = 5; // controls the rect's y coordinte
	Message_rect.w = 0; // controls the width of the rect
	Message_rect.h = 0; // controls the height of the rect
}

void Font::display(int x, int y, int width, int height, string text, int fontSize)
{
	//fontType = TTF_OpenFont("PressStart2P.ttf", 24); //this opens a font style and sets a size
//	fontType = TTF_OpenFont("PressStart2P.ttf", font);
	setFontSize(fontSize);
	surfaceMessage = TTF_RenderText_Solid(fontType, text.c_str(), color);
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	//SDL_Rect textBox;
	SDL_Rect textBoxCopy;
	textBox.x = x;
	textBox.y = y;
	textBox.w = width;
	textBox.h = height;
	SDL_RenderCopy(renderer, Message,0, &textBox);


}
void Font::display(int x, int y, int width, int height, string text)
{
	//fontType = TTF_OpenFont("PressStart2P.ttf", 24); //this opens a font style and sets a size
	//fontType = TTF_OpenFont("PressStart2P.ttf", font);
	surfaceMessage = TTF_RenderText_Solid(fontType, text.c_str(), color);
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	//SDL_Rect textBox;
	SDL_Rect textBoxCopy;
	textBox.x = x;
	textBox.y = y;
	textBox.w = width;
	textBox.h = height;
	SDL_RenderCopy(renderer, Message,0, &textBox);
	SDL_FreeSurface(surfaceMessage);



}


void Font::destroy()
{
	SDL_FreeSurface(surfaceMessage);
	SDL_SetRenderDrawColor(renderer,0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear( renderer );		
	SDL_RenderCopy(renderer, Message, NULL, &textBox);//you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
	SDL_RenderPresent( renderer );
	textBox.w = 0;
	textBox.h = 0;
	
}
void Font::setFontSize(int fontSize)
{
	this->fontSize=fontSize;
}