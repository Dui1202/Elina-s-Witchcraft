#pragma once
#include "GameObject.h"
#include "Math.h"
#include "Animation.h"

class Projectile : public GameObject {
public:
	Projectile();
	Projectile(Vector2f p_pos, Vector2f p_shootDir, float p_speed, Animation* p_animation);
	void shoot(Vector2f startPos);
	void update(Vector2f startpos, Uint32 currentTime);
	Vector2f getDirection();
	float getSpeed();
private:
	Vector2f direction;
	float speed;
};
