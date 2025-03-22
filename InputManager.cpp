#include<SDL.h>
#include"InputManager.h"
#include "UI.h"

KeyState:: KeyState() {

}

MouseState::MouseState() {

}

InputManager::InputManager() 
{}

void InputManager::handleInput(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && !e.key.repeat) {
        keyStates[e.key.keysym.sym].isStart = true;
        keyStates[e.key.keysym.sym].isHold = false;
        keyStates[e.key.keysym.sym].isRelease = false;
    }
    else if (e.type == SDL_KEYUP) {
        keyStates[e.key.keysym.sym].isStart = false;
        keyStates[e.key.keysym.sym].isHold = false;
        keyStates[e.key.keysym.sym].isRelease = true;
    }

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        mouseStates[e.button.button].isStart = true;
        mouseStates[e.button.button].isHold = false;
        mouseStates[e.button.button].isRelease = false;
    }
    else if ((e.type == SDL_MOUSEBUTTONUP)) {
        mouseStates[e.button.button].isStart = false;
        mouseStates[e.button.button].isHold = false;
        mouseStates[e.button.button].isRelease = true;

    }
}


bool InputManager::isKeyHeld(SDL_Keycode p_key) {
    return keyStates[p_key].isHold;
}

bool InputManager::isKeyStart(SDL_Keycode p_key) {
    return keyStates[p_key].isStart;
}

bool InputManager::isKeyRelease(SDL_Keycode p_key) {
    return keyStates[p_key].isRelease;
}

bool InputManager::isMouseStart(Uint8 p_mouseEvent) {
    return mouseStates[p_mouseEvent].isStart;
}

bool InputManager::isMouseHeld(Uint8 p_mouseEvent) {
    return mouseStates[p_mouseEvent].isHold;
}

bool InputManager::isMouseRelease(Uint8 p_mouseEvent) {
    return mouseStates[p_mouseEvent].isRelease;
}

void InputManager::update() {
    for (auto& pair : keyStates) {
        if (pair.second.isStart) {
            pair.second.isHold = true;
            pair.second.isStart = false;
        }
        else if (pair.second.isRelease) {
            pair.second.isRelease = false;
            pair.second.isHold = false;
        }
    }

    for (auto& pair : mouseStates) {
        if (pair.second.isStart) {
            pair.second.isHold = true;
            pair.second.isStart = false;
        }

        if (pair.second.isRelease) {
            pair.second.isRelease = false;
            pair.second.isHold = false;
        }
    }
}
