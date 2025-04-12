#include"Entity.h"
#include<SDL.h>
#include<SDL_image.h>
#include "Animation.h"


Entity::Entity(Vector2f p_vector,Animation* p_animation)
	:pos(p_vector),animation(p_animation) {
}

Entity::~Entity() {
	animation = nullptr;  // Safe nulling

}


Vector2f& Entity::getPos() {
	return pos;
}

void Entity::setPos(const Vector2f& p_pos) {
	pos = p_pos;
	animation->setPos(p_pos);
}


Animation* Entity::getAnimation() {
	return animation;
}

void Entity::setAnimation(Animation* p_animation) {
	animation = p_animation;
}
