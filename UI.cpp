#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "GameObject.h"
#include "Math.h"
#include "Animation.h"
#include "UI.h"

UI::UI(Vector2f p_pos, Animation* p_animation, std::vector<Animation*> &p_animationUIs)
	:pos(p_pos), animationUIs(p_animationUIs){
	Animation* newAnimation = new Animation(*p_animation);
	animation = newAnimation;

	h = getAnimation()->getHeight();
	w = getAnimation()->getWidth();


	p_animationUIs.push_back(newAnimation);
}

//UI::~UI() {
//	delete animation;
//}

Vector2f UI::getPos() {
	return pos;
}

void UI::setPos(Vector2f p_pos){
	pos = p_pos;
	getAnimation()->setPos(p_pos);
}

Animation* UI::getAnimation() {
	return animation;
}

void UI::setAnimation(Animation* p_animation) {
	animation = p_animation;
}

float UI::getWidth() {
	return w;
}

float UI::getHeight() {
	return h;
}

float UI::getScale() {
	return renderScale;
}

std::vector<Animation*>& UI::getAnimationUIs() {
	return animationUIs;
}

Button::Button(Vector2f p_pos, Animation* p_normalAnimation, Animation* p_hoverAnimation, Animation* p_activeAnimation, Text* p_text, std::vector<Animation*>& p_animationUIs, std::function<void()> p_function)
	: UI(p_pos, p_normalAnimation, p_animationUIs), text(p_text), onClick(p_function) {


	//Set the text's position in the center of the button
	Vector2f textPos(getPos() + Vector2f( w / 2, h / 2) - Vector2f(text->getWidth()/2, text->getHeight()/2));
	text->setPos(textPos);

	normalAnimation = animation;
	Animation* newHoverAnimation = new Animation(*p_hoverAnimation);
	Animation* newActiveAnimation = new Animation(*p_activeAnimation);

	hoverAnimation = newHoverAnimation;
	activeAnimation = newActiveAnimation;

	getAnimation()->setPos(p_pos);
	normalAnimation->setPos(p_pos);
	hoverAnimation->setPos(p_pos);
	activeAnimation->setPos(p_pos);

	p_animationUIs.push_back(newHoverAnimation);
	p_animationUIs.push_back(newActiveAnimation);
}

