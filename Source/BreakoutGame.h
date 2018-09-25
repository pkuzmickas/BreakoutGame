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
	Uint32 runTime;
	float deltaTime;
	bool gameRunning = false;
	Graphics* graphics;
	class Paddle* paddle = NULL;
	vector<class Tile*> tiles;
};