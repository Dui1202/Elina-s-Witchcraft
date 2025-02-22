#include <SDL.h>
#include <random>
#include <iostream>
#include "Math.h"
#include "Animation.h"
#include "Enemy.h"
#include "vector"
#include "SpawnManager.h"

SpawnManager::SpawnManager(Enemy* p_enemy)
	:enemy(p_enemy){}

Vector2f SpawnManager::randomPos() {
    // Define range
    int min = 0;
    int max = 4;

    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);

    // Generate random number in the range [min, max]
    int randomValue = distrib(gen);

    return preSpawnPostions[randomValue];
}

void SpawnManager::spawnEnemy() {
    Enemy* newEnenmy = new Enemy(*enemy);
    newEnenmy->setPos(randomPos());
}