#pragma once
#include "GameObject.h"
class Tile : public GameObject {
private:
	std::string imgPath;
	int hpLeft = 0; // How many hits does it take to destroy the tile LEFT
	int hpTotal = 0;
	SDL_Renderer* renderer;
	bool active = true;
public:
	Tile(SDL_Renderer* renderer, int posX, int posY, int hp);
	void tileHit();
	void fullHp();
	int getHpLeft();
	int getHpTotal();
	bool isActive();
	void setActive(bool active);
};