#pragma once
#include <vector>
#include "GameObject.h"
#include "SDL.h"
#include "Math.h"
#include "ProjectilesManager.h"
#include "Animation.h"

class Player : public GameObject {
public:
	Player();
	Player(Vector2f p_pos, Animation* p_animation, Projectile p_fireball);
	void shootFireball(std::vector<Projectile>& projectilesVector, Animation* p_fireBallAnimation, std::vector<Animation*>& animationProjectiles);
	Uint32 getCoolDownFb();
	Uint32 getLastShotFb();
	void setLastShotFb(Uint32 p_lastShot);
private:
	Projectile fireball;
	Uint32 lastShotFb = 0;
	Uint32 coolDownFb = 500;

};
