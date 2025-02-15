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
#include "ProjectilesManager.h"

class Game {
public:
	Game();
	void start();
	void update();
	void clean();
	//Destroy out of bound Projectiles
	void destroyProjectiles();
private:
	RenderWindow window;
	ResourceManager resourceManager;
	std::vector<GameObject*> gameObjectPrefabs;
	std::vector<Projectile*> projectilePrefabs;
	std::vector<Projectile> projectiles;
	Player* player;
	float playerSpeed = 0;
};
