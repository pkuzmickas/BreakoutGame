#pragma once
#include "GameObject.h"

class Ball : public GameObject {
private:
	std::string imgPath = "Assets/ball.png";
	int speed = 700;
	float posX;
	float posY;
	float velX = 0;
	float velY = 0;
	enum BallState {
		NOT_LAUNCHED,
		LAUNCHED
	};
	BallState state = NOT_LAUNCHED;
	class Paddle* paddle;
	class Physics* physics;
	void resetBallLocation();
public:
	Ball(SDL_Renderer* renderer, class Paddle* paddle, class Physics* physics);
	void update(float deltaTime);
};