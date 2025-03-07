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
#include "UI.h"



void settingsButtonFunction() {
	
}



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
		"./asset/slime-move-sprite.png",
		"./asset/UI/button_normal.png",
		"./asset/UI/button_hover.png",
		"./asset/UI/button_active.png",
		"./asset/UI/modal.png"
	};
	resourceManager.loadTexture(allTexturePaths);

	//Set textures
	SDL_Texture* playerTexture = resourceManager.getTexture(allTexturePaths[0]);
	SDL_Texture* grassTexture = resourceManager.getTexture(allTexturePaths[1]);
	SDL_Texture* fireballTexture = resourceManager.getTexture(allTexturePaths[2]);
	SDL_Texture* slimeTexture = resourceManager.getTexture(allTexturePaths[3]);
	SDL_Texture* buttonNormalTexture = resourceManager.getTexture(allTexturePaths[4]);
	SDL_Texture* buttonHoverTexture = resourceManager.getTexture(allTexturePaths[5]);
	SDL_Texture* buttonActiveTexture = resourceManager.getTexture(allTexturePaths[6]);
	SDL_Texture* modalTexture = resourceManager.getTexture(allTexturePaths[7]);

	//Set some frames
	SDL_Rect defaultFrame = { 0, 0 , 64, 64 };
	SDL_Rect grassFrame = { 0, 0, 240, 120 };
	SDL_Rect buttonFrame = { 0, 0, 128 , 64 };
	SDL_Rect modalFrame = { 0, 0, 600, 600 };

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
	Animation* buttonNormalAnimation = new Animation(Vector2f(0, 0), buttonNormalTexture, 1, buttonFrame, 100);
	Animation* buttonHoverAnimation = new Animation(Vector2f(0, 0), buttonHoverTexture, 1, buttonFrame, 100);
	Animation* buttonActiveAnimation = new Animation(Vector2f(0, 0), buttonActiveTexture, 1, buttonFrame, 100);
	Animation* modalAnimation = new Animation(Vector2f(0, 0), modalTexture, 1, modalFrame, 100);

	//Set text
	TTF_Font* normalFont = TTF_OpenFont("./asset/font/Roboto/font.ttf", 20);
	TTF_Font* boldFont = TTF_OpenFont("./asset/font/Roboto/static/Roboto_Condensed-SemiBold.ttf", 32);
	SDL_Color black = { 0, 0, 0, 255 };
	SDL_Color white = { 255, 255, 255, 255 };
	Text* settingsText = new Text("Settings", Vector2f(0,0),black,window.getRenderer(), normalFont);
	Text* menuText = new Text("Menu", Vector2f(0, 0), black, window.getRenderer(), normalFont);
	Text* resumeText = new Text("Resume", Vector2f(0, 0), black, window.getRenderer(), normalFont);
	Text* playText = new Text("Play", Vector2f(0, 0), black, window.getRenderer(), normalFont);
	Text* quitText = new Text("Quit", Vector2f(0, 0), black, window.getRenderer(), normalFont);
	Text* settingsModalText = new Text("Settings", Vector2f(0, 0), white, window.getRenderer(), boldFont);

	//Set button
	Button* settingsButton = new Button(Vector2f(1100, 0), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, settingsText, settingsButtonFunction);
	Button* menuButton = new Button(Vector2f(1100, 0), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, menuText, settingsButtonFunction);
	Button* resumeButton = new Button(Vector2f(1100, 0), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, resumeText, settingsButtonFunction);
	Button* playButton = new Button(Vector2f(1100, 0), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, playText, settingsButtonFunction);
	Button* quitButton = new Button(Vector2f(1100, 0), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, quitText, settingsButtonFunction);

	//Set of buttons
	buttonsInSettingModal.push_back(menuButton);
	buttonsInSettingModal.push_back(resumeButton);

	buttonsInMenu.push_back(playButton);
	buttonsInMenu.push_back(quitButton);

	//Set modal
	Modal* settingModal = new Modal(buttonsInSettingModal, "Settings");

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
	animationPrefabs.push_back(buttonNormalAnimation);
	animationPrefabs.push_back(buttonActiveAnimation);
	animationPrefabs.push_back(buttonHoverAnimation);
	animationPrefabs.push_back(modalAnimation);

	projectilePrefabs.push_back(fireball);

	enemyPrefabs.push_back(slime);

	texts.push_back(settingsText);
	texts.push_back(menuText);
	texts.push_back(resumeText);
	texts.push_back(playText);
	texts.push_back(quitText);
	texts.push_back(settingsModalText);

	buttons.push_back(settingsButton);
	buttons.push_back(menuButton);
	buttons.push_back(resumeButton);
	buttons.push_back(playButton);
	buttons.push_back(quitButton);
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
	//Check collision of player's projectiles and enemies
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

	for (auto& btn : buttons) {
		btn->handleInput(e);
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
				if (e.type == SDL_MOUSEBUTTONDOWN) {
					
				}
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

		for (auto& btn : buttons) {
			window.renderUI(buttons[0]);
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

	for (Animation* anim : animationGrass) {
		delete anim;
	}

	gameObjectPrefabs.clear();
	animationPrefabs.clear();
	projectilePrefabs.clear();
	enemyPrefabs.clear();
	animationGrass.clear();
	animationEnemies.clear();
	animationProjectiles.clear();
	animationGrass.clear();

	
	delete player;
}

void Game::destroyOutOfBound() {
	for (auto prjIt = projectiles.begin(); prjIt != projectiles.end();) {
		if ((*prjIt)->getPos().x >= 1280 || (*prjIt)->getPos().y >= 720) {
			auto animIt = std::find(animationProjectiles.begin(), animationProjectiles.end(), (*prjIt)->getAnimation());
			if (animIt != animationProjectiles.end()) {
				delete* animIt;
				animationProjectiles.erase(animIt);

			}	
			delete *prjIt;
			prjIt = projectiles.erase(prjIt);
			std::cout << "Projectile destroyed!"<<std::endl;
		}
		else {
			++prjIt;
		}
	}

	for (auto eneIt = enemies.begin(); eneIt != enemies.end(); ) {
		if ((*eneIt)->getPos().x < -100 || (*eneIt)->getPos().y <0) {
			auto animIt = std::find(animationEnemies.begin(), animationEnemies.end(), (*eneIt)->getAnimation());
			if (animIt != animationEnemies.end()) {
				delete* animIt;
				animationEnemies.erase(animIt);
			}
			delete *eneIt;
			eneIt = enemies.erase(eneIt);
			std::cout << "Enemy destroyed!" << std::endl;
		}
		else {
			++eneIt;
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