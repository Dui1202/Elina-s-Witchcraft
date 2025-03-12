#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include"Entity.h"
#include "GameObject.h"
#include "Animation.h"
#include "UI.h"
#include "Text.h"

class RenderWindow {
public:
	RenderWindow(const char* title, int p_w, int h_w);
	SDL_Renderer* getRenderer();
	SDL_Texture* loadTexture(const char* p_path);
	void cleanUp();
	void clear();
	void render(GameObject &p_entity);
	void renderAnimation64(Animation* p_animate);
	void renderAnimation(Animation* p_animation);
	void renderUI(Button* p_ui);
	void renderUI(Modal* p_ui);
	void renderUI(Bar* p_bar);
	void renderText(Text* p_text);
	void display();
	float getWidth();
	float getHeight();
private:
	float h;
	float w;
	SDL_Window* window;
	SDL_Renderer* renderer;
};