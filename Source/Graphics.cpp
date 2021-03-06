#include "Graphics.h"

Graphics::Graphics(SDL_Renderer * renderer) {
	this->renderer = renderer;

}

void Graphics::addToDraw(GameObject* gameObject, bool isLogo) {
	if (isLogo) { // To make sure we always draw it on top
		logo = gameObject; 
		return;
	}
	if (gameObject) {
		drawQueue.push_back(gameObject);
	}
	else {
		cout << "Trying to add an empty game object to the draw queue!" << endl;
	}
}

bool Graphics::removeFromDraw(GameObject * gameObject) {
	if (gameObject == logo) {
		logo = NULL;
		return true; 
	}
	for (int i = 0; i < (int)drawQueue.size(); i++) {
		if (drawQueue[i] == gameObject) {
			// Swaps the element with the matching name with the last one in the vector and then pops the vector
			iter_swap(drawQueue.begin() + i, drawQueue.begin() + drawQueue.size() - 1);
			drawQueue.pop_back();
			return true;
		}
	}
	cout << "Could not remove element from draw" << endl;
	return false;
}

void Graphics::draw() {
	SDL_RenderClear(renderer);

	for (auto gameObject : drawQueue) {
		SDL_RenderCopy(renderer, gameObject->getSprite()->getTexture(), gameObject->getSprite()->getSrcRect(), gameObject->getPosRect());
	}
	if (logo) {
		SDL_RenderCopy(renderer, logo->getSprite()->getTexture(), logo->getSprite()->getSrcRect(), logo->getPosRect());
	}
	SDL_RenderPresent(renderer);
}
