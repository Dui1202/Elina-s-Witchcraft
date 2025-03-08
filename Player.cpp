#include <iostream>
#include <vector>
#include "GameObject.h"
#include "SDL.h"
#include "Math.h"
#include "Player.h"
#include "ProjectilesManager.h"

Player::Player()
	: GameObject(Vector2f(0,0), nullptr){}

Player::Player(Vector2f p_pos, Animation* p_animation, std::vector<Projectile*> &p_projectilePrefabs)
	: GameObject(p_pos, p_animation), projectilePrefabs(p_projectilePrefabs){
	currentProjectile = projectilePrefabs[0];
}

void Player::shootProjectile(std::vector<Projectile*>& projectilesVector, std::vector<Animation*>& animationProjectiles) {
	std::cout << "Shoot "<< currentProjectile->getName() <<"!" << std::endl;
	
	Animation* newProjectileAnimation = new Animation(*(currentProjectile->getAnimation()));
	Projectile* newProjectile = new Projectile(currentProjectile->getName(), currentProjectile->getPos(), currentProjectile->getDirection(), currentProjectile->getSpeed(), currentProjectile->getStr(), newProjectileAnimation);
	newProjectile->setPos(getPos());

	projectilesVector.push_back(newProjectile);
	animationProjectiles.push_back(newProjectileAnimation);
}

Uint32 Player::getCoolDownFb() {
	return coolDownFb;
}

Uint32 Player::getLastShotFb() {
	return lastShotFb;
}

void Player::setLastShotFb(Uint32 p_lastShot) {
	lastShotFb = p_lastShot;
}