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
#include "Wave.h"
#include "Enums.h"
#include <string>
#include <fstream>

const float RESTART_BUTTON_Y = 350;
const float MENU_BUTTON_Y = 250;
const float GAMEOVER_TEXT_Y = 100;
const float HIGHSCORE_TEXT_Y = 200;
const float MENU_TITLE_TEXT_Y = 50;
const float MENU_MODAL_Y = 300;
const float BOUND_X = 1280;
const float BOUND_Y = 720;
const float WINDSTORM_BOUND_X = 1200;
const float ENEMY_BOUND_X = -100;
const float ENEMY_BOUND_Y = 0;
const float PLAYER_BOUND_Y_POS = 120;
const float PLAYER_BOUND_Y_NEG = 600;
const float PLAYER_DEFAULT_POS_Y = 362;
const float SOUND_VOLUME = 72;

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
	:window("Gametest",BOUND_X, BOUND_Y), resourceManager(window.getRenderer()), player(nullptr){}

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
		"./asset/UI/inner_cooldown_bar.png",
		"./asset/UI/long_button.png",
		"./asset/UI/indicator.png",
		"./asset/golem_move_sprite.png",
		"./asset/miku_move_sprite.png",
		"./asset/fire_slime_move_sprite.png",
		"./asset/ice_slime_move_sprite.png",
		"./asset/menu_background.png"
	};
	resourceManager.loadTexture(allTexturePaths);

	std::vector<std::string> allSFXPaths = {
		"./asset/SFX/Button SFX.wav",
		"./asset/SFX/Fireball SFX.wav",
		"./asset/SFX/Snowball SFX.wav",
		"./asset/SFX/Windstorm SFX.wav",
		"./asset/SFX/Level up SFX.wav"
	};
	resourceManager.loadSFX(allSFXPaths);

	std::vector<std::string> allMusicPaths = {
		"./asset/SFX/Gameplay Music.mp3",
		"./asset/SFX/Game over Music.mp3",
		"./asset/SFX/Menu Music.mp3"

	};
	resourceManager.loadMusic(allMusicPaths);

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
	SDL_Texture* longButtonTexture = resourceManager.getTexture(allTexturePaths[17]);
	SDL_Texture* indicatorTexture = resourceManager.getTexture(allTexturePaths[18]);
	SDL_Texture* golemMoveTexture = resourceManager.getTexture(allTexturePaths[19]);
	SDL_Texture* mikuMoveTexture = resourceManager.getTexture(allTexturePaths[20]);
	SDL_Texture* fireSlimeMoveTexture = resourceManager.getTexture(allTexturePaths[21]);
	SDL_Texture* iceSlimeMoveTexture = resourceManager.getTexture(allTexturePaths[22]);
	SDL_Texture* menuBackgroundTexture = resourceManager.getTexture(allTexturePaths[23]);

	{
		int index = 0;
		for (std::string& path : allSFXPaths) {
			SFXPrefabs.push_back(resourceManager.getSFX(allSFXPaths[index]));
			index++;
		}
	}

	{
		int index = 0;
		for (std::string& path : allMusicPaths) {
			musicPrefabs.push_back(resourceManager.getMusic(allMusicPaths[index]));
			index++;
		}
	}

	Mix_VolumeMusic(SOUND_VOLUME);
	Mix_VolumeChunk(SFXPrefabs[BUTTON_SFX], SOUND_VOLUME);


	//Set some frames
	SDL_Rect defaultFrame = { 0, 0 , 64, 64 };
	SDL_Rect p128Frame = { 0, 0, 128 ,128 };
	SDL_Rect grassFrame = { 0, 0, 240, 120 };
	SDL_Rect buttonFrame = { 0, 0, 128 , 64 };
	SDL_Rect modalFrame = { 0, 0, 600, 600 };
	SDL_Rect backgroundFrame = { 0, 0, 1280, 120 };
	SDL_Rect skillHolderFrame = { 0, 0, 100, 100 };
	SDL_Rect skillHolderCoolDownFrame = { 100, 0, 100, 100 };
	SDL_Rect windStormFrame = { 0, 0, 64, 128 };
	SDL_Rect outerBarFrame = { 0, 0, 128, 16 };
	SDL_Rect innerBarFrame = { 0, 0, 124, 12 };
	SDL_Rect normalLongButtonFrame = { 0, 0, 512, 64 };
	SDL_Rect hoverLongButtonFrame = { 0, 64, 512, 64 };
	SDL_Rect activeLongButtonFrame = { 0, 128, 512, 64 };
	SDL_Rect indicatorFrame = { 0, 0, 100, 100 };
	SDL_Rect menuBackgroundFrame = { 0 , 0, 1280, 720 };

	//Set some default positions
	Vector2f settingBtnPosition(1100, 10);
	Vector2f shopBtnPosition(50, 10);
	Vector2f coinTextPosition(50, 80);
	Vector2f gameHpTextPosition(50, 680);
	Vector2f gameScoreTextPosition(50, 630);
	Vector2f fireBallSkillHolderPosition(200,10);
	Vector2f snowBallSkillHolderPosition(310, 10);
	Vector2f windStormSkillHolderPosition(420, 10);


	//Set some in-game varibles
	playerSpeed = 5;
	float fireBallSpeed = 10;
	float fireBallStr = 5;
	Uint32 fireBallCoolDown = 500;

	float snowBallSpeed = 10;
	float snowBallStr = 2;
	Uint32 snowBallCoolDown = 1000;

	float windStormSpeed = 6;
	float windStormStr = 1;
	Uint32 windStormCoolDown = 10000;

	float slimeSpeed = 1.5;
	float slimeHp = 10;
	int slimeCoinDrop = 5;
	//Collider slimeCollider(SDL_Rect({ 1,1, 100, 100 }));

	float golemSpeed = 0.8;
	float golemHp = 30;
	int golemCoinDrop = 20;

	float mikuSpeed = 5;
	float mikuHp = 5;
	int mikuCoinDrop = 5;

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

	Animation* longButtonNormalAnimation = new Animation(Vector2f(0, 0), longButtonTexture, 1, normalLongButtonFrame, 100);
	Animation* longButtonHoverAnimation = new Animation(Vector2f(0, 0), longButtonTexture, 1, hoverLongButtonFrame, 100);
	Animation* longButtonActiveAnimation = new Animation(Vector2f(0, 0), longButtonTexture, 1, activeLongButtonFrame, 100);

	Animation* indicatorAnimation = new Animation(Vector2f(0, 0), indicatorTexture, 1, indicatorFrame, 100);
	Animation* golemMoveAnimation = new Animation(Vector2f(0, 0), golemMoveTexture, 3, defaultFrame, 200, 2.5);
	Animation* mikuMoveAnimation = new Animation(Vector2f(0, 0), mikuMoveTexture, 2, p128Frame, 100);
	Animation* fireSlimeAnimation = new Animation(Vector2f(0, 0), fireSlimeMoveTexture, 2, defaultFrame, 200, renderScale64);
	Animation* iceSlimeAnimation = new Animation(Vector2f(0, 0), iceSlimeMoveTexture, 2, defaultFrame, 400, renderScale64);

	Animation* menuBackgroundAnimation = new Animation(Vector2f(0, 0), menuBackgroundTexture, 1, menuBackgroundFrame, 100);

	animationPrefabs.push_back(playerIdleAnimation);
	animationPrefabs.push_back(slimeAnimation);
	animationPrefabs.push_back(grassAnimation);
	animationPrefabs.push_back(fireBallAnimation);
	animationPrefabs.push_back(buttonNormalAnimation);
	animationPrefabs.push_back(buttonHoverAnimation);
	animationPrefabs.push_back(buttonActiveAnimation);
	animationPrefabs.push_back(modalAnimation);
	animationPrefabs.push_back(backgroundAnimation);
	animationPrefabs.push_back(snowBallAnimation);
	animationPrefabs.push_back(windStormAnimation);
	animationPrefabs.push_back(fireBallSkillHolderAnimation);
	animationPrefabs.push_back(snowBallSkillHolderAnimation);
	animationPrefabs.push_back(windStormSkillHolderAnimation);
	animationPrefabs.push_back(fireBallSkillHolderCoolDownAnimation);
	animationPrefabs.push_back(snowBallSkillHolderCoolDownAnimation);
	animationPrefabs.push_back(windStormSkillHolderCoolDownAnimation);
	animationPrefabs.push_back(outerBarAnimation);
	animationPrefabs.push_back(innerHpBarAnimation);
	animationPrefabs.push_back(innerCoolDownBarAnimation);
	animationPrefabs.push_back(longButtonNormalAnimation);
	animationPrefabs.push_back(longButtonHoverAnimation);
	animationPrefabs.push_back(longButtonActiveAnimation);
	animationPrefabs.push_back(indicatorAnimation);
	animationPrefabs.push_back(golemMoveAnimation);
	animationPrefabs.push_back(mikuMoveAnimation);
	animationPrefabs.push_back(fireSlimeAnimation);
	animationPrefabs.push_back(iceSlimeAnimation);
	animationPrefabs.push_back(menuBackgroundAnimation);

	//Set text
	TTF_Font* normal8BitFont = TTF_OpenFont("./asset/font/VT323/VT323-Regular.ttf", 24);
	TTF_Font* large8BitFont = TTF_OpenFont("./asset/font/VT323/VT323-Regular.ttf", 96);
	TTF_Font* normalFont = TTF_OpenFont("./asset/font/Roboto/font.ttf", 20);
	TTF_Font* boldFont = TTF_OpenFont("./asset/font/Roboto/static/Roboto_Condensed-SemiBold.ttf", 32);
	SDL_Color black = { 0, 0, 0, 255 };
	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Color red = { 255, 0, 0, 255 };

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
	Text* gameHpText = new Text("Home HP: ", gameHpTextPosition, black, window.getRenderer(), normal8BitFont);
	Text* menuTitleText = new Text("Elina's Witchcraft", Vector2f(0, 0), white, window.getRenderer(), large8BitFont);
	Text* gameOverText = new Text("GAME OVER!", Vector2f(0, 0), red, window.getRenderer(), large8BitFont);
	Text* restartText = new Text("Restart", Vector2f(0, 0), black, window.getRenderer(), normal8BitFont);
	Text* gameScoreText = new Text("Score: ", gameScoreTextPosition, black, window.getRenderer(), normal8BitFont);
	Text* highScoreText = new Text("New High Score: ", Vector2f(0, 0), black, window.getRenderer(), normal8BitFont);
	Text* musicOnOffText = new Text("Music", Vector2f(0, 0), black, window.getRenderer(), normal8BitFont);

	textsInGame.push_back(settingsText);
	textsInGame.push_back(menuText);
	textsInGame.push_back(resumeText);
	textsInGame.push_back(playText);
	textsInGame.push_back(quitText);
	textsInGame.push_back(settingsModalText);
	textsInGame.push_back(shopText);
	textsInGame.push_back(coinText);
	textsInGame.push_back(levelUpFireBallText);
	textsInGame.push_back(levelUpSnowBallText);
	textsInGame.push_back(levelUpWindStormText);
	textsInGame.push_back(gameHpText);
	textsInGame.push_back(gameScoreText);

	textsInMenu.push_back(menuTitleText);

	textsInGameoverScene.push_back(gameOverText);
	textsInGameoverScene.push_back(highScoreText);

	menuTitleText->setPos(Vector2f(window.getWidth() / 2, MENU_TITLE_TEXT_Y) - Vector2f(menuTitleText->getWidth() / 2, 0));
	gameOverText->setPos(Vector2f(window.getWidth() / 2, GAMEOVER_TEXT_Y) - Vector2f(gameOverText->getWidth() / 2, 0));
	highScoreText->setPos(Vector2f(window.getWidth() / 2, HIGHSCORE_TEXT_Y) - Vector2f(highScoreText->getWidth() / 2, 0));

	//Set button
	Button* settingsButton = new Button(settingBtnPosition, buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, settingsText, animationUIs, std::bind(&Game::settingsButtonFunction, this));
	Button* menuButton = new Button(Vector2f(0, 0), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, menuText, animationUIs, std::bind(&Game::menuButtonFunction, this));
	Button* resumeButton = new Button(Vector2f(0, 0), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, resumeText, animationUIs, std::bind(&Game::resumeButtonFunction, this));
	Button* playButton = new Button(Vector2f(0, 0), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, playText, animationUIs, std::bind(&Game::startGameButtonFunction, this));
	Button* quitButton = new Button(Vector2f(0, 0), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, quitText, animationUIs, std::bind(&Game::quitGameButtonFunction, this));
	Button* shopButton = new Button(shopBtnPosition, buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, shopText, animationUIs, std::bind(&Game::shopButtonFunction, this));
	Button* LevelUpFireBallButton = new Button(Vector2f(0 ,0), longButtonNormalAnimation, longButtonHoverAnimation, longButtonActiveAnimation, levelUpFireBallText, animationUIs, std::bind(&Game::levelUpFireBall, this));
	Button* LevelUpSnowBallButton = new Button(Vector2f(0, 0), longButtonNormalAnimation, longButtonHoverAnimation, longButtonActiveAnimation, levelUpSnowBallText, animationUIs, std::bind(&Game::levelUpSnowBall, this));
	Button* LevelUpWindStormButton = new Button(Vector2f(0, 0), longButtonNormalAnimation, longButtonHoverAnimation, longButtonActiveAnimation, levelUpWindStormText, animationUIs, std::bind(&Game::levelUpWindStorm, this));
	Button* restartButton = new Button(Vector2f(0, 0), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, restartText, animationUIs, std::bind(&Game::restartGameButtonFunction ,this));
	Button* gameOverMenuButton = new Button(Vector2f(0, 0), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, menuText, animationUIs, std::bind(&Game::menuButtonFunction, this));
	Button* musicButton = new Button(Vector2f(0, 0), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, musicOnOffText, animationUIs, std::bind(&Game::toggleMusicButtonFunction, this));
	Button* musicSettingButton = new Button(Vector2f(0, 0), buttonNormalAnimation, buttonHoverAnimation, buttonActiveAnimation, musicOnOffText, animationUIs, std::bind(&Game::toggleMusicButtonFunction, this));


	//Set of buttons
	buttonsInMenu.push_back(playButton);
	buttonsInMenu.push_back(musicButton);
	buttonsInMenu.push_back(quitButton);


	buttonsInSettingModal.push_back(resumeButton);
	buttonsInSettingModal.push_back(musicSettingButton);
	buttonsInSettingModal.push_back(menuButton);

	buttonsInShopModal.push_back(LevelUpFireBallButton);
	buttonsInShopModal.push_back(LevelUpSnowBallButton);
	buttonsInShopModal.push_back(LevelUpWindStormButton);

	buttonsInGame.push_back(settingsButton);
	buttonsInGame.push_back(shopButton);
	buttonsInGame.push_back(menuButton);
	buttonsInGame.push_back(resumeButton);
	buttonsInGame.push_back(LevelUpFireBallButton);
	buttonsInGame.push_back(LevelUpSnowBallButton);
	buttonsInGame.push_back(LevelUpWindStormButton);
	buttonsInGame.push_back(musicSettingButton);
	
	buttonsInGameoverScene.push_back(gameOverMenuButton);
	buttonsInGameoverScene.push_back(restartButton);

	gameOverMenuButton->setPos(Vector2f(window.getWidth() / 2, MENU_BUTTON_Y) - Vector2f(gameOverMenuButton->getWidth() / 2, 0));
	restartButton->setPos(Vector2f(window.getWidth() / 2, RESTART_BUTTON_Y) - Vector2f(restartButton->getWidth() / 2, 0));

	//Set Bar
	float hpp = 100;
	Bar* slimeHpBar = new Bar(Vector2f(0, 0), outerBarAnimation, innerHpBarAnimation, slimeHp, animationUIs);
	Bar* golemHpBar = new Bar(Vector2f(0, 0), outerBarAnimation, innerHpBarAnimation, golemHp, animationUIs);
	Bar* mikuHpBar = new Bar(Vector2f(0, 0), outerBarAnimation, innerHpBarAnimation, mikuHp, animationUIs);
	Bar* fireBallCDBar = new Bar(Vector2f(0, 0), outerBarAnimation, innerCoolDownBarAnimation, fireBallCoolDown, animationUIs);
	Bar* snowBallCDBar = new Bar(Vector2f(0, 0), outerBarAnimation, innerCoolDownBarAnimation, snowBallCoolDown, animationUIs);
	Bar* windStormCDBar = new Bar(Vector2f(0, 0), outerBarAnimation, innerCoolDownBarAnimation, windStormCoolDown, animationUIs);

	//buttonsInMenu.push_back(playButton);
	//buttonsInMenu.push_back(quitButton);

	//Set modal
	Modal* menuModal = new Modal(Vector2f(0, 0), modalAnimation, buttonsInMenu, settingsModalText, animationUIs);
	Modal* settingModal = new Modal(Vector2f(0, 0), modalAnimation, buttonsInSettingModal, settingsModalText, animationUIs);
	Modal* shopModal = new Modal(Vector2f(0, 0), modalAnimation, buttonsInShopModal, settingsModalText, animationUIs);

	modalsInGame.push_back(settingModal);
	modalsInGame.push_back(shopModal);
	modalsInMenu.push_back(menuModal);


	//Set Skill Holders
	SkillHolder* fireBallSkillHolder = new SkillHolder(fireBallSkillHolderPosition, fireBallCDBar, fireBallSkillHolderAnimation, fireBallSkillHolderCoolDownAnimation, indicatorAnimation, animationUIs, bars);
	SkillHolder* snowBallSkillHolder = new SkillHolder(snowBallSkillHolderPosition, snowBallCDBar, snowBallSkillHolderAnimation, snowBallSkillHolderCoolDownAnimation, indicatorAnimation, animationUIs, bars);
	SkillHolder* windStormSkillHolder = new SkillHolder(windStormSkillHolderPosition, windStormCDBar, windStormSkillHolderAnimation, windStormSkillHolderCoolDownAnimation, indicatorAnimation, animationUIs, bars);

	//Set projectiles
	Projectile* fireball = new Projectile("fireBall", Vector2f(0, 0), Vector2f(1, 0), fireBallSpeed, fireBallStr, fireBallCoolDown, fireBallAnimation);
	Projectile* snowBall = new Projectile("snowBall", Vector2f(0, 0), Vector2f(1, 0), snowBallSpeed, snowBallStr, snowBallCoolDown, snowBallAnimation);
	Projectile* windStorm = new Projectile("windStorm", Vector2f(0, 0), Vector2f(1, 0), windStormSpeed, windStormStr, windStormCoolDown, windStormAnimation);

	//Set enemies
	Enemy* slime = new Enemy("slime", Vector2f(0, 0), slimeAnimation, Vector2f(-1, 0), slimeSpeed, slimeHp, slimeCoinDrop, slimeHpBar, bars, animationEnemies);
	Enemy* golem = new Enemy("golem", Vector2f(0, 0), golemMoveAnimation, Vector2f(-1, 0), golemSpeed, golemHp, golemCoinDrop, golemHpBar, bars, animationEnemies);
	Enemy* miku = new Enemy("miku", Vector2f(0, 0), mikuMoveAnimation, Vector2f(-1, 0), mikuSpeed, mikuHp, mikuCoinDrop, mikuHpBar, bars, animationEnemies);
	Enemy* fireSlime = new Enemy("fireSlime", Vector2f(0, 0), fireSlimeAnimation, Vector2f(-1, 0), slimeSpeed, slimeHp, slimeCoinDrop, slimeHpBar, bars, animationEnemies);
	Enemy* iceSlime = new Enemy("iceSlime", Vector2f(0, 0), iceSlimeAnimation, Vector2f(-1, 0), slimeSpeed, slimeHp, slimeCoinDrop, slimeHpBar, bars, animationEnemies);

	enemyPrefabs.push_back(slime);
	enemyPrefabs.push_back(golem);
	enemyPrefabs.push_back(miku);
	enemyPrefabs.push_back(fireSlime);
	enemyPrefabs.push_back(iceSlime);

	//Set positions
	settingModal->setPos(Vector2f(window.getWidth() / 2, window.getHeight() / 2) - Vector2f(settingModal->getWidth() / 2, settingModal->getHeight() / 2));
	shopModal->setPos(Vector2f(window.getWidth() / 2, window.getHeight() / 2) - Vector2f(shopModal->getWidth() / 2, shopModal->getHeight() / 2));
	menuModal->setPos(Vector2f(window.getWidth() / 2, MENU_MODAL_Y) - Vector2f(menuModal->getWidth() / 2, 0));

	//Prefab waves

		//Repeating wave
	Wave wavePrefab1(10, 0, 0, 10, 10);
	Wave wavePrefab2(0, 20, 5, 0, 0);
	Wave wavePrefab3(4, 4, 4, 4, 4);
	Wave wavePrefab4(15, 0, 10, 1, 0);
	Wave wavePrefab5(0, 0, 0, 15, 15);

	wavePrefabs.push_back(wavePrefab1);
	wavePrefabs.push_back(wavePrefab2);
	wavePrefabs.push_back(wavePrefab3);
	wavePrefabs.push_back(wavePrefab4);
	wavePrefabs.push_back(wavePrefab5);

	//Push all animations for easier deconstruction
	projectilePrefabs.push_back(fireball);
	projectilePrefabs.push_back(snowBall);
	projectilePrefabs.push_back(windStorm);

	//Set player
	player = new Player(Vector2f(0, PLAYER_DEFAULT_POS_Y), nullptr, projectilePrefabs);
	playerIdleAnimation->setPos(player->getPos());
	player->setAnimation(playerIdleAnimation);

	buttons.push_back(settingsButton);
	buttons.push_back(menuButton);
	buttons.push_back(resumeButton);
	buttons.push_back(playButton);
	buttons.push_back(quitButton);
	buttons.push_back(shopButton);
	buttons.push_back(LevelUpFireBallButton);
	buttons.push_back(LevelUpSnowBallButton);
	buttons.push_back(LevelUpWindStormButton);
	buttons.push_back(musicButton);
	buttons.push_back(musicSettingButton);

	modals.push_back(settingModal);
	modals.push_back(shopModal);
	modals.push_back(menuModal);

	skillHolders.push_back(fireBallSkillHolder);
	skillHolders.push_back(snowBallSkillHolder);
	skillHolders.push_back(windStormSkillHolder);

	barPrefabs.push_back(slimeHpBar);

	for (auto& skillHolder : skillHolders) {
		skillHolder->getBar()->deplete();
	}

	spawnManager.setWavePrefabs(wavePrefabs);
	spawnManager.setActiveEnemies(&enemies);
	audioManager.setSounds(&musicPrefabs, &SFXPrefabs);

	loadHighScore(gameHighScore);
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
				if (!*pjIt) {
					std::cerr << "Error: null projectile in logic loop!" << std::endl;
					continue;
				}

				if ((*pjIt)->getName() == "fireBall") {
					//std::cout << "Collide with enemy!" << std::endl;

					if (runCoolDown((*pjIt)->getCoolDownDamageTick(), (*pjIt)->getLastTick())) {
						(*pjIt)->setLastTick(currentTime);

						if ((*eneIt)->getName() == "iceSlime") {
							(*eneIt)->setHp((*eneIt)->getHp() - (*pjIt)->getStr() * 2);
							(*eneIt)->getBar()->update((*pjIt)->getStr() * 2);
						}
						else if ((*eneIt)->getName() == "fireSlime") {
							//do nothing
						}
						else {
							(*eneIt)->setHp((*eneIt)->getHp() - (*pjIt)->getStr());
							(*eneIt)->getBar()->update((*pjIt)->getStr());
						}
						
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
						if ((*eneIt)->getName() == "fireSlime") {
							(*eneIt)->setHp((*eneIt)->getHp() - (*pjIt)->getStr() * 2);
							(*eneIt)->getBar()->update((*pjIt)->getStr() * 2);
							(*eneIt)->setSpeed((*eneIt)->getSpeed() / 2);
						}
						else if ((*eneIt)->getName() == "iceSlime") {
							// do nothing
						}
						else {
							(*eneIt)->setHp((*eneIt)->getHp() - (*pjIt)->getStr());
							(*eneIt)->getBar()->update((*pjIt)->getStr());
							(*eneIt)->setSpeed((*eneIt)->getSpeed() / 2);
						}
						

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
					if ((*eneIt)->getName() != "golem") {
						circularMotion((*eneIt), (*pjIt)->getPos(), 0.5);
					}
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

void Game::audio() {
	audioManager.start();
}

void Game::audioUpdate() {
	if (isGamePause && isMusicOn) {
		audioManager.setMusicVolume(16);
	}
	else if(isMusicOn){
		audioManager.setMusicVolume(72);
	}

	if (isMenuOpen) {
		if (!hasMenuMusicPlay) {
			Mix_PlayMusic(musicPrefabs[MENU_MUSIC], -1);
			hasMenuMusicPlay = true;
			hasGameoverMusicPlay = false;
			hasGameplayMusicPlay = false;
		}
	}
	else if (isGameStart && !isGameOver) {
		if (!hasGameplayMusicPlay) {
			Mix_PlayMusic(musicPrefabs[GAMEPLAY_MUSIC], -1);
			hasGameplayMusicPlay = true;
			hasMenuMusicPlay = false;
			hasGameoverMusicPlay = false;

		}
	}
	else if (isGameOver) {
		if (!hasGameoverMusicPlay) {
			Mix_PlayMusic(musicPrefabs[GAMEOVER_MUSIC], -1);
			hasGameoverMusicPlay = true;
			hasGameplayMusicPlay = false;
			hasMenuMusicPlay = false;
		}
	}

}

void Game::backgroundGraphic() {

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
		if ((inputManager.keyStates[SDLK_SPACE].isHold || inputManager.keyStates[SDLK_SPACE].isStart) && (!isGamePause) && (!isGameOver) ) {
			player->shootProjectile(projectiles, animationProjectiles);
			player->getCurrentProjectile()->setLastShot(currentTime - timePause);
			if (player->getCurrentProjectile()->getName() == "fireBall") {
				audioManager.playFireBallSFX();
				skillHolders[FIREBALL_SKILLHOLDER]->getBar()->reset();
			}
			else if (player->getCurrentProjectile()->getName() == "snowBall") {
				audioManager.playSnowBallSFX();
				skillHolders[SNOWBALL_SKILLHOLDER]->getBar()->reset();
			}
			else if (player->getCurrentProjectile()->getName() == "windStorm") {
				audioManager.playWindStormSFX();
				skillHolders[WINDSTORM_SKILLHOLDER]->getBar()->reset();
			}
		}
	}

	p_movement.normalize();
}

void Game::renderGame(Vector2f& p_movement) {
	updateGameHp();
	updateHighScore();
	if (!isGameOver) {
		for (auto& btn : buttonsInGame) {
			btn->handleInput(inputManager);
			btn->update();
		}
		updateCoin();
		player->changeProjectile(inputManager);

		if (!isGamePause) {
			UILogic();
			if (runCoolDown(spawnManager.getCooldown(), spawnManager.getLastTime())) {
				if (spawnManager.getIsWaveEnd()) {
					int randomValue = random(0, 4);
					spawnManager.setEnemy(wavePrefabs[randomValue]);
				}
				spawnManager.spawnEnemy(enemies, enemyPrefabs);
				spawnManager.setLastTime(currentTime - timePause);
			}

			setPlayerInBound();
			
			logic();

			//Player movement
			player->move(p_movement * playerSpeed);
			animationPrefabs[PLAYER_IDLE_ANIMATION]->setPos(player->getPos());

			//Fireball movement
			for (auto& prj : projectiles) {
				prj->update(player->getPos(), currentTime);
			}

			//Enemies movement
			for (auto& ene : enemies) {
				ene->update(currentTime);
			}
		}
	}

	
	//Destroy out of bound projectiles
	destroyOutOfBound();

	//Draw the screen

		//Render Grass
	for (auto& grass : gameObjectGrass) {
		window.renderAnimation(grass.getAnimation());
	}

	//Render Background
	window.renderAnimation(animationPrefabs[BACKGROUND_ANIMATION]);

	//Render Player
	window.renderAnimation(animationPrefabs[PLAYER_IDLE_ANIMATION]);
	animationPrefabs[PLAYER_IDLE_ANIMATION]->update(currentTime);

	//Render FireBall
	for (auto& fb : projectiles) {
		window.renderAnimation(fb->getAnimation());
	}

	//Render Enemies
	for (auto& sl : enemies) {
		window.renderAnimation(sl->getAnimation());
		window.renderUI(sl->getBar());
	}

	window.renderText(textsInGame[COIN_TEXT]);
	window.renderText(textsInGame[GAMEHP_TEXT]);
	window.renderText(textsInGame[GAMESCORE_TEXT]);

	for (auto& skillHolder : skillHolders) {
		window.renderUI(skillHolder);
	}



	for (auto& modal : modalsInGame) {
		if (modal->getIsOpen()) {
			window.renderUI(modal);
		}
	}

	for (auto& btn : buttonsInGame) {
		if (btn->getVisible()) {
			window.renderUI(btn);
		}
	}

	if (isGameOver) {
		
		for (auto& btn : buttonsInGameoverScene) {
			btn->handleInput(inputManager);
			btn->update();
			btn->setEnable(true);
			btn->setVisible(true);

		}
		for (auto& btn : buttonsInGameoverScene) {
			if (btn->getVisible()) {
				window.renderUI(btn);
			}
		}

		window.renderText(textsInGameoverScene[GAMEOVER_TEXT]);
		if (isHighScoreUpdated) {
			window.renderText(textsInGameoverScene[HIGHSCORE_TEXT]);
		}
	}

	checkIsGameOver();
	debug();
}

void Game::renderMenu() {
	window.renderAnimation(animationPrefabs[MENU_BACKGROUND_ANIMATION]);
	for (auto& txt : textsInMenu) {
		window.renderText(txt);
	}

	for (auto& btn : buttonsInMenu) {
		btn->handleInput(inputManager);
		btn->update();
		btn->setVisible(true);
	}

	for (auto& modal : modalsInMenu) {
		window.renderUI(modal);
	}

	for (auto& btn : buttonsInMenu) {
		if (btn->getVisible()) {		
			window.renderUI(btn);
		}
	}
}
//Main game loop
void Game::update() {
	
	backgroundGraphic();

	//Set flag for the game loop
	bool isGameRunning = true;

	SDL_Event e;

	//For program's frame rate
	Uint32 lastTime = SDL_GetTicks();
	float accumulator = 0.0f;
	const float timeStep = 16.67f;

	//References
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
		//Clear the screen
		window.clear();

		SDL_SetRenderDrawColor(window.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(window.getRenderer());
		inputManager.update();
		audioUpdate();

		if (isMenuOpen) {
			renderMenu();
		}
		else {
			renderGame(movement);
		}

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
	resourceManager.clear();

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

	for (Text* text : textsInGame) {
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
			if (((*prjIt)->getPos().x >= BOUND_X || (*prjIt)->getPos().y >= BOUND_Y)) {
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
			if (((*prjIt)->getPos().x >= WINDSTORM_BOUND_X || (*prjIt)->getPos().y >= BOUND_Y)) {
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
		if ((*eneIt)->getPos().x < ENEMY_BOUND_X || (*eneIt)->getPos().y < ENEMY_BOUND_Y) {
			auto animIt = std::find(animationEnemies.begin(), animationEnemies.end(), (*eneIt)->getAnimation());
			if (animIt != animationEnemies.end()) {
				delete* animIt;
				animationEnemies.erase(animIt);
			}
			delete *eneIt;
			eneIt = enemies.erase(eneIt);
			std::cout << "Enemy destroyed!" << std::endl;
			gameHp--;
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
	gameScore += (*eneIt)->getCoinDrop();
	
	if (eneIt == enemies.end()) {
		std::cout << "Didn't find an enemy to destroy!" << std::endl;
		return;
	}

	delete p_enemy;

	p_eneIt = enemies.erase(eneIt);
}

void Game::settingsButtonFunction() {
	std::cout << "Pressed settingButton!" << std::endl;
	openCloseSettingModal();
	if (isGamePause) {
		buttonsInGame[SHOP_BUTTON]->setEnable(false);
	}
	else {
		buttonsInGame[SHOP_BUTTON]->setEnable(true);
	}

	Mix_PlayChannel(-1, SFXPrefabs[BUTTON_SFX], 0);
}

void Game::levelUpFireBall() {
	if (player->getCoin() >= projectilePrefabs[0]->getUpgradeCoin()) {
		projectilePrefabs[0]->levelUp();
		skillHolders[FIREBALL_SKILLHOLDER]->getBar()->setNewCoolDown(projectilePrefabs[0]->getCoolDown());
		player->setCoin(player->getCoin() - projectilePrefabs[0]->getUpgradeCoin());
		projectilePrefabs[0]->levelUpUpgradeCoin();
		Mix_PlayChannel(-1, SFXPrefabs[LEVELUP_SFX], 0);
	}
}

void Game::levelUpSnowBall() {
	if (player->getCoin() >= projectilePrefabs[1]->getUpgradeCoin()) {
		projectilePrefabs[1]->levelUp();
		skillHolders[SNOWBALL_SKILLHOLDER]->getBar()->setNewCoolDown(projectilePrefabs[1]->getCoolDown());
		player->setCoin(player->getCoin() - projectilePrefabs[1]->getUpgradeCoin());
		projectilePrefabs[1]->levelUpUpgradeCoin();
		Mix_PlayChannel(-1, SFXPrefabs[LEVELUP_SFX], 0);
	}
}

void Game::levelUpWindStorm() {
	if (player->getCoin() >= projectilePrefabs[2]->getUpgradeCoin()) {
		projectilePrefabs[2]->levelUp();
		skillHolders[WINDSTORM_SKILLHOLDER]->getBar()->setNewCoolDown(projectilePrefabs[2]->getCoolDown());
		player->setCoin(player->getCoin() - projectilePrefabs[2]->getUpgradeCoin());
		projectilePrefabs[2]->levelUpUpgradeCoin();
		Mix_PlayChannel(-1, SFXPrefabs[LEVELUP_SFX], 0);
	}
}

void Game::pause() {
	if (isGamePause) {
		isGamePause = false;
		Uint32 resumeTime = SDL_GetTicks();
		timePause += (resumeTime - startPause); // Accumulate pause duration
	}
	else {
		isGamePause = true;
		startPause = SDL_GetTicks();
	}
}

void Game::shopButtonFunction() {
	if (modals[SHOP_MODAL]->getIsOpen()) {
		modals[SHOP_MODAL]->close();
	}
	else {
		modals[SHOP_MODAL]->open();
	}
	pause();

	if (isGamePause) {
		buttonsInGame[SETTING_BUTTON]->setEnable(false);
	}
	else {
		buttonsInGame[SETTING_BUTTON]->setEnable(true);
	}
	Mix_PlayChannel(-1, SFXPrefabs[BUTTON_SFX], 0);
}

void Game::startGameButtonFunction() {
	std::cout << "Play button clicked!" << std::endl;
	isMenuOpen = false;
	isGameStart = true;
	restartGameButtonFunction();
	if (modals[SETTING_MODAL]->getIsOpen()) {
		modals[SETTING_MODAL]->close();
		pause();
	}
	
	Mix_PlayChannel(-1, SFXPrefabs[BUTTON_SFX], 0);
}

void Game::restartGameButtonFunction() {
	std::cout << "Restart Button!" << std::endl;
	isHighScoreUpdated = false;
	isGameOver = false;
	gameHp = 5;
	gameScore = 0;
	numberOfWave = 1;
	player->setPos(Vector2f(0, PLAYER_DEFAULT_POS_Y));
	for (auto& ene : enemies) {
		delete ene;
	} 


	for (auto prjIt = projectiles.begin(); prjIt != projectiles.end(); ) {
		delete* prjIt;
		prjIt = projectiles.erase(prjIt);
	}

	projectiles.clear();  


	enemies.clear();
	player->setCoin(0);
	spawnManager.restart();
}

void Game::quitGameButtonFunction() {
	SDL_Event e;
	e.type = SDL_QUIT;
	Mix_PlayChannel(-1, SFXPrefabs[BUTTON_SFX], 0);
	SDL_PushEvent(&e);
}

void Game::menuButtonFunction() {
	std::cout << "Menu Button!" << std::endl;
	isMenuOpen = true;
	isGameStart = false;


	openCloseSettingModal();

	if (isGamePause) {
		buttonsInGame[SHOP_BUTTON]->setEnable(false);
	}
	else {
		buttonsInGame[SHOP_BUTTON]->setEnable(true);
	}

	Mix_PlayChannel(-1, SFXPrefabs[BUTTON_SFX], 0);
}

void Game::resumeButtonFunction() {
	if (modals[SETTING_MODAL]->getIsOpen()) {
		modals[SETTING_MODAL]->close();
	}
	else {
		modals[SETTING_MODAL]->open();
	}
	pause();

	if (isGamePause) {
		buttonsInGame[SHOP_BUTTON]->setEnable(false);
	}
	else {
		buttonsInGame[SHOP_BUTTON]->setEnable(true);
	}
	Mix_PlayChannel(-1, SFXPrefabs[BUTTON_SFX], 0);
}

void Game::openCloseSettingModal() {
	if (modals[SETTING_MODAL]->getIsOpen()) {
		modals[SETTING_MODAL]->close();
	}
	else {
		modals[SETTING_MODAL]->open();
	}
	pause();
	std::cout << isGamePause << std::endl;
}

void Game::checkIsGameOver() {
	if (gameHp <= 0) {
		isGameOver = true;
		//std::cout << "Game Over!" << std::endl;
	}
	else {
		isGameOver = false;
	}
}

void Game::setPlayerInBound() {
	if (player->getPos().y >= PLAYER_BOUND_Y_NEG) {
		player->setPos(Vector2f(player->getPos().x, PLAYER_BOUND_Y_NEG));
	}
	else if (player->getPos().y <= PLAYER_BOUND_Y_POS) {
		player->setPos(Vector2f(player->getPos().x, PLAYER_BOUND_Y_POS));
	}
}

bool Game::runCoolDown(Uint32 p_coolDown, Uint32 p_lastTime) {
	Uint32 timer = currentTime - p_lastTime - timePause; // Use accumulated pause time
	return timer >= p_coolDown;
}

void Game::updateCoin() {
	textsInGame[COIN_TEXT]->setText("Coin: " + std::to_string(player->getCoin()));
	textsInGame[LEVELUP_FIREBALL_TEXT]->setText("Level Up Fireball! Coin to upgrade: " + std::to_string(projectilePrefabs[0]->getUpgradeCoin()));
	textsInGame[LEVELUP_SNOWBALL_TEXT]->setText("Level Up Snowball! Coin to upgrade: " + std::to_string(projectilePrefabs[1]->getUpgradeCoin()));
	textsInGame[LEVELUP_WINDSTORM_TEXT]->setText("Level Up Windstorm! Coin to upgrade: " + std::to_string(projectilePrefabs[2]->getUpgradeCoin()));

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

	if (player->getCurrentProjectile()->getName() == "fireBall") {
		for (auto& sh : skillHolders) {
			sh->setIsActive(false);
		}
		skillHolders[FIREBALL_SKILLHOLDER]->setIsActive(true);
	}

	if (player->getCurrentProjectile()->getName() == "snowBall") {
		for (auto& sh : skillHolders) {
			sh->setIsActive(false);
		}
		skillHolders[SNOWBALL_SKILLHOLDER]->setIsActive(true);
	}

	if (player->getCurrentProjectile()->getName() == "windStorm") {
		for (auto& sh : skillHolders) {
			sh->setIsActive(false);
		}
		skillHolders[WINDSTORM_SKILLHOLDER]->setIsActive(true);
	}
	updateGameScore();
}

void Game::updateGameHp() {
	if (gameHp >= 0) {
		textsInGame[GAMEHP_TEXT]->setText("HOME HP: " + std::to_string(gameHp));
	}
}

void Game::updateGameScore() {
	textsInGame[GAMESCORE_TEXT]->setText("Score: " + std::to_string(gameScore));
}

void Game::loadHighScore(int& p_highScore) {
	std::ifstream in("highscore.txt");
	if (in >> p_highScore) {
		std::cout << "Loaded high score: " << p_highScore << std::endl;
	}
	else {
		p_highScore = 0;
	}
	in.close();
}

void Game::saveHighScore() {
	std::ofstream out("highscore.txt");
	out << gameHighScore;
	out.close();
}

void Game::updateHighScore() {
	if (gameHighScore < gameScore) {
		isHighScoreUpdated = true;
		gameHighScore = gameScore;
		saveHighScore();
	}
	textsInGameoverScene[HIGHSCORE_TEXT]->setText("New High Score: " + std::to_string(gameHighScore));
}

void Game::toggleMusicButtonFunction() {
	std::cout << "Music button pressed!" << std::endl;
	if (isMusicOn) {
		audioManager.setMusicVolume(0);
		audioManager.toggleSFX();
		isMusicOn = false;
	}
	else {
		audioManager.setMusicVolume(SOUND_VOLUME);
		audioManager.toggleSFX();
		isMusicOn = true;
	}
}

