#pragma once
#include <SDL.h>
#include "Math.h"
#include "Animation.h"
#include "Enemy.h"
#include "vector"


class SpawnManager {
public:
	SpawnManager();
	Vector2f randomPos();
	void spawnEnemy(std::vector<Enemy*>& enemies, std::vector<Animation*>& enemyAnimations, Enemy* p_enemy);
	void setLastTime(Uint32 p_lastTime);
	void setCooldown(Uint32 p_cooldown);
	Uint32 getCooldown();
	Uint32 getLastTime();
private:
	Uint32 cooldown = 1000;
	Uint32 lastTime = 0;
	std::vector<Vector2f> preSpawnPostions = { Vector2f(1300,130), Vector2f(1300,250), Vector2f(1300,370), Vector2f(1300,490), Vector2f(1300,610) };
};