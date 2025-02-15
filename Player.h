#pragma once

#include "GameObject.h"
#include "SDL.h"
#include "Math.h"
#include "ProjectilesManager.h"

class Player : public GameObject {
public:
	Player();
	Player(Vector2f p_pos, SDL_Texture* p_tex,  SDL_Rect currentFrame);
private:
};
