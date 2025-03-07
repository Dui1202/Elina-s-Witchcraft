#pragma once
#include <functional>
#include "Text.h"
#include <SDL.h>

class UI {
public:
	UI(Vector2f p_pos, Animation* p_animation);
	virtual Vector2f getPos();
	virtual void setPos(Vector2f p_pos);
	virtual Animation* getAnimation();
	virtual void setAnimation(Animation* p_animation);
protected:
	Vector2f pos;
	Animation* animation;
};

class Button : public UI {
public:
	Button(Vector2f p_pos, Animation* p_animation, Animation* p_hoverAnimation, Animation* p_activeAnimation , Text* p_text, std::function<void()> p_function);
	bool isOnClick(const SDL_Event &e);
	bool isOn();
	void handleInput(const SDL_Event &e);
	void hover();
	Text* getText();
private:
	std::function<void()> onClick;
	float h;
	float w;
	Animation* hoverAnimation;
	Animation* normalAnimation;
	Animation* activeAnimation;

	Text* text;
};

class Modal : public UI {
public:
	Modal(Vector2f p_pos, Animation* p_animation, std::vector<Button*> &p_buttons, Text* p_text);
	void open();
	void close();
private:
	bool isOpen = false;
	std::vector<Button*> buttons;
	Text* text;
};

class Menu : public UI {
public:
private:
};

class Bar : public UI {
public:
private:
};