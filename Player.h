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
	Player(Vector2f p_pos, Animation* p_animation, std::vector<Projectile*> &p_projectilePrefabs);
	void shootProjectile(std::vector<Projectile*>& projectilesVector, std::vector<Animation*>& animationProjectiles);
	void changeProjectile(SDL_Event& e);
	Projectile* getCurrentProjectile();
	int getCoin();
	void setCoin(int p_coin);
	/*Uint32 getCoolDownFb();
	Uint32 getLastShotFb();
	void setLastShotFb(Uint32 p_lastShot);*/
private:
	std::vector<Projectile*> projectilePrefabs;
	Uint32 lastShotFb = 0;
	Uint32 coolDownFb = 500;
	Projectile* currentProjectile;
	int coin = 0;
};
