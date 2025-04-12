#pragma once
#include <vector>
#include "GameObject.h"
#include "SDL.h"
#include "Math.h"
#include "ProjectilesManager.h"
#include "Animation.h"
#include "InputManager.h"


class Player : public GameObject {
public:
	Player();
	~Player();
	Player(Vector2f p_pos, Animation* p_animation, std::vector<Projectile*> &p_projectilePrefabs);
	void shootProjectile(std::vector<Projectile*>& projectilesVector, std::vector<Animation*>& animationProjectiles);
	void changeProjectile(InputManager& p_IM);
	Projectile* getCurrentProjectile();
	int getCoin();
	void setCoin(int p_coin);
	Projectile* getFireBallPrefab();
	Projectile* getSnowBallPrefab();
	Projectile* getWindStormPrefab();
private:
	std::vector<Projectile*> projectilePrefabs;
	Uint32 lastShotFb = 0;
	Uint32 coolDownFb = 500;
	Projectile* currentProjectile;
	int coin = 0;
};
