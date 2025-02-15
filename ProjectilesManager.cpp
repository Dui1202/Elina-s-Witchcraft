#include "GameObject.h"
#include "Math.h"
#include "ProjectilesManager.h"

Projectile::Projectile()
	:GameObject(Vector2f(0, 0), nullptr, { 0, 0, 0, 0 }), direction(Vector2f(0,0)), speed(0){}

Projectile::Projectile(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame, Vector2f p_shootDir, float p_speed)
: GameObject(p_pos, p_tex, p_frame), direction(p_shootDir), speed(p_speed){
}

void Projectile::shoot(Vector2f startpos){
	setPos(getPos() + direction * speed);
}

