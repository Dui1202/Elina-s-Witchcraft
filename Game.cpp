#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.h"
#include "GameObject.h"
#include "Game.h"
#include "Player.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Animation.h"
#include "Enemy.h"
#include "Collision.h"

//Initalize window, resourceManager,
Game::Game()
	:window("Gametest", 1280, 720), resourceManager(window.getRenderer()), player(nullptr){}

//Starting the game (load all game textures, and initalize going-to-be-used GameObject) 
void Game::start() {
	//Load all textures
	std::vector<std::string> allTexturePaths = {
		"./asset/player/witch-idle-sprite-sheet.png",
		"./asset/grass.png",
		"./asset/fireball_sprite.png",
		"./asset/slime-move-sprite.png"
	};
	resourceManager.loadTexture(allTexturePaths);

	//Set textures
	SDL_Texture* playerTexture = resourceManager.getTexture(allTexturePaths[0]);
	SDL_Texture* grassTexture = resourceManager.getTexture(allTexturePaths[1]);
	SDL_Texture* fireballTexture = resourceManager.getTexture(allTexturePaths[2]);
	SDL_Texture* slimeTexture = resourceManager.getTexture(allTexturePaths[3]);

	//Set some frames
	SDL_Rect defaultFrame = { 0, 0 , 64, 64 };
	SDL_Rect grassFrame = { 0, 0, 240, 120 };

	//Set some in-game varibles
	playerSpeed = 5;
	float fireBallSpeed = 10;
	float fireBallStr = 5;
	float slimeSpeed = 3;
	float slimeHp = 10;

	Collider slimeCollider(SDL_Rect({ 1,1, 100, 100 }));

	//Set Animation
	Animation* slimeAnimation = new Animation(Vector2f(0, 0), slimeTexture, 1, defaultFrame, 100);
	Animation* grassAnimation = new Animation(Vector2f(0, 0), grassTexture, 1, grassFrame, 100);
	Animation* fireBallAnimation = new Animation(Vector2f(0, 0), fireballTexture, 2, defaultFrame, 100);

	//Set projectiles
	Projectile* fireball = new Projectile(Vector2f(0, 0), Vector2f(1, 0), fireBallSpeed, fireBallStr, fireBallAnimation);

	//Set player
	player = new Player(Vector2f(0, 362), nullptr, *fireball);
	Animation* playerIdleAnimation = new Animation(player->getPos(), playerTexture, 2, defaultFrame, 300);
	player->setAnimation(playerIdleAnimation);
	
	//Set enemies
	Enemy* slime = new Enemy(Vector2f(0, 0), slimeAnimation, Vector2f(-1, 0), slimeSpeed, slimeHp);

	//Push all animations for easier deconstruction
	animationPrefabs.push_back(playerIdleAnimation);
	animationPrefabs.push_back(fireBallAnimation);
	animationPrefabs.push_back(grassAnimation);
	animationPrefabs.push_back(slimeAnimation);

	projectilePrefabs.push_back(fireball);

	enemyPrefabs.push_back(slime);
}

void Game::debug() {

	for (auto& ene : enemies) {
		ene->getCollider().drawCollider(window.getRenderer());
	}
	
	for (auto& prj : projectiles) {
		prj->getCollider().drawCollider(window.getRenderer());
	}
}

void Game::logic() {
	for (auto pjIt = projectiles.begin(); pjIt != projectiles.end();) {
		bool isDestroy = false;
		for (auto eneIt = enemies.begin(); eneIt != enemies.end(); ++eneIt) {
			if ((*pjIt)->getCollider().checkCollide((*eneIt)->getCollider())) {
				std::cout << "Collide with enemy!" << std::endl;
				(*eneIt)->setHp((*eneIt)->getHp() - (*pjIt)->getStr());
				std::cout << (*pjIt)->getStr() << std::endl;
				destroyProjectile(*pjIt, pjIt);
				std::cout << "1!" << std::endl;
				std::cout << ((*eneIt)->getHp()) << std::endl;
				std::cout << "2!" << std::endl;
				if ((*eneIt)->getHp() <= 0) {
					destroyEnemy(*eneIt, eneIt);
				}
				std::cout << "3!" << std::endl;
				isDestroy = true;
				break;
			}
		}
		if (!isDestroy)
		{
			++pjIt;
		}
	}
}

void Game::graphic() {
	//Set grass field in the game
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			Animation* newGrassAnimation = new Animation(*animationPrefabs[2]);
			animationGrass.push_back(newGrassAnimation);
			GameObject newGrassGO(Vector2f(0,0), newGrassAnimation);

			if (i % 2 == 0) {
				newGrassGO.setPos(Vector2f(0 + 240 * j, 120 + 120 * i));
			}
			else {
				newGrassGO.setPos(Vector2f(-120 + 240 * j, 120 + 120 * i));
			}
			newGrassGO.getAnimation()->setPos(newGrassGO.getPos());
			std::cout << "Add Grass GO!" << std::endl;
			gameObjectGrass.push_back(newGrassGO);
		}
	}
}

void Game::input(SDL_Event &e, Vector2f &p_movement) {
	inputManager.handleInput(e);

	p_movement = Vector2f(0, 0);

	if (inputManager.keyStates[SDLK_w]) p_movement.y -= 1;
	if (inputManager.keyStates[SDLK_s]) p_movement.y += 1;
	if (currentTime - player->getLastShotFb() >= player->getCoolDownFb()) {
		if (inputManager.keyStates[SDLK_SPACE]) {
			player->shootFireball(projectiles, animationPrefabs[1], animationProjectiles);
			player->setLastShotFb(currentTime);
		};
	}

	p_movement.normalize();
	//p_movement.print();
}

