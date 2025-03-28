#include <SDL.h>
#include <random>
#include <iostream>
#include "Math.h"
#include "Animation.h"
#include "Enemy.h"
#include "vector"
#include "SpawnManager.h"
#include "Wave.h"
#include "Enums.h"

SpawnManager::SpawnManager(){
}

void SpawnManager::setActiveEnemies(std::vector<Enemy*>* p_enemies) {
    activeEnemies = p_enemies;
}

Vector2f SpawnManager::randomPos() {
    int randomValue = random(0, 4);

    return preSpawnPostions[randomValue];
}

void SpawnManager::setEnemy(Wave p_wave) {
    std::cout << "Set wave!" << std::endl;
    enemyCount.clear();
    enemyQueue.clear();

    slimeSpawnCount = p_wave.slimeSpawnCount;
    mikuSpawnCount = p_wave.mikuSpawnCount;
    golemSpawnCount = p_wave.golemSpawnCount;
    iceSlimeSpawnCount = p_wave.iceSlimeSpawnCount;
    fireSlimeSpawnCount = p_wave.fireSlimeSpawnCount;

    for (int i = 0; i < slimeSpawnCount; i++) {
        enemyQueue.push_back(SLIME);
    }
    for (int i = 0; i < golemSpawnCount; i++) {
        enemyQueue.push_back(GOLEM);
    }
    for (int i = 0; i < mikuSpawnCount; i++) {
        enemyQueue.push_back(MIKU);
    }
    for (int i = 0; i < fireSlimeSpawnCount; i++) {
        enemyQueue.push_back(FIRE_SLIME);
    }
    for (int i = 0; i < iceSlimeSpawnCount; i++) {
        enemyQueue.push_back(ICE_SLIME);
    }
    
    std::shuffle(enemyQueue.begin(), enemyQueue.end(), std::default_random_engine(SDL_GetTicks()));

    setIsWaveEnd(false);
}

void SpawnManager::spawnEnemy(std::vector<Enemy*>& enemies, std::vector<Enemy*>& enemyPrefabs) {
    if (enemyQueue.empty()) {
        checkIsWaveEnd();
        return;
    }
    
    int nextEnemy = enemyQueue.back();
    enemyQueue.pop_back();

    Enemy* newEnemy = new Enemy(enemyPrefabs[nextEnemy]);
    newEnemy->setPos(randomPos());

    enemies.push_back(newEnemy);
    checkIsWaveEnd();
}

void SpawnManager::setWavePrefabs(std::vector<Wave>& p_prefabs) {
    wavePrefabs = p_prefabs;
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

void SpawnManager::checkIsWaveEnd() {
    if (!activeEnemies->empty()) {
        return;
    }
    setIsWaveEnd(true);
    std::cout << "Wave ended!" << std::endl;
}

bool SpawnManager::getIsWaveEnd() {
    return isWaveEnd;
}

void SpawnManager::setIsWaveEnd(bool p_bool) {
    isWaveEnd = p_bool;
}

void SpawnManager::restart() {
    setIsWaveEnd(true);
}