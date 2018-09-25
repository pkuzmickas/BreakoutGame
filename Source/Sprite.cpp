#include "Sprite.h"

Sprite::Sprite(SDL_Rect posRect, SDL_Rect* srcRect, SDL_Texture * texture) {
	this->srcRect = srcRect;
	this->texture = texture;
}

SDL_Rect * Sprite::getSrcRect() {
	return srcRect;
}

SDL_Texture * Sprite::getTexture() {
	return texture;
}

Sprite::~Sprite() {
	SDL_DestroyTexture(texture);
	texture = NULL;
	delete srcRect;
	srcRect = NULL;
}
