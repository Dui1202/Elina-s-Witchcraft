#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "Math.h"
#include "Animation.h"
#include "Collision.h"

class Enemy : public GameObject {
public:
	Enemy(Vector2f spawn_pos, Animation* p_animation, Vector2f p_direction, float p_speed, float p_hp);
	void movement();
	void update(Uint32 currentTime);
	Collider getCollider();
	void setCollider(Collider p_collider);
	float getHp();
	void setHp(float p_hp);
private:
	Vector2f direction;
	float speed;
	float hp;
	Collider collider;
};
