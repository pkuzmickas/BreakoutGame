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
	class Ball* ball = NULL;
	class Physics* physics = NULL;
	vector<class Tile*> tiles;

	int ballsLeft;
	int score = 0;
	int scoreOnText = 0;

	void loadTilesFromFile(std::string path);
	void checkTiles();
	void checkStats();
	void restartGame();
	SDL_Texture* createTextTexture(int fontSize, std::string text);
	GameObject* createText(SDL_Texture* textTexture, SDL_Rect* posRect);

	enum GameState {
		MENU,
		PLAYING
	};

	GameState gameState = MENU;
	GameObject* menuScreen = NULL;
	GameObject* ballCount = NULL;
	GameObject* scoreCount = NULL;
};