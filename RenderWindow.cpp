#include <iostream>
#include<SDL.h>
#include<SDL_image.h>

#include "RenderWindow.hpp"
#include "Entity.h"
#include "Math.h"
#include "GameObject.h"
#include "Animation.h"

RenderWindow::RenderWindow(const char* title, int p_w, int p_h)
	:window(NULL), renderer(NULL), h(p_h), w(p_w){
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "Failed to initialize window! Error: " << SDL_GetError << std::endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Renderer* RenderWindow::getRenderer() {
	return renderer;
}

SDL_Texture* RenderWindow::loadTexture(const char* p_path) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_path);
	if (texture == NULL) {
		std::cout << "Failed to load texture! Error:" << SDL_GetError() << std::endl;
	}

	return texture;
}
void RenderWindow::cleanUp() {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
}
void RenderWindow::clear() {
	SDL_RenderClear(renderer);
}
//void RenderWindow::render(GameObject &p_entity) {
//	SDL_Rect src;
//	src.x = p_entity.getCurrentFrame().x;
//	src.y = p_entity.getCurrentFrame().y;
//	src.w = p_entity.getCurrentFrame().w;
//	src.h = p_entity.getCurrentFrame().h;
//
//	SDL_Rect dst;
//	dst.x = p_entity.getPos().x;
//	dst.y = p_entity.getPos().y;
//	dst.w = p_entity.getCurrentFrame().w*2;
//	dst.h = p_entity.getCurrentFrame().h*2;
//	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
//}

void RenderWindow::renderAnimation64(Animation* p_animation) {
	SDL_Rect src;
	src.x = p_animation->getCurrentFrameRect().x;
	src.y = p_animation->getCurrentFrameRect().y;
	src.w = p_animation->getCurrentFrameRect().w;
	src.h = p_animation->getCurrentFrameRect().h;

	SDL_Rect dst;
	dst.x = p_animation->getPos().x;
	dst.y = p_animation->getPos().y;
	dst.w = p_animation->getCurrentFrameRect().w * 1.5;
	dst.h = p_animation->getCurrentFrameRect().h * 1.5;

	SDL_RenderCopy(renderer, p_animation->getTexture(), &src, &dst);
}

void RenderWindow::renderAnimation(Animation* p_animation) {
	SDL_Rect src;
	src.x = p_animation->getCurrentFrameRect().x;
	src.y = p_animation->getCurrentFrameRect().y;
	src.w = p_animation->getCurrentFrameRect().w;
	src.h = p_animation->getCurrentFrameRect().h;

	SDL_Rect dst;
	dst.x = p_animation->getPos().x;
	dst.y = p_animation->getPos().y;
	dst.w = p_animation->getCurrentFrameRect().w ;
	dst.h = p_animation->getCurrentFrameRect().h ;

	SDL_RenderCopy(renderer, p_animation->getTexture(), &src, &dst);
}
void RenderWindow::renderUI(Button* p_ui) {
	renderAnimation(p_ui->getAnimation());
	renderText(p_ui->getText());
}

void RenderWindow::renderUI(Modal* p_ui) {
	renderAnimation(p_ui->getAnimation());
}

void RenderWindow::renderUI(Bar* p_bar) {
	renderAnimation(p_bar->getOuterAnimation());
	renderAnimation(p_bar->getInnerAnimation());
}

void RenderWindow::renderText(Text* p_text) {
	SDL_Rect dst;
	dst.x = p_text->getPos().x;
	dst.y = p_text->getPos().y;
	dst.w = p_text->getWidth() ;
	dst.h = p_text->getHeight() ;

	SDL_RenderCopy(renderer, p_text->getTextTexture(), NULL, &dst);
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}

float RenderWindow::getHeight() {
	return h;
}

float RenderWindow::getWidth() {
	return w;
}