#include <SDL.h>
#include "GameObject.h"
#include "Math.h"
#include "Animation.h"
#include "Enemy.h"

Enemy::Enemy(Vector2f spawn_pos, Animation* p_animation, Vector2f p_direction, float p_speed)
	: GameObject(spawn_pos, p_animation), direction(p_direction), speed(p_speed) {

}

void Enemy::movement() {
	setPos(getPos() + direction * speed);
}