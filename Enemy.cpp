#include <SDL.h>
#include "GameObject.h"
#include "Math.h"
#include "Animation.h"
#include "Enemy.h"
#include "Collision.h"

Enemy::Enemy(Vector2f spawn_pos, Animation* p_animation, Vector2f p_direction, float p_speed, float p_hp)
	: GameObject(spawn_pos, p_animation), direction(p_direction), speed(p_speed), hp(p_hp) {
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