#include "Physics.h"
#include <iostream>
#include "Globals.h"

Physics::Physics() {
	// Add 4 gameobjects for walls to the collider
	SDL_Rect* wallLeftRect = new SDL_Rect({ -50, 0, 50, Globals::SCREEN_HEIGHT });
	SDL_Rect* wallUpRect = new SDL_Rect({ 0, -50, Globals::SCREEN_WIDTH, 50 });
	SDL_Rect* wallRightRect = new SDL_Rect({ Globals::SCREEN_WIDTH, 0, 50, Globals::SCREEN_HEIGHT });
	SDL_Rect* wallDownRect = new SDL_Rect({ 0, Globals::SCREEN_HEIGHT, Globals::SCREEN_WIDTH, 50 });
	wallLeft = new GameObject("WallLeft", wallLeftRect, NULL);
	wallUp = new GameObject("WallRight", wallRightRect, NULL);
	wallRight = new GameObject("WallUp", wallUpRect, NULL);
	wallDown = new GameObject("WallDown", wallDownRect, NULL);

	addCollider(wallLeft);
	addCollider(wallUp);
	addCollider(wallRight);
	addCollider(wallDown);
}

Physics::~Physics() {
	delete wallLeft;
	delete wallUp;
	delete wallDown;
	delete wallRight;
}

// Checks if gameObject is colliding with any of the other colliders
// Returns the object it collided with, or NULL if none
GameObject* Physics::checkCollision(GameObject * gameObject) {
	auto object1 = gameObject->getPosRect();

	for (auto collider : colliders) {
		if (collider == gameObject) continue;
		auto object2 = collider->getPosRect();
		if (object1->x < object2->x + object2->w &&
			object1->x + object1->w > object2->x &&
			object1->y < object2->y + object2->h &&
			object1->h + object1->y > object2->y) {

			return collider;
		}
	}
	return NULL;
}
void Physics::addCollider(GameObject * gameObject) {
	colliders.push_back(gameObject);
}

bool Physics::removeCollider(GameObject * gameObject) {
	for (int i = 0; i < (int)colliders.size(); i++) {
		if (colliders[i] == gameObject) {
			// Swaps the element with the matching name with the last one in the vector and then pops the vector
			iter_swap(colliders.begin() + i, colliders.begin() + colliders.size() - 1);
			colliders.pop_back();
			return true;
		}
	}
	std::cout << "Could not remove element from colliders" << std::endl;
	return false;
}


