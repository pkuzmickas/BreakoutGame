#include "BreakoutGame.h"

BreakoutGame::BreakoutGame(SDL_Renderer* renderer) {
	this->renderer = renderer;
	graphics = new Graphics(renderer);
}

BreakoutGame::~BreakoutGame() {
	delete graphics;
}

void BreakoutGame::runGame() {
	gameRunning = true;

	// Game loop
	while (gameRunning) {
		handleInput();
		update();
		graphics->draw();
	}
}

void BreakoutGame::handleInput() {
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			gameRunning = false;
		}
	}
}

void BreakoutGame::update() {

}


