#include "Paddle.h"
#include "Globals.h"
#include <iostream>
Paddle::Paddle(SDL_Renderer* renderer) {
	name = "Paddle";
	posX = (float)(Globals::SCREEN_WIDTH / 2 - width / 2);
	posY = (float)(Globals::SCREEN_HEIGHT - height);
	SDL_Rect* posRect = new SDL_Rect();
	posRect->x = (int)posX;
	posRect->y = (int)posY;
	posRect->h = height;
	posRect->w = width;
	
	init(name, posRect, new Sprite(NULL, IMG_LoadTexture(renderer, imgPath.c_str())));
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

	if (movingRight) {
		posX += movementSpeed * deltaTime;
	}
	else if (movingLeft) {
		posX -= movementSpeed * deltaTime;
	}

	posRect->x = (int)posX;
	posRect->y = (int)posY;

	

}
