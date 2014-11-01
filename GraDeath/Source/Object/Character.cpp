#include "Object/Character.h"
#include <Box2D\Box2D.h>
#include "World/World.h"

Character::Character(CharacterData data){
	b2BodyDef def;
	//def.position.Set(data->position.x, data->position.y);

	body = World::CreateBody(&def);
	body->SetUserData(this);
	
	b2PolygonShape shape;
	// �L�����N�^�[���͂���ԑ傫�Ȏl�p���g���ǂ��ɂ����ăL�������Ƃɒ�`
	shape.SetAsBox(50 / 32, 100 / 32);

	//mesh = ModelManager::Get();
	//collisionMesh = ModelManager::Get();
}


