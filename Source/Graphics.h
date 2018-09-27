#pragma once
#include <vector>
#include <iostream>
#include "GameObject.h"
using namespace std;
class Graphics {
private:
	SDL_Renderer* renderer;
	vector<GameObject*> drawQueue;
	GameObject* logo = NULL;
public:
	Graphics(SDL_Renderer* renderer);
	void draw();
	void addToDraw(GameObject* gameObject, bool isLogo = false);
	bool removeFromDraw(GameObject* gameObject);
};