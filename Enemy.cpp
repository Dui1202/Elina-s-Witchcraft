#include <SDL.h>
#include "GameObject.h"
#include "Math.h"
#include "Animation.h"
#include "Enemy.h"
#include "Collision.h"
#include "UI.h"

Enemy::Enemy(Vector2f spawn_pos, Animation* p_animation, Vector2f p_direction, float p_speed, float p_hp, int p_coinDrop, Bar* p_bar)
	: GameObject(spawn_pos, p_animation), direction(p_direction), speed(p_speed), hp(p_hp), coinDrop(p_coinDrop), hpBar(p_bar) {
}

void Enemy::movement() {
	setPos(getPos() + direction * speed);
}

void Enemy::update(Uint32 currentTime) {
	SDL_Rect hb = { getPos().x + 10,getPos().y + 10, 64, 64};
	movement();
	getAnimation()->update(currentTime);
	getAnimation()->setPos(getPos());
	setCollider(Collider(hb));
}

Collider Enemy::getCollider() {
	return collider;
}

void Enemy::setCollider(Collider p_collider) {
	collider = p_collider;
}

float Enemy::getHp(){
	return hp;
}

void Enemy::setHp(float p_hp) {
	hp = p_hp;
}

float Enemy::getSpeed() {
	return speed;
}

void Enemy::setSpeed(float p_speed) {
	speed = p_speed;
}

float Enemy::getAngle() {
	return angle;
}

void Enemy::setAngle(float p_angle) {
	angle = p_angle;
}

Uint32 Enemy::getCoolDownDamageTick() {
	return coolDownDamageTick;
}

void Enemy::setCoolDownDamageTick(Uint32 p_coolDown) {
	coolDownDamageTick = p_coolDown;
}

Uint32 Enemy::getLastTick() {
	return lastTick;
}

void Enemy::setLastTick(Uint32 p_lastTick) {
	lastTick = p_lastTick;
}

int Enemy::getCoinDrop() {
	return coinDrop;
}

void Enemy::setCoinDrop(int p_coinDrop) {
	coinDrop = p_coinDrop;
}