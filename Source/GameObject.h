#pragma once
#include "Sprite.h"
#include <string>
class GameObject {
private:
	Sprite* sprite = NULL;
protected:
	// Position and size of object
	std::string name;
	SDL_Rect* posRect;
	GameObject() {};
	void init(std::string name, SDL_Rect* posRect, Sprite* sprite);
public:
	GameObject(std::string name, SDL_Rect* posRect, Sprite* sprite);
	~GameObject();
	SDL_Rect* getPosRect();
	Sprite* getSprite();
};