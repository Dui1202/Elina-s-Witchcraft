#include "Math.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Animation.h"

Animation::Animation(Vector2f p_pos, SDL_Texture* p_sprite, int p_frames, SDL_Rect p_frameSize, Uint32 p_timePerFrame)
	: pos(p_pos), animateSprite(p_sprite), frames(p_frames), frameSize(p_frameSize), timePerFrame(p_timePerFrame){
	
	for (int i = 1; i <= frames; i++) {
		SDL_Rect frame = { 0 + (frameSize.w * (i - 1)) , 0, frameSize.w, frameSize.h};
		frameSrcs.push_back(frame);
	}

	currentFrameRect = frameSrcs[0];
}

void Animation::update(Uint32 p_currentTime) {
	if (p_currentTime - timeLastFrame >= timePerFrame) {
		timeLastFrame = p_currentTime;
		if (getCurrentFrame() >= frames - 1) {
			setCurrentFrame(0);
		}
		else {
			setCurrentFrame(getCurrentFrame() + 1);
			
		}
		setCurrentFrameRect(getCurrentFrame());
	}
}

Vector2f Animation::getPos() {
	return pos;
}

void Animation::setPos(Vector2f p_pos) {
	pos = p_pos;
}

SDL_Texture* Animation::getTexture() {
	return animateSprite;
}

SDL_Rect Animation::getCurrentFrameRect() {
	return frameSrcs[getCurrentFrame()];
}

void Animation::setCurrentFrameRect(int p_currentFrame) {
	currentFrameRect = frameSrcs[p_currentFrame];
}

int Animation::getFrames() {
	return frames;
}

int Animation::getCurrentFrame() {
	return currentFrame;
}

void Animation::setCurrentFrame(int p_frame) {
	currentFrame = p_frame;
}

void Animation::move(Vector2f p_dir, float p_speed) {
	setPos(getPos() + p_dir * p_speed);
}