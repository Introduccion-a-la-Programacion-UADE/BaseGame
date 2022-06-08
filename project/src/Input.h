#pragma once
#include <iostream>
#include <SDL.h>

using namespace std;

typedef struct InputState {
    bool up;
    bool down;
    bool left;
    bool right;
    bool fire;
};

void Input_Initialize();

void Input_ProcessInput(InputState& inputState);