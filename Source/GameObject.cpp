#include "GameObject.h"

void GameObject::init(std::string name, SDL_Rect* posRect, Sprite * sprite) {
	this->name = name;
	this->posRect = posRect;
	this->sprite = sprite;
}

GameObject::GameObject(std::string name, SDL_Rect* posRect, Sprite * sprite) {
	init(name, posRect, sprite);
}

GameObject::~GameObject() {
	delete sprite;
	sprite = NULL;
	delete posRect;
	posRect = NULL;
}

SDL_Rect* GameObject::getPosRect() {
	return posRect;
}

Sprite * GameObject::getSprite() {
	return sprite;
}
