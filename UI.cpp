#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "GameObject.h"
#include "Math.h"
#include "Animation.h"
#include "UI.h"

UI::UI(Vector2f p_pos, Animation* p_animation)
	:pos(p_pos), animation(p_animation){
}

Vector2f UI::getPos() {
	return pos;
}

void UI::setPos(Vector2f p_pos){
	pos = p_pos;
}

Animation* UI::getAnimation() {
	return animation;
}

void UI::setAnimation(Animation* p_animation) {
	animation = p_animation;
}

Button::Button(Vector2f p_pos, Animation* p_normalAnimation, Animation* p_hoverAnimation, Animation* p_activeAnimation, Text* p_text, std::function<void()> p_function)
	: UI(p_pos, p_normalAnimation), normalAnimation(p_normalAnimation), hoverAnimation(p_hoverAnimation), activeAnimation(p_activeAnimation), text(p_text), onClick(p_function) {
	h = animation->getCurrentFrameRect().h;
	w = animation->getCurrentFrameRect().w;
	Vector2f textPos(getPos() + Vector2f( w / 2, h / 2) - Vector2f(text->getWidth()/2, text->getHeight()/2));
	text->setPos(textPos);
	getAnimation()->setPos(p_pos);
	normalAnimation->setPos(p_pos);
	hoverAnimation->setPos(p_pos);
	activeAnimation->setPos(p_pos);
}

bool Button::isOnClick(const SDL_Event& e) {
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		Vector2f mouseVector2f(x, y);

		bool isInside = true;

		if (mouseVector2f.x < getPos().x) {
			isInside = false;
		}

		if (mouseVector2f.y < getPos().y) {
			isInside = false;
		}

		if (mouseVector2f.y > getPos().y + h) {
			isInside = false;
		}

		if (mouseVector2f.x > getPos().x + w) {
			isInside = false;
		}

		return isInside;

	}

	return false;
}

bool Button::isOn() {

		int x, y;
		SDL_GetMouseState(&x, &y);
		Vector2f mouseVector2f(x, y);

		bool isInside = true;

		if (mouseVector2f.x < getPos().x) {
			isInside = false;
		}

		if (mouseVector2f.y < getPos().y) {
			isInside = false;
		}

		if (mouseVector2f.y > getPos().y + h) {
			isInside = false;
		}

		if (mouseVector2f.x > getPos().x + w) {
			isInside = false;
		}

		return isInside;

}

void Button::handleInput(const SDL_Event &p_e) {

	if (isOnClick(p_e)) {
		onClick();
		setAnimation(activeAnimation);
	}
	else if (isOn()) {
		setAnimation(hoverAnimation);
	}
	else {
		setAnimation(normalAnimation);
	}
}

Text* Button::getText() {
	return text;
}

Modal::Modal(Vector2f p_pos, Animation* p_animation, std::vector<Button*> &p_buttons, Text* p_heading) 
	:UI(p_pos, p_animation), buttons(p_buttons), text(p_heading)
{
	close();
}
	

void Modal::close() {
	setPos(getPos() + Vector2f(2000, 2000));
	for (auto& btn : buttons) {
		btn->setPos(btn->getPos() + Vector2f(2000, 2000));
		btn->getAnimation()->setPos()
	}
}

void Modal::open() {
	setPos(getPos() - Vector2f(2000, 2000));
}



