#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Utils.h"
#include "Input.h"
#include "SpaceShip.h"
#include <string>

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

TTF_Font* gamingFont;
SDL_Surface* textSurface;
SDL_Texture* textTexture;

SDL_Surface* clockTextSurface;
SDL_Texture* clockTextTexture;



// Inicialización motor
void StartGame() {
	SDL_Init(SDL_INIT_EVERYTHING);

	// Window 
	SDL_Window* window = SDL_CreateWindow("Galaxy", 100, 100, 800, 600, SDL_WINDOW_SHOWN);

	// Renderer
	renderer = SDL_CreateRenderer(window, -1, 0);

	// Color de fondo
	SDL_SetRenderDrawColor(renderer, 60, 60, 100, 255);

	// Fonts 
	TTF_Init();

	// Input
	Input_Initialize();

	
}

void InitalizeUI() {
	SDL_Color color = { 255, 100, 0 };

	string myName = "Hello World";

	textSurface = TTF_RenderText_Blended(gamingFont, myName.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	clockTextSurface = TTF_RenderText_Blended(gamingFont, "30", color);
	clockTextTexture = SDL_CreateTextureFromSurface(renderer, clockTextSurface);
}

// Carga de Recursos 

void LoadAssets() {

	// Font 
	gamingFont = TTF_OpenFont("assets/8-bit-pusab.ttf", 20);

	// Carga
	string filename = "assets/ufo.png";
	ufoTexture = IMG_LoadTexture(renderer, filename.c_str());

	// Ship usando TDA
	SpaceShip_Initialize(playerShip, renderer);
	playerShip.x = 100;
	playerShip.y = 500;
}




void UpdateInput() {

	Input_ProcessInput(inputState);
}


void UpdateUI() {

	SDL_Color color = { 255, 255, 255 };
	int gameSeconds = floor(gameTime);

	string clockText = "00:" + to_string(gameSeconds);

	clockTextSurface = TTF_RenderText_Blended(gamingFont, clockText.c_str(), color); // Creamos el Surface con el texto actualizado
	clockTextTexture = SDL_CreateTextureFromSurface(renderer, clockTextSurface); // Creamos la Textura a partir del Surface

	SDL_FreeSurface(clockTextSurface); // La surface ya fue utilizada, asi que liberamos memoria para evitar un memory Leak.
}


void UpdateGame() {

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

void Render() {

	// Dibujado UFO
	SDL_Rect dest;
	dest.x = 300;
	dest.y = ufoPosY;
	SDL_QueryTexture(ufoTexture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer, ufoTexture, NULL, &dest);

	// Dibujado ship
	SpaceShip_Update(playerShip, renderer);

	// Dibujado UI
	SDL_Rect uiTitleRect;
	uiTitleRect.x = 500;
	uiTitleRect.y = 40;
	uiTitleRect.w = 100;
	uiTitleRect.h = 30;
	SDL_RenderCopy(renderer, textTexture, NULL, &uiTitleRect);

	// Dibujado Reloj
	SDL_Rect uiClockRect;
	uiClockRect.x = 300;
	uiClockRect.y = 400;
	uiClockRect.w = 100;
	uiClockRect.h = 30;
	SDL_RenderCopy(renderer, clockTextTexture, NULL, &uiClockRect); // Dibujamos en pantalla la textura con el reloj actualizado
	SDL_DestroyTexture(clockTextTexture); // La Textura ya fue utilizada, asi que liberamos memoria para evitar un memory Leak.

	SDL_RenderPresent(renderer);
}

int main(int argc, char* args[])
{
	StartGame();

	LoadAssets();

	InitalizeUI();

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

		// Update Input
		UpdateInput();

		// Update lógica y UI
		UpdateGame();
		UpdateUI();

		// Render
		Render();

		SDL_Delay(1000.0 / FPS);
	}

	return 0;
}
