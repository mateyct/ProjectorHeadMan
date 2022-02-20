#include <iostream>
#include <SDL.h>
#include "PointVectorTools.h";

float getVectorMagnitude(SDL_Point point) {
	return sqrt(pow(point.x, 2) + pow(point.y, 2));
}