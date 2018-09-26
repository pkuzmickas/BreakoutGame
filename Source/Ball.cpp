#include "Ball.h"
#include "Paddle.h"
#include "Globals.h"
#include <iostream>
using namespace std;

void Ball::resetBallLocation() {
	posX = paddle->getPosRect()->x + Globals::PADDLE_WIDTH / 2 - Globals::BALL_SIZE / 2;
	posY = paddle->getPosRect()->y - Globals::BALL_SIZE;
	posRect->x = (int)posX;
	posRect->y = (int)posY;
}

Ball::Ball(SDL_Renderer * renderer, Paddle* paddle) {
	if (!paddle) {
		cout << "Paddle has to be initialized before the ball can be created!" << endl;
		return;
	}
	this->paddle = paddle;
	name = "Ball";
	posRect = new SDL_Rect();
	posRect->h = Globals::BALL_SIZE;
	posRect->w = Globals::BALL_SIZE;
	resetBallLocation();

	init(name, posRect, new Sprite(NULL, IMG_LoadTexture(renderer, imgPath.c_str())));
}

void Ball::update(float deltaTime) {
	if (state == NOT_LAUNCHED) {
		resetBallLocation();
	}
}
