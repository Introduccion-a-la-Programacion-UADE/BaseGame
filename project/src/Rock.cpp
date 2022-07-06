#include "Rock.h"

Rock::Rock(SDL_Renderer* renderer)
{
	string filename = "assets/asteroid.png";
	texture = IMG_LoadTexture(renderer, filename.c_str());

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	speed = 200;
}

int Rock::getX()
{
	return x;
}

int Rock::getY()
{
	return y;
}

void Rock::Update(float deltaTime) 
{
	x += deltaTime * speed;
}

void Rock::SetPosition(float newX, float newY)
{
	x = newX;
	y = newY;
}

void Rock::Draw(SDL_Renderer* renderer)
{
	dest.x = x;
	dest.y = y;

	SDL_RenderCopy(renderer, texture, NULL, &dest);
}
