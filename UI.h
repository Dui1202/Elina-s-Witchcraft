#pragma once
#include <functional>
#include "Text.h"
#include <SDL.h>

class UI {
public:
	UI(Vector2f p_pos, Animation* p_animation, std::vector<Animation*>& p_animationUI);
	virtual Vector2f getPos();
	virtual void setPos(Vector2f p_pos);
	virtual Animation* getAnimation();
	virtual void setAnimation(Animation* p_animation);
	virtual float getWidth();
	virtual float getHeight();
protected:
	Vector2f pos;
	Animation* animation;
	float h;
	float w;
};

class Button : public UI {
public:
	void setPos(Vector2f p_pos) override;
	Button(Vector2f p_pos, Animation* p_animation, Animation* p_hoverAnimation, Animation* p_activeAnimation , Text* p_text, std::vector<Animation*> &p_animateButtons,std::function<void()> p_function);
	bool isOnClick(const SDL_Event &e);
	bool isOn();
	void handleInput(const SDL_Event &e);
	Text* getText();
	void setVisible(bool p_bool);
	bool getVisible();
private:
	std::function<void()> onClick;

	Animation* hoverAnimation;
	Animation* normalAnimation;
	Animation* activeAnimation;

	bool isVisible = true;
	Text* text;
};

class Modal : public UI {
public:
	Modal(Vector2f p_pos, Animation* p_animation, std::vector<Button*> &p_buttons, Text* p_text, std::vector<Animation*> &p_animationUIs);
	void open();
	void close();
	bool getIsOpen();
	void setIsOpen(bool p_bool);
	void setPos(Vector2f p_pos) override;
private:

	bool isOpen = false;
	std::vector<Button*> buttons;
	Text* text;
};

class Bar : public UI {
public:
	Bar(Vector2f p_pos, Animation* p_outerBar, Animation* p_innerBar, float p_hp, std::vector<Animation*>& p_animationUI);
	Bar(Vector2f p_pos, Animation* p_outerBar, Animation* p_innerBar, Uint32 p_coolDown, std::vector<Animation*>& p_animationUI);
	Animation* getInnerAnimation();
	Animation* getOuterAnimation();
	void setInnerAnimation(Animation* p_animation);
	void update(float p_minusHp);
	float getInnerBarLength();
	void setInnerBarLength(float p_length);
private:
	Uint32 coolDown;
	float hp;
	Animation* innerBar;
	Animation* outerBar;
	bool isHpBased;
	Vector2f innerOffset = Vector2f(2, 2);
	float innerBarLength;
	float lengthEachPart;
};

class SkillHolder : public UI {
public: 
	SkillHolder(Vector2f p_pos, Bar* p_bar, Animation* p_activeAnimation, Animation* p_onCoolDownAnimation, std::vector<Animation*> &p_animationUIs, std::vector<Bar*> &p_bars);
private:
	Bar* coolDownBar;
	Animation* activeAnimation;
	Animation* onCoolDownAnimation;
};