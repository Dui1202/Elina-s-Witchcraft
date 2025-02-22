#pragma once
#include <SDL.h>
#include "Math.h"
#include "Animation.h"
#include "Enemy.h"
#include "vector"


class SpawnManager {
public:
	SpawnManager(Enemy* p_enemy);
	Vector2f randomPos();
	void spawnEnemy();

private:
	Enemy* enemy;
	std::vector<Vector2f> preSpawnPostions = { Vector2f(1300,180), Vector2f(1300,300), Vector2f(1300,420), Vector2f(1300,540), Vector2f(1300,660) };
};