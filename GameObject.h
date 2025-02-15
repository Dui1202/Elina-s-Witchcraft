#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Entity.h"
#include "Math.h"
class GameObject : public Entity {
public:

	GameObject(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame);
	void move(Vector2f p_direction);
protected:
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};

