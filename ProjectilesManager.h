#pragma once
#include <iostream>
#include "GameObject.h"
#include "Math.h"
#include "Animation.h"
#include "Collision.h"

class Projectile : public GameObject {
public:
	Projectile();
	Projectile(std::string p_name, Vector2f p_pos, Vector2f p_shootDir, float p_speed,float p_str, Uint32 p_coolDown, Animation* p_animation);
	void shoot(Vector2f startPos);
	void update(Vector2f startpos, Uint32 currentTime);
	Vector2f getDirection();
	float getSpeed();
	void setSpeed(float p_speed);
	Collider getCollider();
	void setCollider(Collider p_collider);
	float getStr();
	void setStr(float p_str);
	std::string getName();
	void setName(std::string p_name);
	Uint32 getCoolDown();
	void setCoolDown(Uint32 p_coolDown);
	Uint32 getLastShot();
	void setLastShot(Uint32 p_lastShot);
	Uint32 getCoolDownDamageTick();
	void setCoolDownDamageTick(Uint32 p_coolDown);
	Uint32 getLastTick();
	void setLastTick(Uint32 p_lastTick);
private:
	Vector2f direction;
	float speed;
	float str;
	Collider collider;
	std::string name;
	Uint32 coolDown;
	Uint32 lastShot = 0;
	Uint32 coolDownDamageTick = 1000;
	Uint32 lastTick = 0;
};
