#include "PTexture.h"

PTexture::PTexture() {
	texture = NULL;
	width = 0;
	height = 0;
}

PTexture::~PTexture() {
	// Deallocate
	free();
}

bool PTexture::loadImage(std::string path, SDL_Renderer* renderer) {
	// get ride of old stuff
	free();

	// local variable for texture
	SDL_Texture* newTexture = NULL;

	// load image at path
	SDL_Surface* loadSurf = IMG_Load(path.c_str());
	// check if success
	if (loadSurf == NULL) {
		printf("Image %s couldn't load. Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		//////////////// put extra stuff here later maybe ///////////////

		// create a new texture
		newTexture = SDL_CreateTextureFromSurface(renderer, loadSurf);
		if (newTexture == NULL) {
			printf("Image could not be converted to texture. Error: %s\n", SDL_GetError());
		}
		else {
			// set dimensions
			width = loadSurf->w;
			height = loadSurf->h;
		}

		// rid ourselves of the obselete and forgotten surface
		SDL_FreeSurface(loadSurf);
	}
	texture = newTexture;
	return texture != NULL;
}

void PTexture::free() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void PTexture::render(int x, int y, int animIndex, SDL_Renderer* renderer) {
	// set part to render
	SDL_Rect srcArea = { 0, 0, width, height };
	SDL_Rect desArea = { x, y, width * 5, height * 5};
	desArea.x -= desArea.w / 2;
	desArea.y -= desArea.h / 2;

	// render it
	SDL_RenderCopy(renderer, texture, &srcArea, &desArea);
}

int PTexture::getWidth() {
	return width;
}

int PTexture::getHeight() {
	return height;
}