#include "Text.h"
#include "Math.h"
#include <SDL_ttf.h>


Text::Text() {
}

Text::Text(std::string p_text, Vector2f p_pos, SDL_Color p_color, SDL_Renderer* p_renderer, TTF_Font* p_font)
	: text(p_text), pos(p_pos), fontColor(p_color), renderer(p_renderer), font (p_font) {
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), fontColor);
	textTexture = SDL_CreateTextureFromSurface(p_renderer, textSurface);
	SDL_FreeSurface(textSurface);
	textSurface = NULL;

	TTF_SizeText(font, text.c_str(), &w, &h);
}

Text::~Text() {
	if (textTexture) {
		SDL_DestroyTexture(textTexture);
		textTexture = NULL;
	}
}

Vector2f Text::getPos() {
	return pos;
}

void Text::setPos(Vector2f p_pos) {
	pos = p_pos;
}

SDL_Texture* Text::getTextTexture() {
	return textTexture;
}



void Text::setText(std::string p_text) {
	text = p_text;
}



int Text::getWidth() {
	return w;
}

int Text::getHeight() {
	return h;
}
