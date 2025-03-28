#pragma once
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "Animation.h"


class KeyState {
public:
	KeyState();
	bool isStart = false;
	bool isHold = false;
	bool isRelease = false;
};

class MouseState {
public:
	MouseState();
	bool isStart = false;
	bool isHold = false;
	bool isRelease = false;
	Uint32 releaseTime = 0;
};

class InputManager {
public:
	InputManager();
	void update();
	void handleInput(const SDL_Event& p_e);
	bool isKeyStart(SDL_Keycode p_key);
	bool isKeyHeld(SDL_Keycode p_key);
	bool isKeyRelease(SDL_Keycode p_key);
	bool isMouseStart(Uint8 p_mouseEvent);
	bool isMouseHeld(Uint8 p_mouseEvent);
	bool isMouseRelease(Uint8 p_mouseEvent);
	std::unordered_map<SDL_Keycode, KeyState> keyStates;
	std::unordered_map<Uint8, MouseState> mouseStates;
private:

};
