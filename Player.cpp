#include <iostream>
#include <vector>
#include "GameObject.h"
#include "SDL.h"
#include "Math.h"
#include "Player.h"
#include "ProjectilesManager.h"
#include "InputManager.h"

Player::Player()
	: GameObject(Vector2f(0,0), nullptr){}

Player::Player(Vector2f p_pos, Animation* p_animation, std::vector<Projectile*> &p_projectilePrefabs)
	: GameObject(p_pos, p_animation), projectilePrefabs(p_projectilePrefabs){
	currentProjectile = projectilePrefabs[0];
}

void Player::shootProjectile(std::vector<Projectile*>& projectilesVector, std::vector<Animation*>& animationProjectiles) {
	//std::cout << "Shoot "<< currentProjectile->getName() <<"!" << std::endl;
	
	Animation* newProjectileAnimation = new Animation(*(currentProjectile->getAnimation()));
	Projectile* newProjectile = new Projectile(currentProjectile->getName(), currentProjectile->getPos(), currentProjectile->getDirection(), currentProjectile->getSpeed(), currentProjectile->getStr(), currentProjectile->getCoolDown(), newProjectileAnimation);
	newProjectile->setPos(getPos());

	projectilesVector.push_back(newProjectile);
	animationProjectiles.push_back(newProjectileAnimation);
}

void Player::changeProjectile(InputManager& p_IM) {
	if (p_IM.keyStates[SDLK_j].isHold) {
		currentProjectile = projectilePrefabs[0];
	}
	else if (p_IM.keyStates[SDLK_k].isHold) {
		currentProjectile = projectilePrefabs[1];
	}
	else if (p_IM.keyStates[SDLK_l].isHold) {
		currentProjectile = projectilePrefabs[2];
	}
}

Projectile* Player::getCurrentProjectile() {
	return currentProjectile;
}

int Player::getCoin() {
	return coin;
}

void Player::setCoin(int p_coin) {
	coin = p_coin;
}

Projectile* Player::getFireBallPrefab() {
	return projectilePrefabs[0];
}

Projectile* Player::getSnowBallPrefab() {
	return projectilePrefabs[1];
}

Projectile* Player::getWindStormPrefab() {
	return projectilePrefabs[2];
}