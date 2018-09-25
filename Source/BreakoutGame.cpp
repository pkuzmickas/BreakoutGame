#include "BreakoutGame.h"
#include "Globals.h"
#include "Paddle.h"
#include "Tile.h"
#include <fstream>
#include <iostream>
#include <string>

BreakoutGame::BreakoutGame(SDL_Renderer* renderer) {
	this->renderer = renderer;
	graphics = new Graphics(renderer);
	runTime = SDL_GetTicks();
	paddle = new Paddle(renderer);
	graphics->addToDraw(paddle);

	ifstream file("Assets/tiles.txt");
	char tileHp;
	int col = -1;
	int row = 0;
	int tileCount = 0;

	if (file.is_open())
	{
		while (file >> tileHp) {
			if (isdigit(tileHp) == 0) {
				cout << "Read character is not a number! Stopping the reading." << endl;
				break;
			}
			col++;
			if (col == Globals::MAX_COLUMNS) {
				col = 0;
				row++;
				if (row == Globals::MAX_ROWS) {
					cout << "Maximum amount of rows was reached! Stopping the reading." << endl;
					break;
				}
			}
			tileCount++;
			int hp = tileHp - '0';
			if (hp == 0) {
				continue;
			}
			Tile* tile = new Tile(renderer, col * Globals::TILE_WIDTH, Globals::SPACE_TOP + row * Globals::TILE_HEIGHT, hp);
			tiles.push_back(tile);
			graphics->addToDraw(tile);
		}
		file.close();
	}
	else cout << "Unable to open file";
	if (tileCount != Globals::MAX_ROWS*Globals::MAX_COLUMNS) {
		cout << "File was read wrong! The game might not function properly!" << endl;;
	}
}

BreakoutGame::~BreakoutGame() {
	delete graphics;
	delete paddle;
	for (auto tile : tiles) {
		delete tile;
	}
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
	auto dt = SDL_GetTicks() - runTime; // In miliseconds
	runTime += dt;
	deltaTime = (float)dt / 1000; // In seconds

	paddle->update(deltaTime);

	Globals::GetFrameEvents().clear();
}


