#include "BreakoutGame.h"
#include "Globals.h"
#undef main

using namespace std;

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	if (TTF_Init() == -1)
		cout << "TTF NOT INIT" << endl;
	SDL_StopTextInput(); // Because previously it would be on by default for some reason
	SDL_Window* gWindow = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, SDL_WINDOW_SHOWN /*|| SDL_WINDOW_FULLSCREEN*/);
	SDL_Renderer* gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	// Sets the draw color (in case there will be any GUI drawing with SDL)
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);

	BreakoutGame game(gRenderer);
	game.runGame();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
	return 0;
}

