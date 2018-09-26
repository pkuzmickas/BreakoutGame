#include "Sprite.h"

Sprite::Sprite(SDL_Rect* srcRect, SDL_Texture * texture) {
	this->srcRect = srcRect;
	this->texture = texture;
}

SDL_Rect * Sprite::getSrcRect() {
	return srcRect;
}

SDL_Texture * Sprite::getTexture() {
	return texture;
}

void Sprite::setTexture(SDL_Renderer* renderer, const char* path) {
	SDL_DestroyTexture(texture);
	texture = IMG_LoadTexture(renderer, path);
}

void Sprite::setTexture(SDL_Texture * texture) {
	SDL_DestroyTexture(this->texture);
	this->texture = texture;
}

Sprite::~Sprite() {
	SDL_DestroyTexture(texture);
	texture = NULL;
	delete srcRect;
	srcRect = NULL;
}
