#pragma once
#include "GameObject.h"
#include "Math.h"

class Projectile : public GameObject {
public:
	Projectile();
	Projectile(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame, Vector2f p_shootDir, float p_speed);
	void shoot(Vector2f startPos);
private:
	Vector2f direction;
	float speed;
	
};
