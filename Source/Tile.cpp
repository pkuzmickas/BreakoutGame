#include "Tile.h"
#include "Globals.h"
#include <iostream>
Tile::Tile(SDL_Renderer * renderer, int posX, int posY, int hp) {
	if (hp < 1) hp = 1;
	else if (hp > 2) hp = 2;
	name = "Tile";
	posRect = new SDL_Rect();
	posRect->x = posX;
	posRect->y = posY;
	posRect->h = Globals::TILE_HEIGHT;
	posRect->w = Globals::TILE_WIDTH;
	if (hp == 1) imgPath = "Assets/yellow.png";
	else if (hp == 2) imgPath = "Assets/orange.png";
	init(name, posRect, new Sprite(NULL, IMG_LoadTexture(renderer, imgPath.c_str())));

}
