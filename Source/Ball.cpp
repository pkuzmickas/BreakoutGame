#include "Ball.h"
#include "Paddle.h"
#include "Globals.h"
#include "Physics.h"
#include "Tile.h"
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
	this->renderer = renderer;
	this->paddle = paddle;
	this->physics = physics;
	ballsLeft = Globals::MAX_BALLS;
	name = "Ball";
	posRect = new SDL_Rect();
	posRect->h = Globals::BALL_SIZE;
	posRect->w = Globals::BALL_SIZE;
	resetBallLocation();

	init(name, posRect, new Sprite(NULL, IMG_LoadTexture(renderer, BALL_FILE_PATH)));
}

void Ball::update(float deltaTime) {

	std::vector<SDL_Event> events = Globals::GetFrameEvents();
	//std::cout << "EVENT SIZE IN PLAYER INPUT:" << events.size() << std::endl;
	for (auto e : events) {
		switch (e.type) {

		case SDL_MOUSEBUTTONDOWN: {
			if (!ballLaunched) {
				ballLaunched = true;
				velX = speed * 0.3;
				velY = -speed * 0.7;
			}
		}
			break;

		case SDL_KEYDOWN: {
			if (e.key.keysym.sym == SDLK_SPACE && !ballLaunched) {
				ballLaunched = true;
				velX = speed * 0.3;
				velY = -speed * 0.7;
			}

		}
			break;
		}
	}


	if (!ballLaunched) {
		resetBallLocation();
	}
	else if (ballLaunched) {
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

			if (isColorBright) {
				isColorBright = false;
				getSprite()->setTexture(renderer, BALL_FILE_PATH);
			}
			else {
				isColorBright = true;
				getSprite()->setTexture(renderer, BALL_FILE_PATH2);
			}

			if (colliderName == "Paddle") {
				// Location of the ball relative to the paddle
				// PADDLE CENTRE X - BALL CENTRE X
				//float relativeIntersectX = (posRect->x + posRect->w / 2) - (colliderPos->x + (colliderPos->w / 2)) ;
				//// Normalizing the position (-1 -> 1)
				//float normalizedRelativeIntersectionX = (relativeIntersectX / (colliderPos->w / 2));
				// //Getting the new bounce angle by multiplying the position of the ball by the maximum possible value
				//float bounceAngle = normalizedRelativeIntersectionX * Globals::MAX_BOUNCE_ANGLE_DEGREES;
				//
				////auto bounceAngle = relativeIntersectX / (PI / 3);
				//velX = speed * cos(bounceAngle * PI/180);
				//velY = speed * sin(bounceAngle * PI/180);

				
				// 3 AM, something's wrong with my maths, can't figure it out now, simple solution below

				velY *= -1;
			}
			else if (colliderName == "WallRight" || colliderName == "WallLeft") {
				velX *= -1;
			}
			else if (colliderName == "WallUp" || colliderName == "Tile") {
				velY *= -1;
				if (colliderName == "Tile") {
					((Tile*)collision)->tileHit();
				}
			}
			else if (colliderName == "WallDown") {
				ballsLeft--;
				restartBall();
			}

		}
		

	}

}

void Ball::restartBall() {
	ballLaunched = false;
}

int Ball::getBallsLeft() {
	return ballsLeft;
}

void Ball::resetBalls() {
	ballsLeft = Globals::MAX_BALLS;
}


