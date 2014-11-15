#include "D2D/Sprite/Sprite.h"
#include "Object/Player.h"
#include"Object/CollisionShape.h"
#include "Loader/PlayerLoader.h"
#include "Object/ObjectParameter.h"
#include <string>


Player::Player(){
	sprite = shared_ptr<Sprite> (new Sprite);
}

Player::~Player(){}

bool Player::Init(const char* fileName){
	ObjectParameter objParameter;
	PlayerLoader::LoadFile ( fileName, objParameter );

	// 素材が来たらこの処理を変更
	std::wstring file = L"Resource/Object/Player/Player_Test.bmp";
	sprite->Create ( file.c_str () );

	SetParameter ( objParameter );

	return true;
}

void Player::Release(){

}

void Player::AddForce(b2Vec2& force){
	body->ApplyForce(force, body->GetWorldCenter(),true);
}

void Player::SetParameter ( ObjectParameter& _param )
{
	for ( int i = 0; i < _param.heightLength; i++ )
	{
		shared_ptr<AnimetionParameter> param = shared_ptr<AnimetionParameter> ( new AnimetionParameter );
		param->size = D3DXVECTOR2 ( sprite->GetDefaultSize ().x / _param.widthLength, sprite->GetDefaultSize ().y / _param.heightLength );
		sprite->GetDefaultSize ();
		if ( _param.animeParameter.size () == 0 )
			continue;

		for ( int j = 0; j < _param.widthLength; j++ )
		{
			// エディタ読み込みが終了後ここを変更
			//AnimetionParameter* temp = _param.animeParameter[ j ];
			param->annimaType = 0; // temp->annimaType;
			param->animaCount = _param.widthLength; //temp->animaCount;
			//strcpy_s ( param->effectFile, param->effectCount, temp->effectFile );
			//strcpy_s ( param->soudnFile, param->soundCount, temp->soudnFile );
			//param->shortformCount = temp->shortformCount;

			//param->collisionParameter = std::move ( param->collisionParameter );
		}
		animeParameter.push_back ( param );
	}
}