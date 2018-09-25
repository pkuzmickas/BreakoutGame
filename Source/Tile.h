#pragma once
#include "GameObject.h"
class Tile : public GameObject {
private:
	std::string imgPath;
	int hp = 0; // How many hits does it take to destroy the tile
public:
	Tile(SDL_Renderer* renderer, int posX, int posY, int hp);
};