#include "Tile.h"
#include "Globals.h"
#include <iostream>
Tile::Tile(SDL_Renderer * renderer, int posX, int posY, int hp) {
	this->renderer = renderer;
	if (hp < 1) hp = 1;
	else if (hp > 2) hp = 2;
	this->hpLeft = hp;
	this->hpTotal = hp;
	name = "Tile";
	posRect = new SDL_Rect();
	posRect->x = posX;
	posRect->y = posY;
	posRect->h = Globals::TILE_HEIGHT;
	posRect->w = Globals::TILE_WIDTH;
	if (hp == 1) imgPath = YELLOW_TILE_PATH;
	else if (hp == 2) imgPath = ORANGE_TILE_PATH;
	init(name, posRect, new Sprite(NULL, IMG_LoadTexture(renderer, imgPath.c_str())));

}

void Tile::tileHit() {
	hpLeft--;
	if (hpLeft == 1) {
		getSprite()->setTexture(renderer, YELLOW_TILE_PATH);
	}
}

void Tile::fullHp() {
	hpLeft = hpTotal;
	if (hpTotal == 2) {
		getSprite()->setTexture(renderer, ORANGE_TILE_PATH);
	}
	else if (hpTotal == 1) {
		getSprite()->setTexture(renderer, YELLOW_TILE_PATH);
	}
	//change img as well
}

int Tile::getHpTotal() {
	return hpTotal;
}

bool Tile::isActive() {
	return active;
}

void Tile::setActive(bool active) {
	this->active = active;
}

int Tile::getHpLeft() {
	return hpLeft;
}
