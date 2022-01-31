#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>

/// <summary>
/// Wrapper class for a texture that makes like just a bit easier. Renders at the middle of the image
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

	/// <summary>
	/// Sets the texture
	/// </summary>
	/// <param name="path">The path to load from</param>
	/// <returns>Was it successful</returns>
	bool loadImage(std::string path, SDL_Renderer* renderer);

	// deallocates stuff
	void free();

private:
	// Texture that the object holds
	SDL_Texture* texture;

	// width of texture
	int width;

	// height of the texture
	int height;
};