void Button::setPos(Vector2f p_pos) {
	animation->setPos(p_pos);
	hoverAnimation->setPos(p_pos);
	activeAnimation->setPos(p_pos);
	text->setPos(text->getPos() + p_pos);
	pos = p_pos;
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
	if (isEnable) {
		if (getVisible()) {
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
	}
}

Text* Button::getText() {
	return text;
}

void Button::setVisible(bool p_bool) {
	isVisible = p_bool;
}

bool Button::getVisible() {
	return isVisible;
}

bool Button::getEnable() {
	return isEnable;
}

void Button::setEnable(bool p_bool) {
	isEnable = p_bool;
}

Modal::Modal(Vector2f p_pos, Animation* p_animation, std::vector<Button*> &p_buttons, Text* p_heading, std::vector<Animation*> &p_animationUIs) 
	:UI(p_pos, p_animation, p_animationUIs), buttons(p_buttons), text(p_heading)
{
	close();
}

//Modal::~Modal() {
//	if (text) {
//		delete text;
//		text = nullptr;
//	}
//}
	
void Modal::setPos(Vector2f p_pos) {
	int i = 0;
	animation->setPos(p_pos);
	text->setPos(p_pos);
	pos = p_pos;

	for (auto& btn : buttons) {
		
		btn->setPos(p_pos + Vector2f(getWidth() / 2, 20 + i * 80 ) - Vector2f(btn->getAnimation()->getCurrentFrameRect().w / 2, 0));
		i++;
	}
}

void Modal::close() {
	setIsOpen(false);
	for (auto& btn : buttons) {
		btn->setVisible(false);
	}
}

void Modal::open() {
	setIsOpen(true);
	for (auto& btn : buttons) {
		btn->setVisible(true);
;	}
}

bool Modal::getIsOpen() {
	return isOpen;
}

void Modal::setIsOpen(bool p_bool) {
	isOpen = p_bool;
}

//Bar
Bar::Bar(Vector2f p_pos, Animation* p_outerBar, Animation* p_innerBar, float p_hp, std::vector<Animation*>& p_animationUI)
	: UI(p_pos, p_outerBar, p_animationUI), outerBar(p_outerBar), innerBar(p_innerBar), hp(p_hp) {
	coolDown = 0;
	isHpBased = true;

	outerBar->setPos(p_pos);
	innerBar->setPos(outerBar->getPos() + innerOffset);

	innerBarLength = innerBar->getCurrentFrameRect().w;
	lengthEachPart = innerBarLength / hp;

}

Bar::Bar(Vector2f p_pos, Animation* p_outerBar, Animation* p_innerBar, Uint32 p_coolDown, std::vector<Animation*>& p_animationUI) 
	: UI(p_pos, p_outerBar, p_animationUI), outerBar(p_outerBar), innerBar(p_innerBar), coolDown(p_coolDown) {
	hp = 0;
	isHpBased = false;
	Animation* newOuterBar = new Animation(*p_outerBar);
	Animation* newInnerBar = new Animation(*p_innerBar);
	
	outerBar = newOuterBar;
	innerBar = newInnerBar;

	outerBar->setPos(p_pos);
	innerBar->setPos(outerBar->getPos() + innerOffset);

	innerBarLength = innerBar->getCurrentFrameRect().w;
	lengthEachPart = innerBarLength / hp;

	p_animationUI.push_back(newOuterBar);
	p_animationUI.push_back(newInnerBar);
}

Bar::Bar(const Bar* other)
	: UI(other->pos, other->outerBar, (other->animationUIs)), hp(other->hp), coolDown(other->coolDown) {
	isHpBased = true;

	Animation* newInnerAnimation = new Animation(*(other->innerBar));
	Animation* newOuterAnimation = new Animation(*(other->outerBar));

	innerBar = newInnerAnimation;
	outerBar = newOuterAnimation;

	outerBar->setPos(pos);
	innerBar->setPos(outerBar->getPos() + innerOffset);


	innerBarLength = innerBar->getCurrentFrameRect().w;
	if (coolDown == 0) {
		lengthEachPart = innerBarLength / hp;
	}
	else if (hp == 0) {
		lengthEachPart = innerBarLength / coolDown;
	}
	

	animationUIs.push_back(newInnerAnimation);
	animationUIs.push_back(newOuterAnimation);
}

//Bar::~Bar() {
//	if (innerBar) {
//		delete innerBar;
//		innerBar = nullptr;
//	}
//
//	if (outerBar) {
//		delete outerBar;
//		outerBar = nullptr;
//	}
//}

Animation* Bar::getInnerAnimation() {
	return innerBar;
}

Animation* Bar::getOuterAnimation() {
	return outerBar;
}

void Bar::setPos(Vector2f p_pos) {
	animation->setPos(p_pos);
	outerBar->setPos(p_pos);
	innerBar->setPos(p_pos + innerOffset);
	pos = p_pos;
}

void Bar::setInnerAnimation(Animation* p_animation) {
	innerBar = p_animation;
}

void Bar::setOuterAnimation(Animation* p_animation) {
	outerBar = p_animation;
}

void Bar::update(float p_minusHp) {
	std::cout << "Bar updated!" << std::endl;
	innerBarLength = innerBarLength - (lengthEachPart * p_minusHp);
	int remainLength = static_cast<int>(innerBarLength);
	innerBar->setFrameRectW(remainLength);
}

float Bar::getInnerBarLength() {
	return innerBarLength;
}

void Bar::setInnerBarLength(float p_length) {
	innerBarLength = p_length;
}

//Skill Holder
SkillHolder::SkillHolder(Vector2f p_pos, Bar* p_bar, Animation* p_activeAnimation, Animation* p_onCoolDownAnimation, std::vector<Animation*> &p_animationUIs, std::vector<Bar*> &p_bars)
	: UI(p_pos, p_activeAnimation, p_animationUIs) {
	Animation* newActiveAnimation = new Animation(*p_activeAnimation);
	Animation* newOnCoolDownAnimation = new Animation(*p_onCoolDownAnimation);
	Bar* newBar = new Bar(*p_bar);

	activeAnimation = newActiveAnimation;
	onCoolDownAnimation = newOnCoolDownAnimation;
	coolDownBar = newBar;

	p_animationUIs.push_back(newActiveAnimation);
	p_animationUIs.push_back(newOnCoolDownAnimation);
	p_bars.push_back(newBar);
}

