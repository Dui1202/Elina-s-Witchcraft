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
#include <string>

enum enumSkillHolder {
	FIREBALL_SKILLHOLDER,
	SNOWBALL_SKILLHOLDER,
	WINDSTORM_SKILLHOLDER
};

enum enumModal{
	SETTING_MODAL,
	SHOP_MODAL
};

enum enumButton {
	SETTING_BUTTON,
	MENU_BUTTON,
	RESUME_BUTTON,
	SHOP_BUTTON
};

enum enumText {
	SETTING_TEXT,
	MENU_TEXT,
	RESUME_TEXT,
	PLAY_TEXT,
	QUIT_TEXT,
	SETTING_MODAL_TEXT,
	SHOP_TEXT,
	COIN_TEXT,
	LEVELUP_FIREBALL_TEXT,
	LEVELUP_SNOWBALL_TEXT,
	LEVELUP_WINDSTORM_TEXT
};

void circularMotion(Enemy* &p_enemy, Vector2f p_center, float p_angleSpeed) {
	float radius = 20;
	float angle = p_enemy->getAngle();
	Vector2f motion(p_center.x + radius * cos(angle), p_center.y + radius * sin(angle));

	p_enemy->setPos(motion);

	p_enemy->setAngle(angle + p_angleSpeed);
}

