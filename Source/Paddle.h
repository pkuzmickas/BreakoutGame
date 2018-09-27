#pragma once
#include "GameObject.h"
class Paddle : public GameObject {
private:
	// These two get set in the constructor
	float posX = 0;
	float posY = 0;

	bool movingLeft = false;
	bool movingRight = false;
	int movementSpeed = 600;
public:
	Paddle(SDL_Renderer* renderer);
	void update(float deltaTime);

};