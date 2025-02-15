#include <SDL.h>
#include <SDL_image.h>

#include "Entity.h"
#include "Math.h"
#include "GameObject.h"

GameObject::GameObject(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame)
	:Entity(p_pos, p_tex, p_frame), tex(p_tex), currentFrame(p_frame), pos(p_pos) {}

void GameObject::move(Vector2f p_direction) {
	setPos(getPos() + p_direction);
}

