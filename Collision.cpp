#include <SDL.h>
#include "Collision.h"

Collider::Collider(){}

Collider::Collider(SDL_Rect p_hitbox)
	:hitbox(p_hitbox){}

SDL_Rect Collider::getRect() {
	return hitbox;
}

void Collider::setRect(SDL_Rect p_hitbox) {
	hitbox = p_hitbox;
}

bool Collider::getIsCollide() {
	return isCollide;
}

void Collider::setIsCollide(bool p_tf) {
	isCollide = p_tf;
}

bool Collider::checkCollide(Collider p_other) {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = hitbox.x;
    rightA = hitbox.x + hitbox.w;
    topA = hitbox.y;
    bottomA = hitbox.y + hitbox.h;

    //Calculate the sides of rect B
    leftB = p_other.getRect().x;
    rightB = p_other.getRect().x + p_other.getRect().w;
    topB = p_other.getRect().y;
    bottomB = p_other.getRect().y + p_other.getRect().h;

    //If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
 
void Collider::drawCollider(SDL_Renderer* p_renderer) {
    SDL_SetRenderDrawColor(p_renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(p_renderer, &hitbox);
}
