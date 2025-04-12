#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include"Math.h"
#include "Animation.h"

class Entity {
public:
	Entity(Vector2f p_vector, Animation* p_animation);
	virtual ~Entity();
	//Get the Entity position
	virtual Vector2f& getPos();
	virtual void setPos(const Vector2f& p_pos);
	Animation* getAnimation();
	void setAnimation(Animation* p_animation);

protected:
	Vector2f pos;
	Animation* animation;
	float renderScale;
};
