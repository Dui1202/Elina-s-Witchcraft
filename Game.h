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
#include "Animation.h"
#include "InputManager.h"

class Game {
public:
	Game();
	void start();
	void update();
	void graphic();
	void logic();
	void input(SDL_Event &e, Vector2f& p_movement);
	void clean();
	//Destroy out of bound Projectiles
	void destroyProjectiles();
private:
	RenderWindow window;
	ResourceManager resourceManager;
	InputManager inputManager;
	std::vector<GameObject*> gameObjectPrefabs;
	std::vector<Projectile*> projectilePrefabs;
	std::vector<Projectile> projectiles;
	std::vector<Animation*> animationProjectiles;
	std::vector<Animation*> animationGrass;
	std::vector<GameObject> gameObjectGrass;
	std::vector<Animation*> animations;
	Player* player;
	Uint32 currentTime;
	float playerSpeed = 0;
};
