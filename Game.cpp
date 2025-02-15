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

//Initalize window, resourceManager,
Game::Game()
	:window("Gametest", 1280, 720), resourceManager(window.getRenderer()), player(nullptr){}

//Starting the game (load all game textures, and initalize going-to-be-used GameObject) 
void Game::start() {
	//Load all textures
	std::vector<std::string> allTexturePaths = {
		"./asset/player/witch-idle-sprite.png",
		"./asset/grass.png",
		"./asset/fireball_sprite.png"
	};
	resourceManager.loadTexture(allTexturePaths);
	//Set textures
	SDL_Texture* playerTexture = resourceManager.getTexture(allTexturePaths[0]);
	SDL_Texture* grassTexture = resourceManager.getTexture(allTexturePaths[1]);
	SDL_Texture* fireballTexture = resourceManager.getTexture(allTexturePaths[2]);

	

	SDL_Rect playerFrame = { 0, 0 , 64, 64 };
	

	//Set GameObject
	float fireBallSpeed = 10;
	Projectile* fireball = new Projectile(Vector2f(0, 0), fireballTexture, playerFrame, Vector2f(1, 0), fireBallSpeed);
	projectilePrefabs.push_back(fireball);

	player = new Player(Vector2f(0, 0), playerTexture, playerFrame, *fireball);
	playerSpeed = 5;
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
				if (inputManager.keyStates[SDLK_SPACE]) player->shootFireball(projectiles);
				movement.normalize();

				player->move(movement * playerSpeed);
				
			}
			accumulator -= timeStep;
		}
		
		

		for (auto& fb : projectiles) {
			fb.shoot(player->getPos());
		}
		//Destroy out of bound projectiles
		destroyProjectiles();
		//Clear the screen
		window.clear();
		//Draw the screen
		window.render(*player);
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