void emptyFunction() {
	std::cout << "lmao" << std::endl;
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
		"./asset/projectiles/fireball_sprite.png",
		"./asset/slime-move-sprite.png",
		"./asset/UI/button_normal.png",
		"./asset/UI/button_hover.png",
		"./asset/UI/button_active.png",
		"./asset/UI/modal.png",
		"./asset/background.png",
		"./asset/projectiles/snowball_sprite.png",
		"./asset/projectiles/windstorm_sprite.png",
		"./asset/UI/fireball_skillholder.png",
		"./asset/UI/snowball_skillholder.png",
		"./asset/UI/windstorm_skillholder.png",
		"./asset/UI/outer_bar.png",
		"./asset/UI/inner_hp_bar.png",
		"./asset/UI/inner_cooldown_bar.png"
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
	SDL_Texture* backgroundTexture = resourceManager.getTexture(allTexturePaths[8]);
	SDL_Texture* snowBallTexture = resourceManager.getTexture(allTexturePaths[9]);
	SDL_Texture* windStormTexture = resourceManager.getTexture(allTexturePaths[10]);
	SDL_Texture* fireBallSkillHolderTexture = resourceManager.getTexture(allTexturePaths[11]);
	SDL_Texture* snowBallSkillHolderTexture = resourceManager.getTexture(allTexturePaths[12]);
	SDL_Texture* windStormSkillHolderTexture = resourceManager.getTexture(allTexturePaths[13]);
	SDL_Texture* outerBarTexture = resourceManager.getTexture(allTexturePaths[14]);
	SDL_Texture* innerHpBarTexture = resourceManager.getTexture(allTexturePaths[15]);
	SDL_Texture* innerCoolDownBarTexture = resourceManager.getTexture(allTexturePaths[16]);

	//Set some frames
	SDL_Rect defaultFrame = { 0, 0 , 64, 64 };
	SDL_Rect grassFrame = { 0, 0, 240, 120 };
	SDL_Rect buttonFrame = { 0, 0, 128 , 64 };
	SDL_Rect modalFrame = { 0, 0, 600, 600 };
	SDL_Rect backgroundFrame = { 0, 0, 1280, 120 };
	SDL_Rect skillHolderFrame = { 0, 0, 100, 100 };
	SDL_Rect skillHolderCoolDownFrame = { 100, 0, 100, 100 };
	SDL_Rect windStormFrame = { 0, 0, 64, 128 };
	SDL_Rect outerBarFrame = { 0, 0, 128, 16 };
	SDL_Rect innerBarFrame = { 0, 0, 124, 12 };

	//Set some default positions
	Vector2f settingBtnPosition(1100, 10);
	Vector2f shopBtnPosition(50, 10);
	Vector2f coinTextPosition(50, 80);

	//Set some in-game varibles
	playerSpeed = 5;
	float fireBallSpeed = 10;
	float fireBallStr = 5;
	Uint32 fireBallCoolDown = 500;

	float snowBallSpeed = 10;
	float snowBallStr = 2;
	Uint32 snowBallCoolDown = 2000;

	float windStormSpeed = 6;
	float windStormStr = 1;
	Uint32 windStormCoolDown = 1000;

	float slimeSpeed = 2;
	float slimeHp = 10;
	int slimeCoinDrop = 50;
	Collider slimeCollider(SDL_Rect({ 1,1, 100, 100 }));

	//Set some default scale
	float renderScale64 = 1.5;
	float renderScaleHpBar = 0.5;
	float renderScaleCoolDownBar = 0.5;

	//Set Animation
	Animation* playerIdleAnimation = new Animation(Vector2f(0, 0), playerTexture, 2, defaultFrame, 300 , renderScale64);
	Animation* slimeAnimation = new Animation(Vector2f(0, 0), slimeTexture, 1, defaultFrame, 100, renderScale64);
	Animation* grassAnimation = new Animation(Vector2f(0, 0), grassTexture, 1, grassFrame, 100);
	Animation* fireBallAnimation = new Animation(Vector2f(0, 0), fireballTexture, 2, defaultFrame, 100, renderScale64);
	Animation* buttonNormalAnimation = new Animation(Vector2f(0, 0), buttonNormalTexture, 1, buttonFrame, 100);
	Animation* buttonHoverAnimation = new Animation(Vector2f(0, 0), buttonHoverTexture, 1, buttonFrame, 100);
	Animation* buttonActiveAnimation = new Animation(Vector2f(0, 0), buttonActiveTexture, 1, buttonFrame, 100);
	Animation* modalAnimation = new Animation(Vector2f(0, 0), modalTexture, 1, modalFrame, 100);
	Animation* backgroundAnimation = new Animation(Vector2f(0, 0), backgroundTexture, 1, backgroundFrame, 100);
	Animation* snowBallAnimation = new Animation(Vector2f(0, 0), snowBallTexture, 2, defaultFrame, 100, renderScale64);
	Animation* windStormAnimation = new Animation(Vector2f(0, 0), windStormTexture, 2, windStormFrame, 200, renderScale64);
	Animation* fireBallSkillHolderAnimation = new Animation(Vector2f(0, 0), fireBallSkillHolderTexture, 1, skillHolderFrame, 100);
	Animation* snowBallSkillHolderAnimation = new Animation(Vector2f(0, 0), snowBallSkillHolderTexture, 1, skillHolderFrame, 100);
	Animation* windStormSkillHolderAnimation = new Animation(Vector2f(0, 0), windStormSkillHolderTexture, 1, skillHolderFrame, 100);
	Animation* fireBallSkillHolderCoolDownAnimation = new Animation(Vector2f(0, 0), fireBallSkillHolderTexture, 1, skillHolderCoolDownFrame, 100);
	Animation* snowBallSkillHolderCoolDownAnimation = new Animation(Vector2f(0, 0), snowBallSkillHolderTexture, 1, skillHolderCoolDownFrame, 100);
	Animation* windStormSkillHolderCoolDownAnimation = new Animation(Vector2f(0, 0), windStormSkillHolderTexture, 1, skillHolderCoolDownFrame, 100);
	Animation* outerBarAnimation = new Animation(Vector2f(0, 0), outerBarTexture, 1, outerBarFrame, 100, renderScaleHpBar);
	Animation* innerHpBarAnimation = new Animation(Vector2f(0, 0), innerHpBarTexture, 1, innerBarFrame, 100, renderScaleHpBar);
	Animation* innerCoolDownBarAnimation = new Animation(Vector2f(0, 0), innerCoolDownBarTexture, 1, innerBarFrame, 100, renderScaleCoolDownBar);

	Animation* bigButtonNormalAnimation = new Animation(Vector2f(0, 0), buttonNormalTexture, 1, buttonFrame, 100, 2);
	Animation* bigButtonHoverAnimation = new Animation(Vector2f(0, 0), buttonHoverTexture, 1, buttonFrame, 100, 2);
	Animation* bigButtonActiveAnimation = new Animation(Vector2f(0, 0), buttonActiveTexture, 1, buttonFrame, 100, 2);
	//Set text
	TTF_Font* normal8BitFont = TTF_OpenFont("./asset/font/VT323/VT323-Regular.ttf", 24);
	TTF_Font* normalFont = TTF_OpenFont("./asset/font/Roboto/font.ttf", 20);
	TTF_Font* boldFont = TTF_OpenFont("./asset/font/Roboto/static/Roboto_Condensed-SemiBold.ttf", 32);
	SDL_Color black = { 0, 0, 0, 255 };
	SDL_Color white = { 255, 255, 255, 255 };

	Text* settingsText = new Text("Settings", Vector2f(0,0),black,window.getRenderer(), normal8BitFont);
	Text* menuText = new Text("Menu", Vector2f(0, 0), black, window.getRenderer(), normal8BitFont);
	Text* resumeText = new Text("Resume", Vector2f(0, 0), black, window.getRenderer(), normal8BitFont);
	Text* playText = new Text("Play", Vector2f(0, 0), black, window.getRenderer(), normal8BitFont);
	Text* quitText = new Text("Quit", Vector2f(0, 0), black, window.getRenderer(), normal8BitFont);
	Text* settingsModalText = new Text("Settings", Vector2f(0, 0), white, window.getRenderer(), boldFont);
	Text* shopText = new Text("Shop", Vector2f(0, 0), black, window.getRenderer(), normal8BitFont);
	Text* coinText = new Text("Coin: 0", coinTextPosition, white, window.getRenderer(), normal8BitFont);
	Text* levelUpFireBallText = new Text("Level up Fireball!", Vector2f(0, 0), black, window.getRenderer(), normal8BitFont);
	Text* levelUpSnowBallText = new Text("Level up Snowball!", Vector2f(0, 0), black, window.getRenderer(), normal8BitFont);
	Text* levelUpWindStormText = new Text("Level up Windstorm!", Vector2f(0, 0), black, window.getRenderer(), normal8BitFont);


	//Set button
	Button* settingsButton = new Button(settingBtnPosition, buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, settingsText, animationUIs, std::bind(&Game::settingsButtonFunction, this));
	Button* menuButton = new Button(Vector2f(0, 0), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, menuText, animationUIs, emptyFunction);
	Button* resumeButton = new Button(Vector2f(0, 0), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, resumeText, animationUIs, emptyFunction);
	Button* playButton = new Button(Vector2f(50, 50), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, playText, animationUIs, emptyFunction);
	Button* quitButton = new Button(Vector2f(100, 100), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, quitText, animationUIs, emptyFunction);
	Button* shopButton = new Button(shopBtnPosition, buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, shopText, animationUIs, std::bind(&Game::shopButtonFunction, this));
	Button* LevelUpFireBallButton = new Button(Vector2f(0 ,0), bigButtonNormalAnimation, bigButtonHoverAnimation, bigButtonActiveAnimation, levelUpFireBallText, animationUIs, std::bind(&Game::levelUpFireBall, this));
	Button* LevelUpSnowBallButton = new Button(Vector2f(0, 0), bigButtonNormalAnimation, bigButtonHoverAnimation, bigButtonActiveAnimation, levelUpSnowBallText, animationUIs, std::bind(&Game::levelUpSnowBall, this));
	Button* LevelUpWindStormButton = new Button(Vector2f(0, 0), bigButtonNormalAnimation, bigButtonHoverAnimation, bigButtonActiveAnimation, levelUpWindStormText, animationUIs, std::bind(&Game::levelUpWindStorm, this));

	//Set of buttons
	buttonsInSettingModal.push_back(menuButton);
	buttonsInSettingModal.push_back(resumeButton);

	buttonsInShopModal.push_back(LevelUpFireBallButton);
	buttonsInShopModal.push_back(LevelUpSnowBallButton);
	buttonsInShopModal.push_back(LevelUpWindStormButton);


	//Set Bar
	float hpp = 100;
	Bar* slimeHpBar = new Bar(Vector2f(0, 0), outerBarAnimation, innerHpBarAnimation, slimeHp, animationUIs);
	Bar* fireBallCDBar = new Bar(Vector2f(0, 0), outerBarAnimation, innerCoolDownBarAnimation, fireBallCoolDown, animationUIs);
	Bar* snowBallCDBar = new Bar(Vector2f(0, 0), outerBarAnimation, innerCoolDownBarAnimation, snowBallCoolDown, animationUIs);
	Bar* windStormCDBar = new Bar(Vector2f(0, 0), outerBarAnimation, innerCoolDownBarAnimation, windStormCoolDown, animationUIs);

	//buttonsInMenu.push_back(playButton);
	//buttonsInMenu.push_back(quitButton);

	//Set modal
	Modal* settingModal = new Modal(Vector2f(0, 0), modalAnimation, buttonsInSettingModal, settingsModalText, animationUIs);
	Modal* shopModal = new Modal(Vector2f(0, 0), modalAnimation, buttonsInShopModal, settingsModalText, animationUIs);

	//Set Skill Holders
	SkillHolder* fireBallSkillHolder = new SkillHolder(Vector2f(200, 10), fireBallCDBar, fireBallSkillHolderAnimation, fireBallSkillHolderCoolDownAnimation, animationUIs, bars);
	SkillHolder* snowBallSkillHolder = new SkillHolder(Vector2f(310, 10), snowBallCDBar, snowBallSkillHolderAnimation, snowBallSkillHolderCoolDownAnimation, animationUIs, bars);
	SkillHolder* windStormSkillHolder = new SkillHolder(Vector2f(420, 10), windStormCDBar, windStormSkillHolderAnimation, windStormSkillHolderCoolDownAnimation, animationUIs, bars);

	//Set projectiles
	Projectile* fireball = new Projectile("fireBall", Vector2f(0, 0), Vector2f(1, 0), fireBallSpeed, fireBallStr, fireBallCoolDown, fireBallAnimation);
	Projectile* snowBall = new Projectile("snowBall", Vector2f(0, 0), Vector2f(1, 0), snowBallSpeed, snowBallStr, snowBallCoolDown, snowBallAnimation);
	Projectile* windStorm = new Projectile("windStorm", Vector2f(0, 0), Vector2f(1, 0), windStormSpeed, windStormStr, windStormCoolDown, windStormAnimation);

	//Set enemies
	Enemy* slime = new Enemy(Vector2f(0, 0), slimeAnimation, Vector2f(-1, 0), slimeSpeed, slimeHp, slimeCoinDrop, slimeHpBar, bars, animationEnemies);

	//Set positions
	settingModal->setPos(Vector2f(window.getWidth() / 2, window.getHeight() / 2) - Vector2f(settingModal->getWidth() / 2, settingModal->getHeight() / 2));
	shopModal->setPos(Vector2f(window.getWidth() / 2, window.getHeight() / 2) - Vector2f(shopModal->getWidth() / 2, shopModal->getHeight() / 2));

	//Push all animations for easier deconstruction
	animationPrefabs.push_back(playerIdleAnimation);
	animationPrefabs.push_back(fireBallAnimation);
	animationPrefabs.push_back(grassAnimation);
	animationPrefabs.push_back(slimeAnimation);
	animationPrefabs.push_back(buttonNormalAnimation);
	animationPrefabs.push_back(buttonActiveAnimation);
	animationPrefabs.push_back(buttonHoverAnimation);
	animationPrefabs.push_back(modalAnimation);
	animationPrefabs.push_back(backgroundAnimation);
	animationPrefabs.push_back(snowBallAnimation);
	animationPrefabs.push_back(windStormAnimation);
	animationPrefabs.push_back(fireBallSkillHolderAnimation);
	animationPrefabs.push_back(snowBallSkillHolderAnimation);
	animationPrefabs.push_back(windStormSkillHolderAnimation);
	animationPrefabs.push_back(outerBarAnimation);
	animationPrefabs.push_back(innerHpBarAnimation);
	animationPrefabs.push_back(innerCoolDownBarAnimation);

	projectilePrefabs.push_back(fireball);
	projectilePrefabs.push_back(snowBall);
	projectilePrefabs.push_back(windStorm);

	//Set player
	player = new Player(Vector2f(0, 362), nullptr, projectilePrefabs);
	playerIdleAnimation->setPos(player->getPos());
	player->setAnimation(playerIdleAnimation);

	enemyPrefabs.push_back(slime);

	texts.push_back(settingsText);
	texts.push_back(menuText);
	texts.push_back(resumeText);
	texts.push_back(playText);
	texts.push_back(quitText);
	texts.push_back(settingsModalText);
	texts.push_back(shopText);
	texts.push_back(coinText);
	texts.push_back(levelUpFireBallText);
	texts.push_back(levelUpSnowBallText);
	texts.push_back(levelUpWindStormText);

	buttons.push_back(settingsButton);
	buttons.push_back(menuButton);
	buttons.push_back(resumeButton);
	//buttons.push_back(playButton);
	//buttons.push_back(quitButton);
	buttons.push_back(shopButton);
	buttons.push_back(LevelUpFireBallButton);
	buttons.push_back(LevelUpSnowBallButton);
	buttons.push_back(LevelUpWindStormButton);

	modals.push_back(settingModal);
	modals.push_back(shopModal);

	skillHolders.push_back(fireBallSkillHolder);
	skillHolders.push_back(snowBallSkillHolder);
	skillHolders.push_back(windStormSkillHolder);

	barPrefabs.push_back(slimeHpBar);

	for (auto& skillHolder : skillHolders) {
		skillHolder->getBar()->deplete();
	}

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
				if ((*pjIt)->getName() == "fireBall") {
					std::cout << "Collide with enemy!" << std::endl;

					if (runCoolDown((*pjIt)->getCoolDownDamageTick(), (*pjIt)->getLastTick())) {
						(*pjIt)->setLastTick(currentTime);
						(*eneIt)->setHp((*eneIt)->getHp() - (*pjIt)->getStr());
						(*eneIt)->getBar()->update((*pjIt)->getStr());
					}
					destroyProjectile(*pjIt, pjIt);
					if ((*eneIt)->getHp() <= 0) {
						destroyEnemy(*eneIt, eneIt);
					}
					isDestroy = true;
					break;
				}
				else if ((*pjIt)->getName() == "snowBall") {

					if (runCoolDown((*pjIt)->getCoolDownDamageTick(), (*pjIt)->getLastTick())) {
						(*pjIt)->setLastTick(currentTime);
						(*eneIt)->setHp((*eneIt)->getHp() - (*pjIt)->getStr());
						(*eneIt)->setSpeed((*eneIt)->getSpeed() / 2);
						std::cout << (*pjIt)->getStr() << std::endl;
						(*eneIt)->getBar()->update((*pjIt)->getStr());

					}

					destroyProjectile(*pjIt, pjIt);
					if ((*eneIt)->getHp() <= 0) {
						destroyEnemy(*eneIt, eneIt);
					}
					isDestroy = true;
					break;
				}
				else if ((*pjIt)->getName() == "windStorm") {
					if (runCoolDown((*eneIt)->getCoolDownDamageTick(), (*eneIt)->getLastTick())) {
						(*eneIt)->setLastTick(currentTime - timePause);
						(*eneIt)->setHp((*eneIt)->getHp() - (*pjIt)->getStr());
						(*eneIt)->getBar()->update((*pjIt)->getStr());

					}
					circularMotion((*eneIt), (*pjIt)->getPos(), 0.5);
					if ((*eneIt)->getHp() <= 0) {
						destroyEnemy(*eneIt, eneIt);
					}
				}
				
			}
		}
		if (!isDestroy)
		{
			++pjIt;
		}
	}

}

