#include "GameObject.h"
#include "Math.h"
#include "ProjectilesManager.h"

Projectile::Projectile()
	:GameObject(Vector2f(0, 0), nullptr), direction(Vector2f(0,0)), speed(0){}

Projectile::Projectile(Vector2f p_pos, Vector2f p_shootDir, float p_speed, Animation* p_animation)
: GameObject(p_pos, p_animation), direction(p_shootDir), speed(p_speed){
}

void Projectile::update(Vector2f startpos, Uint32 currentTime) {
	shoot(startpos);
	animation->setPos(getPos());
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

