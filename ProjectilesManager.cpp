#include "GameObject.h"
#include "Math.h"
#include "ProjectilesManager.h"
#include <iostream>

Projectile::Projectile()
	:GameObject(Vector2f(0, 0), nullptr), direction(Vector2f(0,0)), speed(0){}

Projectile::Projectile(std::string p_name, Vector2f p_pos, Vector2f p_shootDir, float p_speed, float p_str, Uint32 p_coolDown, Animation* p_animation)
: GameObject(p_pos, p_animation), name(p_name), direction(p_shootDir), speed(p_speed), str(p_str), coolDown(p_coolDown) {
	if (name == "windStorm") {
		coinForUpgrade = 100;
	}
	else if (name == "fireBall") {
		coinForUpgrade = 50;
	}
	else if (name == "snowBall") {
		coinForUpgrade = 50;
	}
}

Projectile::~Projectile() {


	animation = nullptr; // Safe nullify

	std::cout << "Projectile [" << name << "] destroyed!" << std::endl;
}



void Projectile::update(Vector2f startpos, Uint32 currentTime) {


	if (name == "windStorm") {
		shoot(startpos + Vector2f(0, -64));
		animation->setPos(getPos() + Vector2f(0, -64));
		SDL_Rect windStormHb = { getPos().x + 25, getPos().y, 64, 80 };
		setCollider(Collider(windStormHb));
	}
	else {
		shoot(startpos);
		SDL_Rect hb = { getPos().x + 25,getPos().y + 30, 64, 40 };
	    animation->setPos(getPos());
		setCollider(Collider(hb));
	}
	animation->update(currentTime);
	
}

void Projectile::shoot(Vector2f startpos){
	setPos(getPos() + direction * speed);
}

Vector2f Projectile::getDirection() {
	return direction;
}

float Projectile::getSpeed() {
	return speed;
}

void Projectile::setSpeed(float p_speed) {
	speed = p_speed;
}

Collider Projectile::getCollider() {
	return collider;
}

void Projectile::setCollider(Collider p_collider) {
	collider = p_collider;
}

float Projectile::getStr() {
	return str;
}

void Projectile::setStr(float p_str) {
	str = p_str;
}

std::string Projectile::getName() {
	return name;
}

void Projectile::setName(std::string p_name) {
	name = p_name;
}

Uint32 Projectile::getCoolDown() {
	return coolDown;
}

void Projectile::setCoolDown(Uint32 p_coolDown) {
	coolDown = p_coolDown;
}

Uint32 Projectile::getLastShot() {
	return lastShot;
}

void Projectile::setLastShot(Uint32 p_lastShot) {
	lastShot = p_lastShot;
}

Uint32 Projectile::getCoolDownDamageTick() {
	return coolDownDamageTick;
}

void Projectile::setCoolDownDamageTick(Uint32 p_coolDown) {
	coolDownDamageTick = p_coolDown;
}

Uint32 Projectile::getLastTick() {
	return lastTick;
}

void Projectile::setLastTick(Uint32 p_lastTick) {
	lastTick = p_lastTick;
}

bool Projectile::isOnCoolDown(Uint32 p_currentTime) {
	Uint32 timer = p_currentTime - lastShot;
	bool offCoolDown = (timer < coolDown);
	return offCoolDown;
}

void Projectile::levelUp() {
	if (level < 5) {
		level++;
		std::cout << "Level Up!" << std::endl;
		if (name == "windStorm") {
			str += 0.5;
			coolDown -= 500;
		}
		else if (name == "fireBall") {
			str += 3;
		}
		else if (name == "snowBall") {
			str += 1;
			coolDown -= 200;
		}
	}
}

int Projectile::getUpgradeCoin() {
	return coinForUpgrade;
}

void Projectile::levelUpUpgradeCoin() {
	if (level < 5) {
		if (name == "windStorm") {
			coinForUpgrade += 100;
		}
		else if (name == "fireBall") {
			coinForUpgrade += 50;
		}
		else if (name == "snowBall") {
			coinForUpgrade += 50;
		}
	}
}
