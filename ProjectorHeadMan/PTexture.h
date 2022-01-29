#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>

/// <summary>
/// 
/// </summary>
class PTexture {
public:

	// Loads the the file from the path
	PTexture();

	// Destructors the object
	~PTexture();

	/// <summary>
	/// Gets the texture width
	/// </summary>
	/// <returns>texture width</returns>
	int getWidth();

	/// <summary>
	/// Gets the texture height
	/// </summary>
	/// <returns>texture height</returns>
	int getHeight();

	/// <summary>
	/// Renders the texture on the screen
	/// </summary>
	/// <param name="x">X location</param>
	/// <param name="y">Y location</param>
	/// <param name="animIndex">Animation part to show</param>
	/// <param name="renderer">Renderer to show</param>
	void render(int x, int y, int animIndex, SDL_Renderer* renderer);

private:
	// Texture that the object holds
	SDL_Texture* texture;

	// width of texture
	int width;

	// height of the texture
	int height;
};

