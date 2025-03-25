#pragma once
#include <SDL.h>
#include "Math.h"
#include "Animation.h"
#include "Enemy.h"
#include "vector"
#include "Wave.h"
#include "Enums.h"


class SpawnManager {
public:
	SpawnManager();
	void setWavePrefabs(std::vector<Wave>& p_prefabs);
	void setActiveEnemies(std::vector<Enemy*>* p_enemies);
	Vector2f randomPos();
	void setEnemy(Wave p_wave);
	void spawnEnemy(std::vector<Enemy*>& enemies, std::vector<Enemy*>& enemyPrefabs);
	void setLastTime(Uint32 p_lastTime);
	void setCooldown(Uint32 p_cooldown);
	Uint32 getCooldown();
	Uint32 getLastTime();
	void checkIsWaveEnd();
	bool getIsWaveEnd();
	void setIsWaveEnd(bool p_bool);
private:
	bool isWaveEnd = true;
	int slimeSpawnCount = 0;
	int golemSpawnCount = 0;
	int iceSlimeSpawnCount = 0;
	int fireSlimeSpawnCount = 0;
	int mikuSpawnCount = 0;
	std::vector<int> enemyCount;
	Uint32 cooldown = 1500;
	Uint32 lastTime = 0;
	std::vector<Vector2f> preSpawnPostions = { Vector2f(1300,130), Vector2f(1300,250), Vector2f(1300,370), Vector2f(1300,490), Vector2f(1300,610) };
	std::vector<Wave> wavePrefabs;
	std::vector<Enemy*>* activeEnemies;
	std::vector<int> enemyQueue;
};