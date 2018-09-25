#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Sprite {
private:
	// Position on the texture
	SDL_Rect* srcRect;
	SDL_Texture* texture;
public:
	Sprite(SDL_Rect* srcRect, SDL_Texture* texture);
	SDL_Rect* getSrcRect();
	SDL_Texture* getTexture();
	~Sprite();
};