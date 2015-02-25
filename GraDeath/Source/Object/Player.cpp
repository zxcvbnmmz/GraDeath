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
	IsCollidable = true;
}

Player::~Player(){
}

bool Player::Init(const char* fileName, const b2Vec2& bodyPos, float scale){

	// 素材が来たらこの処理を変更
	WCHAR temp[80];

	sprite.reset(new Sprite);
	sprite->Create( Utility::ConvertToWChar(temp,fileName));
	sprite->SetScale(scale, scale);

	int x, y;
	System::Window::GetWindowSize(&x, &y);

	b2BodyDef def;
	def.position = bodyPos;
	def.type = b2_dynamicBody;
	
	body = World::CreateBody(&def);
	body->SetUserData(this);
	IsCollidable = true;

	return true;
}

void Player::Release(){
	World::DestoryBody(body);
	sprite.reset();
}

void Player::AddForce(b2Vec2& force){
	body->SetLinearVelocity(force);
}

void Player::AddPosition(float x, float y){
	b2Transform t = body->GetTransform();
	t.p += b2Vec2(x,y);
	body->SetTransform(t.p,0);
}

void Player::SetAngularVelocity(b2Vec2& force){
	body->ApplyForce(force,body->GetPosition(),false);
}

void DettachFixture(b2Body* body);

void Player::AttachFixture(vector<shared_ptr<CollisionShape>>& shapes){
	// 新しいフィクスチャーを作る前に一旦前のを消しておく
	DettachFixture(body);

	if (!IsCollidable){
		return;
	}

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

void Player::Destroy(){
	DettachFixture(body);
	IsCollidable = false;
}