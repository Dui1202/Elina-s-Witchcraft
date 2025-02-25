#include <SDL.h>
#include <random>
#include <iostream>
#include "Math.h"
#include "Animation.h"
#include "Enemy.h"
#include "vector"
#include "SpawnManager.h"

SpawnManager::SpawnManager(){}

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

void SpawnManager::spawnEnemy(std::vector<Enemy*>& enemies, std::vector<Animation*>& enemyAnimations, Enemy* p_enemy) {
    
    Enemy* newEnemy = new Enemy(*p_enemy);
    Animation* newEnemyAnimation = new Animation(*(newEnemy->getAnimation()));
    newEnemy->setAnimation(newEnemyAnimation);
    newEnemy->setPos(randomPos());
    SDL_Rect hb = { newEnemy->getPos().x + 10, newEnemy->getPos().y + 10, 64, 64 };
    newEnemy->setCollider(hb);
    
    enemyAnimations.push_back(newEnemyAnimation);
    enemies.push_back(newEnemy);
}

void SpawnManager::setLastTime(Uint32 p_lastTime) {
    lastTime = p_lastTime;
}

void SpawnManager::setCooldown(Uint32 p_cooldown) {
    cooldown = p_cooldown;
}

Uint32 SpawnManager::getCooldown() {
    return cooldown;
}

Uint32 SpawnManager::getLastTime() {
    return lastTime;
}