#include "BreakoutGame.h"
#include "Globals.h"

BreakoutGame::BreakoutGame(SDL_Renderer* renderer) {
	this->renderer = renderer;
	graphics = new Graphics(renderer);
	runTime = SDL_GetTicks();
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

	while (SDL_PollEvent(&e) != 0) {
		Globals::GetFrameEvents().push_back(e);
	}
	for (auto e : Globals::GetFrameEvents()) {
		switch (e.type) {
		case SDL_QUIT:
			gameRunning = false;
			break;

		}
	}
}

void BreakoutGame::update() {
	deltaTime = SDL_GetTicks() - runTime;
	runTime += deltaTime;
}


