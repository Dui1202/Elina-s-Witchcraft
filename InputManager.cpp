#include<SDL.h>
#include"InputManager.h"
#include"Player.h"

InputManager::InputManager() 
{}

void InputManager::handleInput(const SDL_Event &e) {
    if (e.type == SDL_KEYDOWN) {
        keyStates[e.key.keysym.sym] = true;  // Mark key as pressed
    }
    else if (e.type == SDL_KEYUP) {
        keyStates[e.key.keysym.sym] = false; // Mark key as released
    }
}

