#include <SDL.h>
#include <SDL_image.h>

#include "Entity.h"
#include "Math.h"
#include "GameObject.h"

GameObject::GameObject(Vector2f p_pos, Animation* p_animation)
	:Entity(p_pos, p_animation){}

//GameObject::~GameObject() {
//}

void GameObject::move(Vector2f p_direction) {
	setPos(getPos() + p_direction);
}

