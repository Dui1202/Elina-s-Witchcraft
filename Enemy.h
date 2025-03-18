#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "Math.h"
#include "Animation.h"
#include "Collision.h"
#include "UI.h"

class Enemy : public GameObject {
public:
	Enemy(Vector2f spawn_pos, Animation* p_animation, Vector2f p_direction, float p_speed, float p_hp, int p_coinDrop, Bar* p_bar, std::vector<Bar*>& p_bars, std::vector<Animation*>& p_enemyAnimation);
	Enemy(const Enemy* other);
	~Enemy();
	void setPos(const Vector2f& p_pos) override;
	void movement();
	void update(Uint32 currentTime);
	Collider getCollider();
	void setCollider(Collider p_collider);
	float getHp();
	void setHp(float p_hp);
	float getSpeed();
	void setSpeed(float p_speed);
	float getAngle();
	void setAngle(float p_angle);
	Uint32 getLastTick();
	void setLastTick(Uint32 p_lastTick);
	Uint32 getCoolDownDamageTick();
	void setCoolDownDamageTick(Uint32 p_coolDown);
	int getCoinDrop();
	void setCoinDrop(int p_coinDrop);
	Bar* getBar();
	void setHpBar(Bar* p_bar);
private:
	Vector2f direction;
	float speed;
	float hp;
	Collider collider;
	float angle = 0;
	Uint32 lastTick = 0;
	Uint32 coolDownDamageTick = 1000;
	int coinDrop;
	Bar* hpBar;
	std::vector<Bar*>& bars;
	std::vector<Animation*>& enemyAnimation;
	float w;
	float h;
};
