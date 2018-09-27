#pragma once
#include "GameObject.h"

class Ball : public GameObject {
private:
	int speed = 750;
	float posX;
	float posY;
	float velX = 0;
	float velY = 0;
	int ballsLeft;
	bool ballLaunched = false;
	class Paddle* paddle;
	class Physics* physics;
	void resetBallLocation();
	SDL_Renderer* renderer;
	bool isColorBright = false;
public:
	Ball(SDL_Renderer* renderer, class Paddle* paddle, class Physics* physics);
	void update(float deltaTime);
	void restartBall();
	int getBallsLeft();
	void resetBalls();
};