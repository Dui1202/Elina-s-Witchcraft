#include "GameObject.h"
#include "Math.h"
#include "ProjectilesManager.h"

Projectile::Projectile(GameObject* p_gameObj, Vector2f p_shootDir, float p_speed) 
: object(p_gameObj), direction(p_shootDir), speed(p_speed){
}

void Projectile::move(){
	object->setPos(object->getPos() + direction * speed);
}