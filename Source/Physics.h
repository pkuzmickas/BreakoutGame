#pragma once
#include "GameObject.h"
#include <vector>
class Physics {
private:
	std::vector<GameObject*> colliders;
public:
	// Checks if game object collides with anything
	GameObject* checkCollision(GameObject* gameObject);
	void addCollider(GameObject* gameObject);
	bool removeCollider(GameObject* gameObject);
};