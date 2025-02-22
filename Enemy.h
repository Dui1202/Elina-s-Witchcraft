#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "Math.h"
#include "Animation.h"

class Enemy : public GameObject {
public:
	Enemy(Vector2f spawn_pos, Animation* p_animation, Vector2f p_direction, float p_speed);
	void movement();
private:
	Vector2f direction;
	float speed;
};
