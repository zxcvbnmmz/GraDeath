#include "D2D/Sprite/Sprite.h"
#include "Object/Player.h"
#include"Object/CollisionShape.h"
#include "Loader/PlayerLoader.h"
#include "Utility/Converter.h"
#include "Utility/Debug.h"
#include <string>


#include "System/Window.h"
#include "World/World.h"


Player::Player(){
	sprite = shared_ptr<Sprite> (new Sprite);
}

Player::~Player(){
}


bool Player::Init(const char* fileName, const b2Vec2& bodyPos){

	// 素材が来たらこの処理を変更
	std::wstring file = L"Resource/Object/Player/shirokuro.png";//"Resource/Object/Player/Player_Test.bmp";
	sprite->Create ( file.c_str () );

	int x, y;
	System::Window::GetWindowSize(&x, &y);

	b2BodyDef def;
	def.position = bodyPos;
	def.type = b2_dynamicBody;
	
	body = World::CreateBody(&def);
	return true;
}

void Player::Release(){
	World::DestoryBody(body);
}

void Player::AddForce(b2Vec2& force){
	body->SetLinearVelocity(force);
}

void DettachFixture(b2Body* body);

void Player::AttachFixture(vector<shared_ptr<CollisionShape>>& shapes){
	// 新しいフィクスチャーを作る前に一旦前のを消しておく
	DettachFixture(body);

	// 各セルに配置されたCollisionShapeを新しいフィクスチャーとして全てbodyに追加する
	for (auto shape : shapes){
		shape->AddFixture(body);
	}
}

void DettachFixture(b2Body* body){
	b2Fixture* fixture = body->GetFixtureList();
	if (fixture == nullptr){
		return;
	}

	while (fixture != nullptr){
		b2Fixture* temp = fixture->GetNext();
		body->DestroyFixture(fixture);
		fixture = temp;
	}
}
