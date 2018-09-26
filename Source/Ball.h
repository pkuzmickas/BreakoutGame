#pragma once
#include "GameObject.h"

class Ball : public GameObject {
private:
	std::string imgPath = "Assets/ball.png";
	int speed = 100;
	float posX;
	float posY;
	enum BallState {
		NOT_LAUNCHED,
		LAUNCHED
	};
	BallState state = NOT_LAUNCHED;
	class Paddle* paddle;
	void resetBallLocation();
public:
	Ball(SDL_Renderer* renderer, class Paddle* paddle);
	void update(float deltaTime);
};