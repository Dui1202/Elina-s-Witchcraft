#pragma once
#include <iostream>
#include <SDL_ttf.h>
#include <SDL.h>
#include "Math.h"

class Text {
public:
	Text();
	Text(std::string p_text, Vector2f p_pos, SDL_Color p_color, SDL_Renderer* p_renderer, TTF_Font* p_font);
	Vector2f getPos();
	void setPos(Vector2f p_pos);
	SDL_Texture* getTextTexture();
	void setText(std::string p_text);

	int getWidth();
	int getHeight();
private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Color fontColor;
	SDL_Texture* textTexture;
	Vector2f pos;
	std::string text;
	int h;
	int w;
};