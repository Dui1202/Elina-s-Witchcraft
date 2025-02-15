#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Entity.h"
#include "GameObject.h"
#include "RenderWindow.hpp"
#include "ResourceManager.h"
#include "Player.h"

class Game {
public:
	Game();
	void start();
	void update();
	void clean();
private:
	RenderWindow window;
	ResourceManager resourceManager;
	std::vector<GameObject> gameObjects;
	Player player;
	float playerSpeed = 0;
};
