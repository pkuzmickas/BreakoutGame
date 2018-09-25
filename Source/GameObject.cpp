#include "GameObject.h"

GameObject::GameObject(SDL_Rect posRect, Sprite * sprite) {
	this->posRect = posRect;
	this->sprite = sprite;
}

GameObject::~GameObject() {
	delete sprite;
}

SDL_Rect GameObject::getPosRect() {
	return posRect;
}

Sprite * GameObject::getSprite() {
	return sprite;
}
