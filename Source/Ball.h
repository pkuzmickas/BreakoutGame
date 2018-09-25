#pragma once
#include "GameObject.h"

class Ball : public GameObject {
private:
	std::string imgPath = "Assets/ball.png";
	int speed = 100;
	int posX;
	int posY;
public:
	Ball(SDL_Renderer* renderer, class Paddle* paddle);
	void update(float deltaTime);
};