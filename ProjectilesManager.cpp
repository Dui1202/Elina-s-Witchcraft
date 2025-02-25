#include "GameObject.h"
#include "Math.h"
#include "ProjectilesManager.h"

Projectile::Projectile()
	:GameObject(Vector2f(0, 0), nullptr), direction(Vector2f(0,0)), speed(0){}

Projectile::Projectile(Vector2f p_pos, Vector2f p_shootDir, float p_speed,float p_str, Animation* p_animation)
: GameObject(p_pos, p_animation), direction(p_shootDir), speed(p_speed), str(p_str){
}

void Projectile::update(Vector2f startpos, Uint32 currentTime) {

	SDL_Rect hb = { getPos().x + 25,getPos().y + 30, 64, 40 };

	shoot(startpos);
	animation->setPos(getPos());
	animation->update(currentTime);
	setCollider(Collider(hb));
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

Collider Projectile::getCollider() {
	return collider;
}

void Projectile::setCollider(Collider p_collider) {
	collider = p_collider;
}

float Projectile::getStr() {
	return str;
}