#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Utils.h"
#include "Input.h"
#include "SpaceShip.h"

using namespace std;

// Variables Globales

const float FPS = 60.0;
const float UFO_SPEED = 300;

float gameTime = 30;

float deltaTimeInSeconds;
SDL_Renderer* renderer;

SDL_Texture* ufoTexture;
int ufoPosY = 0;
bool ufoGoesDown = true;

InputState inputState;

SpaceShip playerShip;



// Inicialización motor
void StartGame() {
	SDL_Init(SDL_INIT_EVERYTHING);

	// Window 
	SDL_Window* window = SDL_CreateWindow("Galaxy", 100, 100, 800, 600, SDL_WINDOW_SHOWN);

	// Renderer
	renderer = SDL_CreateRenderer(window, -1, 0);

	// Color de fondo
	SDL_SetRenderDrawColor(renderer, 60, 60, 100, 255);

	Input_Initialize();

	
}

// Carga de Recursos 

void LoadAssets() {

	// Carga
	string filename = "assets/ufo.png";
	ufoTexture = IMG_LoadTexture(renderer, filename.c_str());

	// Ship usando TDA
	SpaceShip_Initialize(playerShip, renderer);
	playerShip.x = 100;
	playerShip.y = 500;
}

void updateInput() {

	Input_ProcessInput(inputState);
}

void updateGame() {

	// Actualizacion tiempo
	gameTime -= deltaTimeInSeconds;


	// Actualizacion Nave
	float currentSpeed = UFO_SPEED * deltaTimeInSeconds;

	if (ufoGoesDown) {
		ufoPosY = ufoPosY + currentSpeed;
	}
	else {
		ufoPosY = ufoPosY - currentSpeed;
	}

	// Pantalla 600 de alto

	if (ufoPosY >= 600) {

		ufoPosY = 600;
		ufoGoesDown = false;
	}
	else if(ufoPosY <= 0) {
		ufoPosY = 0;
		ufoGoesDown = true;
	}

	// Player Ship

	if (inputState.left) {
		playerShip.x -= 200 * deltaTimeInSeconds;
	} 
	else if (inputState.right) {
		playerShip.x += 200 * deltaTimeInSeconds;
	}

	if (inputState.up) {
		playerShip.y -= 200 * deltaTimeInSeconds;
	} 
	else if (inputState.down) {
		playerShip.y += 200 * deltaTimeInSeconds;
	}
	
}

void render() {

	// Dibujado
	SDL_Rect dest;
	dest.x = 300;
	dest.y = ufoPosY;
	SDL_QueryTexture(ufoTexture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer, ufoTexture, NULL, &dest);

	SpaceShip_Update(playerShip, renderer);


	SDL_RenderPresent(renderer);
}

int main(int argc, char* args[])
{
	StartGame();

	LoadAssets();


	bool isGameRunning = true;

	// Mostrar una nave y que se mueva de arriba hacia abajo

	float previousTime = 0;
	float currentTime = 0;

	while (isGameRunning) {
		// Actualizo Timer
		previousTime = currentTime;
		currentTime = SDL_GetTicks();

		deltaTimeInSeconds = (currentTime - previousTime) / 1000.0;

		// Limpio pantalla
		SDL_RenderClear(renderer);

		updateInput();
		updateGame();
		render();

		SDL_Delay(1000.0 / FPS);
	}

	return 0;
}
