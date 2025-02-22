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

	//Set Animation
	Animation* slimeAnimation = new Animation(Vector2f(0, 0), slimeTexture, 1, defaultFrame, 100);
	Animation* grassAnimation = new Animation(Vector2f(0, 0), grassTexture, 1, grassFrame, 100);
	Animation* fireBallAnimation = new Animation(Vector2f(0, 0), fireballTexture, 2, defaultFrame, 100);

	//Set projectiles
	Projectile* fireball = new Projectile(Vector2f(0, 0), Vector2f(1, 0), fireBallSpeed, fireBallAnimation);

	//Set player
	player = new Player(Vector2f(0, 0), nullptr, *fireball);
	Animation* playerIdleAnimation = new Animation(player->getPos(), playerTexture, 2, defaultFrame, 300);
	player->setAnimation(playerIdleAnimation);
	projectilePrefabs.push_back(fireball);

	//Push all animations for easier deconstruction
	animations.push_back(playerIdleAnimation);
	animations.push_back(fireBallAnimation);
	animations.push_back(grassAnimation);
	animations.push_back(slimeAnimation);
}

void Game::logic() {

}

void Game::graphic() {
	//Set grass field in the game
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			Animation* newGrassAnimation = new Animation(*animations[2]);
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
			player->shootFireball(projectiles, animations[1], animationProjectiles);
			player->setLastShotFb(currentTime);
		};
	}

	p_movement.normalize();

	p_movement.print();

	
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
	Animation* playerIdleAnimation = animations[0];
	Animation* fireBallAnimation = animations[1];

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

		//Player movement
		player->move(movement * playerSpeed);
		playerIdleAnimation->setPos(player->getPos());

		//Fireball movement
		for (auto& fb : projectiles) {
			fb.update(player->getPos(), currentTime);
		}

		//Destroy out of bound projectiles
		destroyProjectiles();

		//Clear the screen
		window.clear();

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
			window.renderAnimation64(fb.getAnimation());
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

	for (Animation* anim : animations) {
		delete anim;
	}
	
	for (Projectile* pj : projectilePrefabs) {
		delete pj;
	}

	for (Animation* anim : animationGrass) {
		delete anim;
	}

	animations.clear();
	animationGrass.clear();
	projectilePrefabs.clear();
	
	delete player;
}


void Game::destroyProjectiles() {
	for (auto i = 0; i < projectiles.size();) {
		if (projectiles[i].getPos().x >= 1280 || projectiles[i].getPos().y >= 720) {
			delete projectiles[i].getAnimation();
			projectiles.erase(projectiles.begin() + i);
			std::cout << "Projectile destroyed!"<<std::endl;
		}
		else {
			i++;
		}
	}
}