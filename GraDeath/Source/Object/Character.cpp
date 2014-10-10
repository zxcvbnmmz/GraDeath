#include "Object/Character.h"
#include <Box2D\Box2D.h>

Character::Character(){
	b2BodyDef def;
	b2World world(b2Vec2(0,-9.8));
	body = world.CreateBody(&def);
	body->SetUserData(this);
}

