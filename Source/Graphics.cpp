#include "Graphics.h"

Graphics::Graphics(SDL_Renderer * renderer) {
	this->renderer = renderer;

}

void Graphics::draw() {
	SDL_RenderClear(renderer);

	for (auto gameObject : drawQueue) {
		SDL_RenderCopy(renderer, gameObject->getSprite()->getTexture(), gameObject->getSprite()->getSrcRect(), &gameObject->getPosRect());
	}

	SDL_RenderPresent(renderer);
}