//Main game loop
void Game::update() {
	graphic();
	//Set flag for the game loop
	bool isGameRunning = true;

	SDL_Event e;
	//For program's frame rate
	Uint32 lastTime = SDL_GetTicks();
	float accumulator = 0.0f;
	const float timeStep = 16.67f;

	//References
	Projectile* fireball = projectilePrefabs[0];
	Enemy* slime = enemyPrefabs[0];
	Animation* playerIdleAnimation = animationPrefabs[0];
	Animation* fireBallAnimation = animationPrefabs[1];
	

	Vector2f movement(0, 0);
	//The main game loop
	while (isGameRunning) {
		currentTime = SDL_GetTicks();
		float frameTime = currentTime - lastTime;
		lastTime = currentTime;
		accumulator += frameTime;

		while (accumulator >= timeStep) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					isGameRunning = false;
				}
				input(e, movement);
			}
			accumulator -= timeStep;
		}
		if (currentTime - spawnManager.getLastTime() >= spawnManager.getCooldown()) {
			spawnManager.spawnEnemy(enemies, animationEnemies, slime);
			spawnManager.setLastTime(currentTime);
		}
		
		logic();
		//Player movement
		player->move(movement * playerSpeed);
		playerIdleAnimation->setPos(player->getPos());

		//Fireball movement
		for (auto& fb : projectiles) {
			fb->update(player->getPos(), currentTime);
		}

		//Slime movement
		for (auto& ene : enemies) {
			ene->update(currentTime);
		}



		//Destroy out of bound projectiles
		destroyOutOfBound();

		//Clear the screen
		window.clear();

		SDL_SetRenderDrawColor(window.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(window.getRenderer());
		//Draw the screen
		
			//Render Grass
		for (auto& grass : gameObjectGrass) {
			window.renderAnimation(grass.getAnimation());
		}
		
			//Render Player
		window.renderAnimation64(playerIdleAnimation);
		playerIdleAnimation->update(currentTime);

			//Render FireBall
		for (auto& fb : projectiles) {
			window.renderAnimation64(fb->getAnimation());
		}
			
			//Render Enemies
		for (auto& sl : enemies) {
			window.renderAnimation64(sl->getAnimation());
		}

		debug();
		

		//Show screen
		window.display();

		//std::cout << player->getPos().y << std::endl;

		//Show the fps on console
		float fps = 1000.0f / frameTime;
		//std::cout << fps << std::endl;

		//Frame Delay ( make sure the game is always on 60 fps )
		int frameDelay = 16 - (SDL_GetTicks() - currentTime);
		if (frameDelay > 0) SDL_Delay(frameDelay);
	}
	
}

void Game::clean() {

	//Destroy all textures
	resourceManager.clearTexture();

	//Destroy window and renderer
	window.cleanUp();
	for (GameObject* go : gameObjectPrefabs) {
		delete go;
	}

	for (Animation* anim : animationPrefabs) {
		delete anim;
	}
	
	for (Projectile* pj : projectilePrefabs) {
		delete pj;
	}

	for (Enemy* ene : enemyPrefabs) {
		delete ene;
	}

	for (Animation* anim : animationGrass) {
		delete anim;
	}

	for (Animation* anim : animationEnemies) {
		delete anim;
	}

	for (Animation* anim : animationProjectiles) {
		delete anim;
	}


	gameObjectPrefabs.clear();
	animationPrefabs.clear();
	projectilePrefabs.clear();
	enemyPrefabs.clear();
	animationGrass.clear();
	animationEnemies.clear();
	animationProjectiles.clear();

	
	delete player;
}

void Game::destroyOutOfBound() {
	for (auto i = 0; i < projectiles.size();) {
		if (projectiles[i]->getPos().x >= 1280 || projectiles[i]->getPos().y >= 720) {
			delete projectiles[i]->getAnimation();
			animationProjectiles.erase(animationProjectiles.begin() + i);
			projectiles.erase(projectiles.begin() + i);
			std::cout << "Projectile destroyed!"<<std::endl;
		}
		else {
			i++;
		}
	}

	for (auto i = 0; i < enemies.size();) {
		if (enemies[i]->getPos().x < -100 || enemies[i]->getPos().y <0) {
			delete enemies[i]->getAnimation();
			animationEnemies.erase(animationEnemies.begin() + i);
			enemies.erase(enemies.begin() + i);
			std::cout << "Enemy destroyed!" << std::endl;
		}
		else {
			i++;
		}
	}
}

 
void Game::destroyProjectile(Projectile* p_projectile,std::vector<Projectile*>::iterator& p_prjIt) {
	auto prjIt = std::find(projectiles.begin(), projectiles.end(), p_projectile);
	auto animIt = std::find(animationProjectiles.begin(), animationProjectiles.end(), p_projectile->getAnimation());

	if (prjIt == projectiles.end()) {
		std::cout << "Didn't find projectile to destroy!" << std::endl;
		return;
	}
	
	delete p_projectile;

	p_prjIt = projectiles.erase(prjIt);
}

void Game::destroyEnemy(Enemy* p_enemy, std::vector<Enemy*>::iterator& p_eneIt) {
	auto eneIt = std::find(enemies.begin(), enemies.end(), p_enemy);
	auto animIt = std::find(animationEnemies.begin(), animationEnemies.end(), p_enemy->getAnimation());

	if (eneIt == enemies.end()) {
		std::cout << "Didn't find an enemy to destroy!" << std::endl;
		return;
	}

	delete p_enemy;

	p_eneIt = enemies.erase(eneIt);
}