#include"Entity.h"
#include<SDL.h>
#include<SDL_image.h>

Entity::Entity(Vector2f p_vector, SDL_Texture* p_tex, SDL_Rect p_frame)
	:pos(p_vector), tex(p_tex), currentFrame(p_frame){}

Vector2f& Entity::getPos() {
	return pos;
}

void Entity::setPos(const Vector2f& p_pos) {
	pos = p_pos;
}

SDL_Rect Entity::getCurrentFrame() {
	return currentFrame;
}

SDL_Texture* Entity::getTex() {
	return tex;
}