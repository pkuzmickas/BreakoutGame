#pragma once
#include "Sprite.h"
class GameObject {
private:
	// Position and size of object
	SDL_Rect posRect;
	Sprite* sprite = NULL;
public:
	GameObject(SDL_Rect posRect, Sprite* sprite);
	~GameObject();
	SDL_Rect getPosRect();
	Sprite* getSprite();
};