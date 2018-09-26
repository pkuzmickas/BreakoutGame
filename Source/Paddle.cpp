#include "Paddle.h"
#include "Globals.h"
#include <iostream>
Paddle::Paddle(SDL_Renderer* renderer) {
	name = "Paddle";
	posX = (float)(Globals::SCREEN_WIDTH / 2 - Globals::PADDLE_WIDTH / 2);
	posY = (float)(Globals::SCREEN_HEIGHT - Globals::BOTTOM_DISTANCE);
	posRect = new SDL_Rect();
	posRect->x = (int)posX;
	posRect->y = (int)posY;
	posRect->h = Globals::PADDLE_HEIGHT;
	posRect->w = Globals::PADDLE_WIDTH;
	
	init(name, posRect, new Sprite(NULL, IMG_LoadTexture(renderer, PADDLE_FILE_PATH)));
}

void Paddle::update(float deltaTime) {
	std::vector<SDL_Event> events = Globals::GetFrameEvents();
	for (auto e : events) {
		switch (e.type) {

		case SDL_KEYDOWN: {
			// Handles the movement keys
			if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT) {
				movingRight = true;				
			}
			if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_LEFT) {
				movingLeft = true;
			}
			break;
		}
		case SDL_KEYUP: {
			// Handles the movement keys
			if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT) {
				movingRight = false;
			}
			if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_LEFT) {
				movingLeft = false;
			}
			break;
		}

		}
	}

	float velocity = movementSpeed * deltaTime;

	if (movingRight) {
		if (posX + velocity <= Globals::SCREEN_WIDTH - Globals::PADDLE_WIDTH) {
			posX += velocity;
		}
	}
	else if (movingLeft) {
		if (posX - velocity >= 0) {
			posX -= velocity;
		}
	}

	posRect->x = (int)posX;
	posRect->y = (int)posY;

	

}
