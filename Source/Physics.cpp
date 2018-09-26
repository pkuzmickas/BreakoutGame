#include "Physics.h"
#include <iostream>
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
