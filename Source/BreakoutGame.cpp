#include "BreakoutGame.h"
#include "Globals.h"
#include "Paddle.h"
#include "Ball.h"
#include "Tile.h"
#include "Physics.h"
#include <fstream>
#include <iostream>
#include <string>

BreakoutGame::BreakoutGame(SDL_Renderer* renderer) {
	this->renderer = renderer;
	graphics = new Graphics(renderer);
	runTime = SDL_GetTicks();
	
	menuScreen = new GameObject(
		"MenuScreen",
		new SDL_Rect({ 0, 0, Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT }),
		new Sprite(NULL, IMG_LoadTexture(renderer, MENU_FILE_PATH))
	);

	graphics->addToDraw(menuScreen);
}

BreakoutGame::~BreakoutGame() {
	if (graphics)
		delete graphics;
	if (paddle)
		delete paddle;
	for (auto tile : tiles) {
		if (tile)
			delete tile;
	}
	if (ball)
		delete ball;
	if (physics)
		delete physics;
	if (menuScreen)
		delete menuScreen;
	if (ballCount)
		delete ballCount;
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
		case SDL_QUIT: {
			gameRunning = false;
			break;
		}
		case SDL_KEYDOWN: {
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				gameRunning = false;
			}
			if (gameState == MENU && e.key.keysym.sym == SDLK_RETURN) {
				gameState = PLAYING;
				graphics->removeFromDraw(menuScreen);
				physics = new Physics();
				paddle = new Paddle(renderer);
				physics->addCollider(paddle);
				graphics->addToDraw(paddle);
				ball = new Ball(renderer, paddle, physics);
				graphics->addToDraw(ball);

				ballsLeft = ball->getBallsLeft();
				std::string balls = BALLS_TEXT;
				std::string text = balls + to_string(ballsLeft);
				SDL_Texture* ballCountTexture = createTextTexture(Globals::BOTTOMTEXT_FONT_SIZE, text.c_str());
				int w, h;
				SDL_QueryTexture(ballCountTexture, NULL, NULL, &w, &h);
				ballCount = createText(ballCountTexture, new SDL_Rect({ Globals::SCREEN_WIDTH - w, Globals::SCREEN_HEIGHT - h, w, h }));
				
				std::string scoreText = SCORE_TEXT;
				text = scoreText + to_string(score);
				SDL_Texture* scoreTexture = createTextTexture(Globals::BOTTOMTEXT_FONT_SIZE, text.c_str());
				SDL_QueryTexture(scoreTexture, NULL, NULL, &w, &h);
				scoreCount = createText(scoreTexture, new SDL_Rect({ 0, Globals::SCREEN_HEIGHT - h, w, h }));

				graphics->addToDraw(ballCount);
				graphics->addToDraw(scoreCount);

				loadTilesFromFile(TILE_FILE_PATH);
			}
			break;
		}

		}
	}
}



void BreakoutGame::update() {
	auto dt = SDL_GetTicks() - runTime; // In miliseconds
	runTime += dt;
	deltaTime = (float)dt / 1000; // In seconds

	switch (gameState) {
	case MENU: {

		break;
	}
	case PLAYING: {
		paddle->update(deltaTime);
		ball->update(deltaTime);

		checkTiles();
		checkBall();
		break;
	}
	}



	Globals::GetFrameEvents().clear();
}

void BreakoutGame::loadTilesFromFile(std::string path) {
	ifstream file(path);
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
			physics->addCollider(tile);
		}
		file.close();
	}
	else cout << "Unable to open file";
	if (tileCount != Globals::MAX_ROWS*Globals::MAX_COLUMNS) {
		cout << "File was read wrong! The game might not function properly!" << endl;;
	}
}

void BreakoutGame::checkTiles() {
	for (auto tile : tiles) {
		if (tile->getHpLeft() == 0 && tile->isActive()) {
			graphics->removeFromDraw(tile);
			physics->removeCollider(tile);
			tile->setActive(false);
		}
	}
}

void BreakoutGame::checkBall() {
	int realBallsLeft = ball->getBallsLeft();
	if (ballsLeft != realBallsLeft) {
		ballsLeft = realBallsLeft;
		std::string balls = BALLS_TEXT;
		std::string text = balls + to_string(ballsLeft);
		ballCount->getSprite()->setTexture(createTextTexture(Globals::BOTTOMTEXT_FONT_SIZE, text.c_str()));
	}
}

void BreakoutGame::restartGame() {
	//tile->setActive(true);
}


SDL_Texture * BreakoutGame::createTextTexture(int fontSize, std::string text) {
	TTF_Font* textFont = TTF_OpenFont(FONT_FILE_PATH, fontSize);
	SDL_Surface* textSurface = TTF_RenderText_Blended(textFont, text.c_str(), { 255,255,255 });
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(textFont);
	return textTexture;
}

GameObject * BreakoutGame::createText(SDL_Texture * textTexture, SDL_Rect * posRect) {
	return new GameObject(
		"text",
		posRect,
		new Sprite(NULL, textTexture)
	);
}