void Game::graphic() {

	Animation* backgroundAnimation = animationPrefabs[8];

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

	if (inputManager.keyStates[SDLK_w].isHold || inputManager.keyStates[SDLK_w].isStart) p_movement.y -= 1;
	if (inputManager.keyStates[SDLK_s].isHold || inputManager.keyStates[SDLK_s].isStart) p_movement.y += 1;
	if (runCoolDown(player->getCurrentProjectile()->getCoolDown(), player->getCurrentProjectile()->getLastShot())) {
		if ((inputManager.keyStates[SDLK_SPACE].isHold || inputManager.keyStates[SDLK_SPACE].isStart) && (!isGamePause)) {
			player->shootProjectile(projectiles, animationProjectiles);
			player->getCurrentProjectile()->setLastShot(currentTime - timePause);
			if (player->getCurrentProjectile()->getName() == "fireBall") {
				skillHolders[FIREBALL_SKILLHOLDER]->getBar()->reset();
			}
			else if (player->getCurrentProjectile()->getName() == "snowBall") {
				skillHolders[SNOWBALL_SKILLHOLDER]->getBar()->reset();
			}
			else if (player->getCurrentProjectile()->getName() == "windStorm") {
				skillHolders[WINDSTORM_SKILLHOLDER]->getBar()->reset();
			}
		}
	}
	player->changeProjectile(e, inputManager);



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
	Animation* backgroundAnimation = animationPrefabs[8];
	
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
		for (auto& btn : buttons) {
			btn->handleInput(inputManager);
			btn->update();
		}
		updateCoin();
		inputManager.update();

		if (!isGamePause) {

			if (runCoolDown(spawnManager.getCooldown(), spawnManager.getLastTime())) {
				spawnManager.spawnEnemy(enemies, animationEnemies, slime);
				spawnManager.setLastTime(currentTime - timePause);
			}
			
			setPlayerInBound();
			UILogic();
			logic();

		//Player movement
			player->move(movement * playerSpeed);
			playerIdleAnimation->setPos(player->getPos());

			//Fireball movement
			for (auto& prj : projectiles) {
			prj->update(player->getPos(), currentTime);
		}

			//Slime movement
			for (auto& ene : enemies) {
				ene->update(currentTime);
			}
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
			
			//Render Background
		window.renderAnimation(backgroundAnimation);
		
			//Render Player
		window.renderAnimation(playerIdleAnimation);
		playerIdleAnimation->update(currentTime);

			//Render FireBall
		for (auto& fb : projectiles) {
			window.renderAnimation(fb->getAnimation());
		}
			
			//Render Enemies
		for (auto& sl : enemies) {
			window.renderAnimation(sl->getAnimation());
			window.renderUI(sl->getBar());
		}


		window.renderText(texts[COIN_TEXT]);

		for (auto& skillHolder : skillHolders) {
			window.renderUI(skillHolder);
		}

		for (auto& modal : modals) {
			if (modal->getIsOpen()) {
				window.renderUI(modal);
			}
		}

		for (auto& btn : buttons) {
			if (btn->getVisible()) {
				window.renderUI(btn);
			}
			
		}

		

		debug();
		

		//Show screen
		window.display();

		//std::cout << player->getPos().y << std::endl;

		//Show the fps on console
		//float fps = 1000.0f / frameTime;
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

	for (Projectile* prj : projectiles) {
		delete prj;
	}

	for (Enemy* ene : enemies) {
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

	for (Animation* anim : animationUIs) {
		delete anim;
	}

	for (Text* text : texts) {
		delete text;
	}

	for (Button* btn : buttons) {
		delete btn;
	}

	for (Button* btn : buttonsInMenu) {
		delete btn;
	}

	for (Button* btn : buttonsInSettingModal) {
		delete btn;
	}

	for (Modal* modal : modals) {
		delete modal;
	}

	gameObjectPrefabs.clear();
	animationPrefabs.clear();
	projectilePrefabs.clear();
	enemyPrefabs.clear();
	animationGrass.clear();
	animationEnemies.clear();
	animationProjectiles.clear();
	animationGrass.clear();
	animationUIs.clear();

	
	delete player;
}

void Game::destroyOutOfBound() {
	for (auto prjIt = projectiles.begin(); prjIt != projectiles.end();) {
		if ((*prjIt)->getName() != "windStorm") {
			if (((*prjIt)->getPos().x >= 1280 || (*prjIt)->getPos().y >= 720)) {
				auto animIt = std::find(animationProjectiles.begin(), animationProjectiles.end(), (*prjIt)->getAnimation());
				if (animIt != animationProjectiles.end()) {
					delete* animIt;
					animationProjectiles.erase(animIt);

				}
				delete* prjIt;
				prjIt = projectiles.erase(prjIt);
				std::cout << "Projectile destroyed!" << std::endl;
			}
			else {
				++prjIt;
			}
		}
		else {
			if (((*prjIt)->getPos().x >= 1200 || (*prjIt)->getPos().y >= 720)) {
				auto animIt = std::find(animationProjectiles.begin(), animationProjectiles.end(), (*prjIt)->getAnimation());
				if (animIt != animationProjectiles.end()) {
					delete* animIt;
					animationProjectiles.erase(animIt);

				}
				delete* prjIt;
				prjIt = projectiles.erase(prjIt);
				std::cout << "Projectile destroyed!" << std::endl;
			}
			else {
				++prjIt;
			}
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
	delete *animIt;
	animationProjectiles.erase(animIt);

	delete p_projectile;
	p_prjIt = projectiles.erase(prjIt);
}

void Game::destroyEnemy(Enemy* p_enemy, std::vector<Enemy*>::iterator& p_eneIt) {
	auto eneIt = std::find(enemies.begin(), enemies.end(), p_enemy);
	//auto animIt = std::find(animationEnemies.begin(), animationEnemies.end(), p_enemy->getAnimation());
	 
	player->setCoin(player->getCoin() + (*eneIt)->getCoinDrop());
	
	if (eneIt == enemies.end()) {
		std::cout << "Didn't find an enemy to destroy!" << std::endl;
		return;
	}

	delete p_enemy;

	p_eneIt = enemies.erase(eneIt);
}

void Game::settingsButtonFunction() {
	std::cout << "Pressed settingButton!" << std::endl;
	if (modals[SETTING_MODAL]->getIsOpen()) {
		modals[SETTING_MODAL]->close();
	}
	else {
		modals[SETTING_MODAL]->open();
	}
	pause(SHOP_BUTTON);
}

void Game::shopButtonFunction() {
	if (modals[SHOP_MODAL]->getIsOpen()) {
		modals[SHOP_MODAL]->close();
	}
	else {
		modals[SHOP_MODAL]->open();
	}
	pause(SETTING_BUTTON);
}

void Game::levelUpFireBall() {
	if (player->getCoin() >= projectilePrefabs[0]->getUpgradeCoin()) {
		projectilePrefabs[0]->levelUp();
		skillHolders[FIREBALL_SKILLHOLDER]->getBar()->setNewCoolDown(projectilePrefabs[0]->getCoolDown());
		player->setCoin(player->getCoin() - projectilePrefabs[0]->getUpgradeCoin());
		projectilePrefabs[0]->levelUpUpgradeCoin();
	}
}

void Game::levelUpSnowBall() {
	if (player->getCoin() >= projectilePrefabs[1]->getUpgradeCoin()) {
		projectilePrefabs[1]->levelUp();
		skillHolders[SNOWBALL_SKILLHOLDER]->getBar()->setNewCoolDown(projectilePrefabs[1]->getCoolDown());
		player->setCoin(player->getCoin() - projectilePrefabs[1]->getUpgradeCoin());
		projectilePrefabs[1]->levelUpUpgradeCoin();
	}
}

void Game::levelUpWindStorm() {
	if (player->getCoin() >= projectilePrefabs[2]->getUpgradeCoin()) {
		projectilePrefabs[2]->levelUp();
		skillHolders[WINDSTORM_SKILLHOLDER]->getBar()->setNewCoolDown(projectilePrefabs[2]->getCoolDown());
		player->setCoin(player->getCoin() - projectilePrefabs[2]->getUpgradeCoin());
		projectilePrefabs[2]->levelUpUpgradeCoin();

	}
}

void Game::pause(int p_button) {
	if (isGamePause) {
		isGamePause = false;
		Uint32 resumeTime = SDL_GetTicks();
		timePause += (resumeTime - startPause); // Accumulate pause duration
		buttons[p_button]->setEnable(true);
	}
	else {
		isGamePause = true;
		startPause = SDL_GetTicks();
		buttons[p_button]->setEnable(false);
	}
}

bool Game::runCoolDown(Uint32 p_coolDown, Uint32 p_lastTime) {
	Uint32 timer = currentTime - p_lastTime - timePause; // Use accumulated pause time
	return timer >= p_coolDown;
}

void Game::updateCoin() {
	texts[COIN_TEXT]->setText("Coin: " + std::to_string(player->getCoin()));
	texts[LEVELUP_FIREBALL_TEXT]->setText("Level Up Fireball! Coin to upgrade: " + std::to_string(projectilePrefabs[0]->getUpgradeCoin()));
	texts[LEVELUP_SNOWBALL_TEXT]->setText("Level Up Snowball! Coin to upgrade: " + std::to_string(projectilePrefabs[1]->getUpgradeCoin()));
	texts[LEVELUP_WINDSTORM_TEXT]->setText("Level Up Windstorm! Coin to upgrade: " + std::to_string(projectilePrefabs[2]->getUpgradeCoin()));

}

void Game::UILogic() {
	skillHolders[FIREBALL_SKILLHOLDER]->getBar()->update(currentTime - player->getFireBallPrefab()->getLastShot() - timePause);
	skillHolders[SNOWBALL_SKILLHOLDER]->getBar()->update(currentTime - player->getSnowBallPrefab()->getLastShot() - timePause);
	skillHolders[WINDSTORM_SKILLHOLDER]->getBar()->update(currentTime - player->getWindStormPrefab()->getLastShot() - timePause);
	if (player->getFireBallPrefab()->isOnCoolDown(currentTime - timePause)) {
		skillHolders[FIREBALL_SKILLHOLDER]->switchOnCoolDownAnimation();
	}
	else {
		skillHolders[FIREBALL_SKILLHOLDER]->switchActiveAnimation();
	}

	if (player->getSnowBallPrefab()->isOnCoolDown(currentTime - timePause)) {
		skillHolders[SNOWBALL_SKILLHOLDER]->switchOnCoolDownAnimation();
	}
	else {
		skillHolders[SNOWBALL_SKILLHOLDER]->switchActiveAnimation();
	}

	if (player->getWindStormPrefab()->isOnCoolDown(currentTime - timePause)) {
		skillHolders[WINDSTORM_SKILLHOLDER]->switchOnCoolDownAnimation();
	}
	else {
		skillHolders[WINDSTORM_SKILLHOLDER]->switchActiveAnimation();
	}

}

void Game::setPlayerInBound() {
	if (player->getPos().y >= (720 - 120)) {
		player->setPos(Vector2f(player->getPos().x, 720 - 120));
	}
	else if (player->getPos().y <= 120) {
		player->setPos(Vector2f(player->getPos().x, 120));
	}
}