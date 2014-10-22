#include "Object/Object.h"
#include <Box2D\Box2D.h>

Object::Object():body(nullptr), pos(b2Vec2(0, 0)), scale(b2Vec2(1, 1)), rot(0){
}



