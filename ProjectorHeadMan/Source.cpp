#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "./PTexture.h"

#undef main

// Constants for window size
const int S_WIDTH = 640;
const int S_HEIGHT = 480;

// The main renderer
SDL_Renderer* renderer = NULL;

// The main window
SDL_Window* window = NULL;

// The main character texture
PTexture character;

// Initialize all the stuff
bool init();

// Load media into variables
bool loadMedia();

// close everything to not do bad memory stuff
void close();

bool init() {
	// success flag
	bool success = true;

	// Start SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could not init SDL. Error: %s", SDL_GetError());
		success = false;
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		// make the window
		window = SDL_CreateWindow("Projector Head Man", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, S_WIDTH, S_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			// set up renderer
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL) {
				printf("Renderer could not be created! Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				// renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);

				// init png SDL_image
				int imgFlag = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlag) & imgFlag)) {
					printf("SDL_image could not initialize! Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia() {
	// success flag
	bool success = true;

	// load in texture
	success = character.loadImage("assets/guy.png", renderer);

	return success;
}

void close() {
	// deallocate character
	character.free();
	// destroy window and renderer
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = nullptr;

	// close subsystems
	IMG_Quit();
	SDL_Quit();
}

int main() {
	// check if initializaiton works
	if (!init()) {
		printf("Could not be intiaiized.");
	}
	else {
		// check if loading media worked
		if (!loadMedia()) {
			printf("Could not load media.");
		}
		else {
			bool quit = false;
			// main loop
			while (quit != true) {
				// make event for getting info
				SDL_Event e;
				while (SDL_PollEvent(&e)) {
					// if the event is to quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}
				// rerender things
				SDL_RenderClear(renderer);

				character.render(S_WIDTH / 2, S_HEIGHT / 2, 0, renderer);

				SDL_RenderPresent(renderer);
			}

		}
	}
	
	// close the program
	close();
	return 0;
}
