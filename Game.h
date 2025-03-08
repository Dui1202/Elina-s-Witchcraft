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
#include "Enemy.h"
#include "SpawnManager.h"
#include "UI.h"

class Game {
public:
	Game();
	void start();
	void update();
	void pause();
	void debug();
	void graphic();
	void logic();
	void input(SDL_Event &e, Vector2f& p_movement);
	void clean();
	//Destroy out of bound Projectiles
	void destroyOutOfBound();
	void destroyEnemy(Enemy* p_enemy, std::vector<Enemy*>::iterator& p_eneIt);
	void destroyProjectile(Projectile* p_projectile, std::vector<Projectile*>::iterator& p_prjIt);

	//Button functions
	void settingsButtonFunction();
private:
	RenderWindow window;
	ResourceManager resourceManager;
	InputManager inputManager;
	SpawnManager spawnManager;

	//Prefabs
	std::vector<GameObject*> gameObjectPrefabs;
	std::vector<Projectile*> projectilePrefabs;
	std::vector<Animation*> animationPrefabs;
	std::vector<Enemy*> enemyPrefabs;

	//In-game
	std::vector<Projectile*> projectiles;
	std::vector<GameObject> gameObjectGrass;
	std::vector<Enemy*> enemies;
	std::vector<Text*> texts;
	std::vector<Button*> buttons;
	std::vector<Button*> buttonsInSettingModal;
	std::vector<Button*> buttonsInMenu;
	std::vector<Modal*> modals;

	std::vector<Animation*> animationProjectiles;
	std::vector<Animation*> animationGrass;
	std::vector<Animation*> animationEnemies;
	std::vector<Animation*> animationUIs;

	Player* player;
	Uint32 currentTime;
	float playerSpeed = 0;

	Uint32 startPause = 0;
	Uint32 lastPause = 0;
	Uint32 timePause = 0;

	bool isGamePause = false;
	bool isGameOver = true;
};
