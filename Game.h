#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_mixer.h>
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
#include "AudioManager.h"

class Game {
public:
	Game();
	void start();
	void update();
	void pause();
	void debug();
	void graphic();
	void audio();
	void audioUpdate();
	void logic();
	void renderGame(Vector2f& p_movement);
	void renderMenu();
	void UILogic();
	void input(SDL_Event &e, Vector2f& p_movement);
	void checkIsGameOver();
	void clean();
	bool runCoolDown(Uint32 p_coolDown, Uint32 p_lastTime);

	//Destroy out of bound Projectiles
	void destroyOutOfBound();
	void destroyEnemy(Enemy* p_enemy, std::vector<Enemy*>::iterator& p_eneIt);
	void destroyProjectile(Projectile* p_projectile, std::vector<Projectile*>::iterator& p_prjIt);
	void setPlayerInBound();

	void updateCoin();
	//Button functions
	void settingsButtonFunction();
	void shopButtonFunction();
	void levelUpFireBall();
	void levelUpSnowBall();
	void levelUpWindStorm();
	void restartGameButtonFunction();
	void startGameButtonFunction();
	void quitGameButtonFunction();
	void menuButtonFunction();

	bool isGamePause = false;
	bool isGameOver = false;
	bool isGameStart = true;
	bool isMenuOpen = true;

	bool hasMenuMusicPlay = false;
	bool hasGameplayMusicPlay = false;
	bool hasGameoverMusicPlay = false;
private:
	RenderWindow window;
	ResourceManager resourceManager;
	InputManager inputManager;
	SpawnManager spawnManager;
	AudioManager audioManager;

	//Prefabs
	std::vector<GameObject*> gameObjectPrefabs;
	std::vector<Projectile*> projectilePrefabs;
	std::vector<Animation*> animationPrefabs;
	std::vector<Enemy*> enemyPrefabs;
	std::vector<Bar*> barPrefabs;
	std::vector<Wave> wavePrefabs;
	std::vector<Mix_Chunk*> SFXPrefabs;
	std::vector<Mix_Music*> musicPrefabs;

	//In-game
	std::vector<Projectile*> projectiles;
	std::vector<GameObject> gameObjectGrass;
	std::vector<Enemy*> enemies;
	std::vector<Text*> textsInGame;
	std::vector<Text*> textsInMenu;
	std::vector<Text*> textsInGameoverScene;
	std::vector<Button*> buttons;

	std::vector<Button*> buttonsInSettingModal;
	std::vector<Button*> buttonsInMenu;
	std::vector<Button*> buttonsInShopModal;
	std::vector<Button*> buttonsInGame; 
	std::vector<Button*> buttonsInGameoverScene;

	std::vector<Modal*> modals;
	std::vector<Modal*> modalsInMenu;
	std::vector<Modal*> modalsInGame;
	std::vector<Bar*> bars;
	std::vector<SkillHolder*> skillHolders;

	std::vector<Animation*> animationProjectiles;
	std::vector<Animation*> animationGrass;
	std::vector<Animation*> animationEnemies;
	std::vector<Animation*> animationUIs;
	std::vector<Button*> empty;

	Player* player;
	Uint32 currentTime;
	float playerSpeed = 0;

	Uint32 startPause = 0;
	Uint32 lastPause = 0;
	Uint32 timePause = 0;

	int gameHp = 1;
	int gameScore = 0;
	int numberOfWave = 1;
};
