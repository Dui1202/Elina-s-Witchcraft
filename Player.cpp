#include <iostream>
#include <vector>
#include "GameObject.h"
#include "SDL.h"
#include "Math.h"
#include "Player.h"
#include "ProjectilesManager.h"

Player::Player()
	: GameObject(Vector2f(0,0), nullptr, {0, 0, 0, 0}){}

Player::Player(Vector2f p_pos, SDL_Texture* p_tex,  SDL_Rect p_currentFrame, Projectile p_fireball)
	: GameObject(p_pos, p_tex, p_currentFrame), fireball(p_fireball){
}

void Player::shootFireball(std::vector<Projectile>& projectilesVector) {
	std::cout << "Shoot Fire Ball!" << std::endl;
	Projectile preFabFireBall(fireball);
	preFabFireBall.setPos(getPos());
	projectilesVector.push_back(preFabFireBall);
}