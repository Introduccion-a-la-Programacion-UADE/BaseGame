#ifndef ROCK_H
#define ROCK_H

#include <SDL_image.h>
#include <iostream>

using namespace std;

class Rock
{
private:
    float x;
    float y;
    float speed;
    SDL_Rect dest;
    SDL_Texture* texture;

public:
    Rock(SDL_Renderer* renderer);

    int getX();
    int getY();

    void SetPosition(float newX, float newY);

    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);
};

#endif