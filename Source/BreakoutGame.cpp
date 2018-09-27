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

	resultScreen = new GameObject(
		"ResultScreen",
		new SDL_Rect({ 0, 0, Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT }),
		new Sprite(NULL, IMG_LoadTexture(renderer, MENU_FILE_PATH))
	);
	

	// For the lose screen score text
	SDL_Texture* scoreTexture = createTextTexture(FONT_FILE_PATH, 25, "Score: 00", { 0, 0, 0});
	int w, h;
	SDL_QueryTexture(scoreTexture, NULL, NULL, &w, &h);
	scoreCountLoseScreen = createText(
		scoreTexture,
		new SDL_Rect({ Globals::SCREEN_WIDTH / 2 - w / 2, Globals::SCREEN_HEIGHT / 2 - h / 2, w, h })
	);

	graphics->addToDraw(resultScreen);
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
	if (resultScreen)
		delete resultScreen;
	if (ballCount)
		delete ballCount;
	if (scoreCount)
		delete scoreCount;
	if (scoreCountLoseScreen)
		delete scoreCountLoseScreen;
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
			if (e.key.keysym.sym == SDLK_RETURN) {
				if (gameState == MENU) {
					gameState = PLAYING;
					graphics->removeFromDraw(resultScreen);
					physics = new Physics();
					paddle = new Paddle(renderer);
					physics->addCollider(paddle);
					graphics->addToDraw(paddle);
					ball = new Ball(renderer, paddle, physics);
					graphics->addToDraw(ball);

					ballsLeft = ball->getBallsLeft();
					std::string balls = BALLS_TEXT;
					std::string text = balls + to_string(ballsLeft);
					SDL_Texture* ballCountTexture = createTextTexture(FONT_FILE_PATH, Globals::BOTTOMTEXT_FONT_SIZE, text.c_str(), { 255, 255, 255 });
					int w, h;
					SDL_QueryTexture(ballCountTexture, NULL, NULL, &w, &h);
					ballCount = createText(ballCountTexture, new SDL_Rect({ Globals::SCREEN_WIDTH - w, Globals::SCREEN_HEIGHT - h, w, h }));

					std::string scoreText = SCORE_TEXT;
					text = scoreText + to_string(scoreOnText);
					SDL_Texture* scoreTexture = createTextTexture(FONT_FILE_PATH, Globals::BOTTOMTEXT_FONT_SIZE, text.c_str(), { 255, 255, 255 });
					SDL_QueryTexture(scoreTexture, NULL, NULL, &w, &h);
					scoreCount = createText(scoreTexture, new SDL_Rect({ 0, Globals::SCREEN_HEIGHT - h, w, h }));

					text = "Ninja Kiwi";
					SDL_Texture* logoTexture = createTextTexture(NK_FONT, 140, text.c_str(), { 0, 0, 0, 0 });
					SDL_QueryTexture(logoTexture, NULL, NULL, &w, &h);
					nkLogo = createText(logoTexture, new SDL_Rect({ Globals::SCREEN_WIDTH/2 - w/2, Globals::SPACE_TOP + (Globals::MAX_ROWS+1) * Globals::TILE_HEIGHT / 2 - h/2, w, h }));

					graphics->addToDraw(ballCount);
					graphics->addToDraw(scoreCount);
					
					loadTilesFromFile(TILE_FILE_PATH);
					graphics->addToDraw(nkLogo, true);
				}
				else if (gameState == OVER) {
					graphics->removeFromDraw(resultScreen);
					graphics->removeFromDraw(scoreCountLoseScreen);
					restartGame();
				}
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

	if (gameState == PLAYING) {
		paddle->update(deltaTime);
		ball->update(deltaTime);

		checkTiles();
		checkStats();
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
			score++;
		}
	}
}

void BreakoutGame::checkStats() {
	int realBallsLeft = ball->getBallsLeft();
	if (realBallsLeft == 0) {
		gameState = OVER;
		graphics->removeFromDraw(nkLogo);
		resultScreen->getSprite()->setTexture(renderer, LOSE_FILE_PATH);
		graphics->addToDraw(resultScreen);
		std::string scoreText = SCORE_TEXT;
		std::string text = scoreText + to_string(scoreOnText);
		SDL_Texture* scoreTexture = createTextTexture(FONT_FILE_PATH, 25, text, { 0, 0, 0 });
		scoreCountLoseScreen->getSprite()->setTexture(scoreTexture);
		graphics->addToDraw(scoreCountLoseScreen);
	}
	if (ballsLeft != realBallsLeft) {
		ballsLeft = realBallsLeft;
		std::string balls = BALLS_TEXT;
		std::string text = balls + to_string(ballsLeft);
		ballCount->getSprite()->setTexture(createTextTexture(FONT_FILE_PATH, Globals::BOTTOMTEXT_FONT_SIZE, text.c_str(), {255, 255, 255}));
	}
	if (scoreOnText != score) {
		scoreOnText = score;
		std::string scoreText = SCORE_TEXT;
		std::string text = scoreText + to_string(scoreOnText);
		scoreCount->getSprite()->setTexture(createTextTexture(FONT_FILE_PATH, Globals::BOTTOMTEXT_FONT_SIZE, text.c_str(), { 255, 255, 255 }));
	}
	if (score == tiles.size()) {
		gameState = OVER;
		graphics->removeFromDraw(nkLogo);
		resultScreen->getSprite()->setTexture(renderer, WIN_FILE_PATH);
		graphics->addToDraw(resultScreen);
		std::string scoreText = SCORE_TEXT;
		std::string text = scoreText + to_string(scoreOnText);
		SDL_Texture* scoreTexture = createTextTexture(FONT_FILE_PATH, 25, text, { 0, 0, 0 });
		scoreCountLoseScreen->getSprite()->setTexture(scoreTexture);
		graphics->addToDraw(scoreCountLoseScreen);
	}

}

void BreakoutGame::restartGame() {
	for (auto tile : tiles) {
		if (!tile->isActive()) {
			graphics->addToDraw(tile);
			physics->addCollider(tile);
			tile->setActive(true);
		}
		tile->fullHp();
	}
	graphics->addToDraw(nkLogo, true);
	ball->restartBall();
	score = 0;
	ball->resetBalls();
	gameState = PLAYING;
	
}


SDL_Texture * BreakoutGame::createTextTexture(const char* fontPath, int fontSize, std::string text, SDL_Color color) {
	TTF_Font* textFont = TTF_OpenFont(fontPath, fontSize);
	SDL_Surface* textSurface = TTF_RenderText_Blended(textFont, text.c_str(), { color });
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



