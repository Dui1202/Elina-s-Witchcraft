#pragma once
#include <SDL.h>

class Collider {
public:
	Collider();
	Collider(SDL_Rect p_hitbox);
	SDL_Rect getRect();
	void setRect(SDL_Rect p_hitbox);
	bool checkCollide(Collider p_other);
	bool getIsCollide();
	void setIsCollide(bool p_tf);
	void drawCollider(SDL_Renderer* p_renderer);
private:
	SDL_Rect hitbox ;
	bool isCollide = false;
};