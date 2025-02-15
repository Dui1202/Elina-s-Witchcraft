#pragma once
#include "GameObject.h"
#include "Math.h"

class Projectile {
public:
	Projectile(GameObject* p_gameObj, Vector2f p_shootDir, float p_speed);
	void move();
private:
	GameObject* object;
	Vector2f direction;
	float speed;
};
