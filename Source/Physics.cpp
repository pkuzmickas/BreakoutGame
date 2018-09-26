#include "Physics.h"
#include <iostream>
#include "Globals.h"

// Checks if gameObject is colliding with any of the other colliders
// Returns the object it collided with, or NULL if none
GameObject* Physics::checkCollision(GameObject * gameObject) {
	auto object1 = gameObject->getPosRect();

	// Add 4 gameobjects for walls to the collider
	// Remove them after this function


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
