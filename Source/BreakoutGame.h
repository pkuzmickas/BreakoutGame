#pragma once
#include "Graphics.h"
class BreakoutGame {
public:
	BreakoutGame(SDL_Renderer* renderer);
	~BreakoutGame();
	void runGame();
	void handleInput();
	void update();
private:
	SDL_Renderer* renderer = NULL;
	int runTime, deltaTime;
	bool gameRunning = false;
	Graphics* graphics;
};