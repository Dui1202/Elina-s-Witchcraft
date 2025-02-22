#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Entity.h"
#include "Math.h"
#include "Animation.h"
class GameObject : public Entity {
public:
	GameObject(Vector2f p_pos, Animation* p_animation);
	void move(Vector2f p_direction);
	//SDL_Rect currentFrame;
	//SDL_Texture* tex;
};

