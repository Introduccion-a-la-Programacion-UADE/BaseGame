#include "Input.h"



void onKeyDown(int keyCode, InputState& inputState) {
    switch (keyCode) {
    case SDLK_UP:
        inputState.up = true;
        break;
    case SDLK_DOWN:
        inputState.down = true;
        break;
    case SDLK_LEFT:
        inputState.left = true;
        break;
    case SDLK_RIGHT:
        inputState.right = true;
        break;
    default:
        break;
    }
}


void onKeyUp(int keyCode, InputState& inputState) {
    switch (keyCode) {
    case SDLK_UP:
        inputState.up = false;
        break;
    case SDLK_DOWN:
        inputState.down = false;
        break;
    case SDLK_LEFT:
        inputState.left = false;
        break;
    case SDLK_RIGHT:
        inputState.right = false;
        break;
    default:
        break;
    }
}


void onJoystickAxisMotion(int joystick, int axis, int value, InputState& inputState) {
    if (axis == 1) {

        if (abs(value) < 15000) {
            inputState.up = inputState.down = 0;
        }
        else {
            inputState.up = value < 0;
            inputState.down = !inputState.up;
        }

    }
    else if (axis == 0) {

        if (abs(value) < 15000) {
            inputState.left = inputState.right = 0;
        }
        else {
            inputState.right = value > 0;
            inputState.left = !inputState.right;
        }
    }
}

void onJoystickButtonUp(int joystick, int button, InputState& inputState) {
    if (button == 0) {
        inputState.fire = false;
    }

}

void onJoystickButtonDown(int joystick, int button, InputState& inputState) {
    if (button == 0) {
        inputState.fire = true;
    }
}


void Input_Initialize() {
    SDL_JoystickEventState(SDL_ENABLE);
}



void Input_ProcessInput(InputState &inputState) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            exit(0);
            break;

        case SDL_KEYDOWN:
            onKeyDown(event.key.keysym.sym, inputState);
            break;
        case SDL_KEYUP:
            onKeyUp(event.key.keysym.sym, inputState);
            break;
        case SDL_JOYAXISMOTION:
            onJoystickAxisMotion(event.jaxis.which, event.jaxis.axis, event.jaxis.value, inputState);
            break;
        case SDL_JOYBUTTONDOWN:
            onJoystickButtonDown(event.jbutton.which, event.jbutton.button, inputState);
            break;
        case SDL_JOYBUTTONUP:
            onJoystickButtonUp(event.jbutton.which, event.jbutton.button, inputState);
            break;

        default:
            break;
        }
    }
}



