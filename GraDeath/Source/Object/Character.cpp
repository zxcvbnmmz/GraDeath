#include "Object/Character.h"
#include <Box2D\Box2D.h>
#include "World/World.h"

Character::Character(){
	b2BodyDef def;
	def.position.SetZero();
	body = World::CreateBody(&def);
	body->SetUserData(this);
}

