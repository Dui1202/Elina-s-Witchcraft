#pragma once
#include "Math.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
class Animation {
public:
	Animation();
	Animation(Vector2f p_pos, SDL_Texture* p_sprite, int p_frames, SDL_Rect p_frameSize, Uint32 timePerFrame);
	void update(Uint32 p_currentTime);
	Vector2f getPos();
	void setPos(Vector2f p_pos);
	SDL_Texture* getTexture();
	SDL_Rect getCurrentFrameRect();
	void setCurrentFrameRect(int p_currentFrame);
	int getFrames();
	int getCurrentFrame();
	void setCurrentFrame(int p_frame);
	void move(Vector2f p_dir, float speed);
private:
	Vector2f pos;
	SDL_Texture* animateSprite;
	int frames;
	int currentFrame = 0;
	SDL_Rect currentFrameRect;
	SDL_Rect frameSize;
	Uint32 timePerFrame;
	std::vector<SDL_Rect> frameSrcs;
	Uint32 timeLastFrame = 0;
};