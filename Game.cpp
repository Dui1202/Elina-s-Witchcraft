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

//Initalize window, resourceManager,
Game::Game()
	:window("Gametest", 1280, 720), resourceManager(window.getRenderer()), player(nullptr){}

//Starting the game (load all game textures, and initalize going-to-be-used GameObject) 
void Game::start() {
	//Load all textures
	std::vector<std::string> allTexturePaths = {
		"./asset/player/witch-idle-sprite-sheet.png",
		"./asset/grass.png",
		"./asset/fireball_sprite.png"
	};
	resourceManager.loadTexture(allTexturePaths);
	//Set textures
	SDL_Texture* playerTexture = resourceManager.getTexture(allTexturePaths[0]);
	SDL_Texture* grassTexture = resourceManager.getTexture(allTexturePaths[1]);
	SDL_Texture* fireballTexture = resourceManager.getTexture(allTexturePaths[2]);

	

	SDL_Rect defaultFrame = { 0, 0 , 64, 64 };
	

	//Set GameObject
	float fireBallSpeed = 10;
	Projectile* fireball = new Projectile(Vector2f(0, 0), fireballTexture, defaultFrame, Vector2f(1, 0), fireBallSpeed);
	projectilePrefabs.push_back(fireball);

	//Set Player GameObject
	player = new Player(Vector2f(0, 0), playerTexture, defaultFrame, *fireball);
	playerSpeed = 5;

	//Set Animation
	Animation* playerIdleAnimation = new Animation(player->getPos(), playerTexture, 2, { 0, 0, 64, 64 }, 300);
	animations.push_back(playerIdleAnimation);
	Animation* fireBallAnimation = new Animation(Vector2f(0, 0), fireballTexture, 2, defaultFrame, 100);
	animations.push_back(fireBallAnimation);
}

//Main game loop
void Game::update() {
	//Set flag for the game loop
	bool isGameRunning = true;

	SDL_Event e;
	//For program's frame rate
	Uint32 lastTime = SDL_GetTicks();
	float accumulator = 0.0f;
	const float timeStep = 16.67f;

	//Input
	InputManager inputManager;

	//GameObject reference
	Projectile* fireball = projectilePrefabs[0];
	Animation* playerIdleAnimation = animations[0];
	Animation* fireBallAnimation = animations[1];
	
	//The main game loop
	while (isGameRunning) {
		Uint32 currentTime = SDL_GetTicks();
		float frameTime = currentTime - lastTime;
		lastTime = currentTime;
		accumulator += frameTime;

		while (accumulator >= timeStep) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					isGameRunning = false;
				}
				inputManager.handleInput(e);

				Vector2f movement(0, 0);

				if (inputManager.keyStates[SDLK_w]) movement.y -= 1;
				if (inputManager.keyStates[SDLK_s]) movement.y += 1;
				if (currentTime - player->getLastShotFb() >= player->getCoolDownFb()) {
					if (inputManager.keyStates[SDLK_SPACE]) {
						player->shootFireball(projectiles);
						player->setLastShotFb(currentTime);
					};
				}

				movement.normalize();

				player->move(movement * playerSpeed);
				
			}
			accumulator -= timeStep;
		}

		playerIdleAnimation->setPos(player->getPos());
		//Fireball movement
		for (auto& fb : projectiles) {
			fb.shoot(player->getPos());
		}
		//Destroy out of bound projectiles
		destroyProjectiles();
		//Clear the screen
		window.clear();
		//Draw the screen

			//Render Player
		window.renderAnimation(*playerIdleAnimation);
		playerIdleAnimation->update(currentTime);

			//Render FireBall
		for (auto& fb : projectiles) {
			window.render(fb);
		}
		
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
	
	delete player;
}


void Game::destroyProjectiles() {
	for (auto i = 0; i < projectiles.size();) {
		if (projectiles[i].getPos().x >= 1280 || projectiles[i].getPos().y >= 720) {
			projectiles.erase(projectiles.begin() + i);
			std::cout << "Projectile destroyed!"<<std::endl;
		}
		else {
			i++;
		}
	}
}