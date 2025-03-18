#include <SDL.h>
#include <iostream>
#include "GameObject.h"
#include "Math.h"
#include "Animation.h"
#include "Enemy.h"
#include "Collision.h"
#include "UI.h"

Enemy::Enemy(Vector2f spawn_pos, Animation* p_animation, Vector2f p_direction, float p_speed, float p_hp, int p_coinDrop, Bar* p_bar, std::vector<Bar*>& p_bars, std::vector<Animation*>& p_enemyAnimation)
	: GameObject(spawn_pos, p_animation), direction(p_direction), speed(p_speed), hp(p_hp), coinDrop(p_coinDrop), bars(p_bars), enemyAnimation(p_enemyAnimation) {

	h = animation->getHeight();
	w = animation->getWidth();

	Bar* newHpBar = new Bar(p_bar);

	std::cout << "JALKFJAWJ   " << p_bar << " " << newHpBar << std::endl;



	hpBar = newHpBar;

	p_bars.push_back(newHpBar);
}

Enemy::Enemy(const Enemy* p_enemy)
	: GameObject(p_enemy->pos, p_enemy->animation), direction(p_enemy->direction), speed(p_enemy->speed), hp(p_enemy->hp), coinDrop(p_enemy->coinDrop), bars(p_enemy->bars), enemyAnimation(p_enemy->enemyAnimation){
	Bar* newHpBar = new Bar(p_enemy->hpBar);
	Animation* newAnimation = new Animation(*(p_enemy->animation));
	h = animation->getHeight();
	w = animation->getWidth();


	hpBar = newHpBar;
	animation = newAnimation;
	hpBar->setPos(getPos() + Vector2f(w - hpBar->getWidth() / 2, 0));

	bars.push_back(newHpBar);
	enemyAnimation.push_back(newAnimation);
}

Enemy::~Enemy() {
	std::cout << "Deconstruct a enemy!" << std::endl;
	if (hpBar) {
		delete hpBar;
		hpBar = nullptr;
	}
}

void Enemy::setPos(const Vector2f& p_pos) {
	pos = p_pos;
	hpBar->setPos(p_pos + Vector2f(w / 2 - hpBar->getWidth() / 2, 0));
	
}


void Enemy::movement() {
	setPos(getPos() + direction * speed);
	hpBar->setPos(hpBar->getPos() + direction * speed);
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

Bar* Enemy::getBar() {
	return hpBar;
}

void Enemy::setHpBar(Bar* p_bar) {
	hpBar = p_bar;

}