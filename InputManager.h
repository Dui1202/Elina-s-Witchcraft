#pragma once
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "Player.h"



class InputManager {
public:
	std::unordered_map<SDL_Keycode, bool> keyStates;
	InputManager();
	void handleInput(const SDL_Event& p_e);
	bool isKeyPressed(SDL_Keycode p_key);
	bool isKeyHeld(SDL_Keycode p_key);
	bool isKeyUp(SDL_Keycode p_key);
private:

};
