#include "Object/Object.h"
#include <Box2D\Box2D.h>

Object::Object():body(nullptr){}

const b2Vec2& Object::GetPosition(){
	return body->GetPosition();
}

