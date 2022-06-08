#pragma once

#include <SDL_image.h>
#include <iostream>

using namespace std;

typedef struct SpaceShip {
	int x;
	int y;
	SDL_Rect dest;
	SDL_Texture* texture;
};


void SpaceShip_Initialize(SpaceShip& spaceShip, SDL_Renderer* renderer) {

	string filename = "assets/ufo.png";
	spaceShip.texture = IMG_LoadTexture(renderer, filename.c_str());

	SDL_QueryTexture(spaceShip.texture, NULL, NULL, &spaceShip.dest.w, &spaceShip.dest.h);
}

void SpaceShip_Update(SpaceShip& spaceShip, SDL_Renderer* renderer) {

	spaceShip.dest.x = spaceShip.x;
	spaceShip.dest.y = spaceShip.y;

	SDL_RenderCopy(renderer, spaceShip.texture, NULL, &spaceShip.dest);

}