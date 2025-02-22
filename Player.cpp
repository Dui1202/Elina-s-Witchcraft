#include <iostream>
#include <vector>
#include "GameObject.h"
#include "SDL.h"
#include "Math.h"
#include "Player.h"
#include "ProjectilesManager.h"

Player::Player()
	: GameObject(Vector2f(0,0), nullptr){}

Player::Player(Vector2f p_pos, Animation* p_animation, Projectile p_fireball)
	: GameObject(p_pos, p_animation), fireball(p_fireball){
}

void Player::shootFireball(std::vector<Projectile>& projectilesVector, Animation* p_fireBallAnimation, std::vector<Animation*>& animationProjectiles) {
	std::cout << "Shoot Fire Ball!" << std::endl;
	
	Animation* newfireBallAnimation = new Animation(*p_fireBallAnimation);
	Projectile newFireBall(fireball.getPos(), fireball.getDirection(), fireball.getSpeed(), newfireBallAnimation);
	newFireBall.setPos(getPos());

	projectilesVector.push_back(newFireBall);
	animationProjectiles.push_back(p_fireBallAnimation);
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