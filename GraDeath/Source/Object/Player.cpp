#include "D2D/Sprite/Sprite.h"
#include "Object/Player.h"
#include"Object/CollisionShape.h"
#include "Loader/PlayerLoader.h"
#include "Utility/Converter.h"
#include "Utility/Debug.h"

#include <string>


Player::Player(){
	sprite = shared_ptr<Sprite> (new Sprite);
}

Player::~Player(){
	if ( animData.fileName )
	{
		delete[] animData.fileName;
	}
}

bool Player::Init(const char* fileName){
	PlayerLoader::LoadFile ( fileName, &animData );

	// ‘fÞ‚ª—ˆ‚½‚ç‚±‚Ìˆ—‚ð•ÏX
	std::wstring file = L"Resource/Object/Player/Player_Test.png";//"Resource/Object/Player/Player_Test.bmp";
	sprite->Create ( file.c_str () );

	animData.cellSize = D3DXVECTOR2 ( sprite->GetDefaultSize ().x / animData.rectWCount, sprite->GetDefaultSize ().y / animData.rectHCount );

	return true;
}

void Player::Release(){

}

void Player::AddForce(b2Vec2& force){
	body->ApplyForce(force, body->GetWorldCenter(),true);
}
