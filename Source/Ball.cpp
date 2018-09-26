#include "Ball.h"
#include "Paddle.h"
#include "Globals.h"
#include "Physics.h"
#include <math.h>
#include <iostream>
using namespace std;

void Ball::resetBallLocation() {
	posX = paddle->getPosRect()->x + Globals::PADDLE_WIDTH / 2 - Globals::BALL_SIZE / 2;
	posY = paddle->getPosRect()->y - Globals::BALL_SIZE;
	posRect->x = (int)posX;
	posRect->y = (int)posY;
}

Ball::Ball(SDL_Renderer * renderer, Paddle* paddle, Physics* physics) {
	if (!paddle) {
		cout << "Paddle has to be initialized before the ball can be created!" << endl;
		return;
	}
	this->paddle = paddle;
	this->physics = physics;
	name = "Ball";
	posRect = new SDL_Rect();
	posRect->h = Globals::BALL_SIZE;
	posRect->w = Globals::BALL_SIZE;
	resetBallLocation();

	init(name, posRect, new Sprite(NULL, IMG_LoadTexture(renderer, imgPath.c_str())));
}

void Ball::update(float deltaTime) {

	std::vector<SDL_Event> events = Globals::GetFrameEvents();
	//std::cout << "EVENT SIZE IN PLAYER INPUT:" << events.size() << std::endl;
	for (auto e : events) {
		switch (e.type) {

		case SDL_MOUSEBUTTONDOWN: {
			if (state == NOT_LAUNCHED) {
				state = LAUNCHED;
				velX = speed * 0.3;
				velY = -speed * 0.7;
			}
		}
								  break;
		}
	}


	if (state == NOT_LAUNCHED) {
		resetBallLocation();
	}
	else if (state == LAUNCHED) {
		// Change the ball position
		posX += velX * deltaTime;
		posY += velY * deltaTime;
		posRect->x = (int)posX;
		posRect->y = (int)posY;

		auto collision = physics->checkCollision(this);
		if (collision) {
			// If collided, get the ball position back to where it was
			posX -= velX * deltaTime;
			posY -= velY * deltaTime;
			posRect->x = (int)posX;
			posRect->y = (int)posY;

			SDL_Rect* colliderPos = collision->getPosRect();
			auto colliderName = collision->getName();

			if (colliderName == "Paddle") {
				// Location of the ball relative to the paddle
				// PADDLE CENTRE X - BALL CENTRE X
				//float relativeIntersectX = (colliderPos->x + (colliderPos->w / 2)) - (posRect->x + posRect->w / 2);
				//// Normalizing the position (-1 -> 1)
				//float normalizedRelativeIntersectionX = (relativeIntersectX / (colliderPos->w / 2));
				//// Getting the new bounce angle by multiplying the position of the ball by the maximum possible value
				//float bounceAngle = normalizedRelativeIntersectionX * Globals::MAX_BOUNCE_ANGLE_DEGREES;
				//velX = speed * cos(bounceAngle * PI / 180);
				//velY = speed * -sin(bounceAngle * PI / 180);
				velY *= -1;
			}
			else if (colliderName == "WallRight" || colliderName == "WallLeft") {
				velX *= -1;
			}
			else if (colliderName == "WallUp" || colliderName == "Tile") {
				velY *= -1;
			}

		}
		

	}

}


