#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "./PTexture.h"
#include <cmath>
#include "PointVectorTools/PointVectorTools.h"

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

// character acceleration
SDL_Point acceleration = { 0, 0 };

// character velocity
SDL_Point velocity = { 0, 0 };

// character position
SDL_Point pos = { S_WIDTH / 2, S_HEIGHT / 2 };

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
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);

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
			int frame = 0;
			// main loop
			while (quit != true) {
				// make event for getting info
				SDL_Event e;
				while (SDL_PollEvent(&e)) {
					// if the event is to quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					// key events
					if (e.type == SDL_KEYDOWN) {
						SDL_Keycode key = e.key.keysym.sym;
						if (key == SDLK_LEFT && !(velocity.x < 0)) {
							velocity.x -= 5;
						}
						if (key == SDLK_RIGHT && !(velocity.x > 0)) {
							velocity.x += 5;
						}
						if (key == SDLK_DOWN && !(velocity.y > 0)) {
							velocity.y += 5;
						}
						if (key == SDLK_UP && !(velocity.y < 0)) {
							velocity.y -= 5;
						}
					}
					// key up to stop
					if (e.type == SDL_KEYUP) {
						SDL_Keycode key = e.key.keysym.sym;
						if (key == SDLK_LEFT && velocity.x < 0) {
							velocity.x = 0;
						}
						if (key == SDLK_RIGHT && velocity.x > 0) {
							velocity.x = 0;
						}
						if (key == SDLK_DOWN && velocity.y > 0) {
							velocity.y = 0;
						}
						if (key == SDLK_UP && velocity.y < 0) {
							velocity.y = 0;
						}
					}
				}
				
				// position calculations
				pos.x += velocity.x;
				pos.y += velocity.y;

				// rerender things
				SDL_RenderClear(renderer);

				frame++;
				if (frame >= 64) {
					frame = 0;
				}
				
				printf("%d", frame / 16);
				character.render(pos.x, pos.y, frame / 16, renderer);


				SDL_RenderPresent(renderer);
			}

		}
	}
	
	// close the program
	close();
	return 0;
}
