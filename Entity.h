#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include"Math.h"
#include "Animation.h"

class Entity {
public:
	Entity(Vector2f p_vector, Animation* p_animation);
	//Get the Entity position
	Vector2f& getPos();
	void setPos(const Vector2f& p_pos);
	Animation* getAnimation();
	void setAnimation(Animation* p_animation);
	//SDL_Rect getCurrentFrame();
	//SDL_Texture* getTex();
protected:
	Vector2f pos;
	//SDL_Rect currentFrame;
	//SDL_Texture* tex;
	Animation* animation;
};
